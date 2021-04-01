# TODO
- twee keer dezelfde naam mag niet worden opgegeven voor de votefunctie, maar dat wordt niet gecontroleerd, dus...
- PREFERENCES is een 2D-matrix array[][] uit X * X-1 elementen...
- dus een dubbele for loop met een break als x = x (want [x][x] kan niet)
- en dat voor elke voter! Of niet? ...
- neen, het is een 2 niveau matrix, want enkel wie wint bij face to face elections. Dus voorkeur
- voor Tom, tweede plaats Piet...

# De preferences
- ik zat verkeerd: ik voegde de ranks toe aan de kandidaat, maar moet eigenlijk
- omgekeerd werken.
- - voor elke voter wordt de ranks array doorgegeven aan de
- preferences functie. De preferences functie bepaalt hoeveel
- stemmen een kandidaat beter is dan de andere. Dus de balans
- tussen een paar.

- DUS:
* kijk voor elk paar naar de machtsverhouding en
* leg die vast in de preferences array.
* Doe dit al met het eerste paar.

# Nu kijk ik eerst naar de punten,
maar ik moet eerst naar de kandidaten kijke

oude preferences:

  for (int i = 0; i < candidate_count - 1; i ++)
    {
        int winner = ranks[i];
        // give winner a point for every loser
        for (int j = i + 1; j < candidate_count - i; j++)
        {
            preferences[winner][ranks[j]]++;


# Pairsss...
# LOCKING
De cycles bepalen is heel moeilijk voor mij...
voor elk nieuw toe te voegen paar W-V moet ik controleren:
1/ of de V nooit Winnaar is geweest van W (gemakkelijk) - dat is de basecase.
2/ of de vorige winnaar W2 van W en diens winnaar en diens winnaar, enz.. nooit verloren is van V

* A heeft gewonnen van B
* Heeft B ooit gewonnen van A?
* Als ja => SKIP WANT CYCLE
* Als neen:
  * heeft ooit iemand gewonnen van A?
    * als neen: prachtig! =>  NIET SKIPPEN
    * als ja: heeft B ooit gewonnen van winnaars van A?
      * als ja => SKIP WANT CYCLE
      * als neen: heeft ooit iemand gewonnen van de winnaars van A?
        * als neen: prachtig! => NIET SKIPPEN
        * als ja: heeft B ooit gewonnen tegen de winnaars van de winnaars van A?
          * als ja => SKIP WANT CYCLE
          * als neen: heeft B ooit gewonnen tegen de winnaars van de winnaars van de winnaars ...

return recursieve functie(args);

# Oude functie locked

 // lock all pairs, but avoid cycles
    // first pair can be locked
    // second pair no cycle?
    int first_winner = pairs[0].winner;
    int first_loser = pairs[0].loser;
    int winners[MAX] = {-1}; // fill with value we will not encounter
    int losers[MAX] = {-1};
    printf("Pairs: %d", pair_count);
    for (int i = 0; i < pair_count; i++)
    {
        int this_winner = pairs[i].winner;
        int this_loser = pairs[i].loser;
        // sometimes we will have to skip here
        int skip = 0;
        // for example, if winner has ever lost from loser
        for (int j = 0; j < pair_count; j++)
        {
            if (this_winner == losers[j] && this_loser == winners[j])
            {
                skip = 1;
            }
        }
        if (skip == 1)
        {
            break;
        }
        locked[this_winner][this_loser] = true;
        winners[i] = this_winner;
        losers[i] = this_loser;
    }
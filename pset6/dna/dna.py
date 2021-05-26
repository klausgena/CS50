import re
import sys
import csv

# check number of arguments
if len(sys.argv) < 3:
    print("This program needs exactly 2 arguments.")

# read files
# csv contains names database
csv_file = open(sys.argv[1], "r")
database = csv.DictReader(csv_file)
# txt contains helix
with open(sys.argv[2], "r") as txt:
    helix = txt.read()

# FUNCTIONS


def get_longest_STR(sequence, helix):
    # Get the longest run of consecutive repeats of
    # a certain nucleotide sequence
    count = 0
    oldcount = 0
    i = 0
    j = 0
    while i < len(helix):
        # keep counting STR while letters are the same
        if sequence[j] == helix[i]:
            j = j + 1
            i = i + 1
            count = count + 1
            if j >= len(sequence):
                j = 0
        else:
            # divide letters by wordcount to have amount of word occurrence
            newcount = int(count / len(sequence))
            # We should count this result as a possible STR and compare
            # it with the older STR, to see if it's longer.
            # And than store that value as the new maximum.
            if oldcount < newcount:
                oldcount = newcount
            # if partly recognized string contains part of string,
            # then we have to return for another check. We might have
            # missed a part of the string .. (ex. AGAGATC when looking for AGATC)
            # we might add a condition here. It's only necessary when count < len
            if count < len(sequence):
                i = i - count + 1
            # initialize count for a new STR
            count = 0
            # re-initialize j for a new cycle
            j = 0
    # if cycle ends with an STR we want to know
    if count > 0:
        newcount = int(count / len(sequence))
        if oldcount < newcount:
            oldcount = newcount
    # return longest STR
    return oldcount


def get_match(person, helix):
    # check if a helix matches the data of
    # a certain persons STR's. If not, break
    # out of loop immediately. Else keep comparing
    # and if nothing fails, return name.
    name = person.pop('name')
    for key in person:
        number = get_longest_STR(key, helix)
        if number != int(person[key]):
            return 1
            break
    return name


def main():
    for person in database:
        result = get_match(person, helix)
        # as soon as we get a winner, we can leave
        if result != 1:
            print(result)
            return
    # if after entire loop result is still 1,
    # than print No match
    if result == 1:
        print("No match")


main()

# close file
csv_file.close()
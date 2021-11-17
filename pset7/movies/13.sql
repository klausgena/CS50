SELECT DISTINCT people.name FROM people
INNER JOIN stars ON people.id = stars.person_id
INNER JOIN movies ON movies.id = stars.movie_id
WHERE NOT name="Kevin Bacon"
AND movies.id IN
(SELECT movies.id FROM movies
INNER JOIN stars ON stars.movie_id = movies.id
INNER JOIN people ON stars.person_id = people.id
WHERE name="Kevin Bacon" AND birth=1958);
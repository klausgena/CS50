SELECT name FROM people
INNER JOIN stars ON person_id = people.id
INNER JOIN movies ON movie_id = movies.id
WHERE title="Toy Story"
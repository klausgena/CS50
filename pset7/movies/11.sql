SELECT title FROM movies
INNER JOIN stars ON stars.movie_id = movies.id
INNER JOIN people ON stars.person_id = people.id
INNER JOIN ratings ON movies.id = ratings.movie_id
WHERE name="Chadwick Boseman"
ORDER BY rating DESC
LIMIT 5;
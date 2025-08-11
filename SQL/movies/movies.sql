SELECT title FROM movies WHERE year = 2008;

SELECT birth FROM people WHERE name = "Emma Stone";

SELECT title FROM movies WHERE year >= 2018 ORDER BY title;

SELECT count(movie_id) FROM ratings WHERE rating = 10.0;

SELECT title, movies.year FROM movies WHERE title LIKE 'Harry Potter%' ORDER BY year;

SELECT AVG(rating) FROM ratings WHERE movie_id in (SELECT id FROM movies WHERE year = 2012);

SELECT movies.title, ratings.rating FROM movies INNER JOIN ratings ON movies.id = ratings.movie_id AND movies.year = 2010 AND ratings.rating > 0 ORDER BY ratings.rating DESC, title ASC;

SELECT name FROM people WHERE id IN (SELECT person_id FROM stars WHERE movie_id IN(SELECT id FROM movies WHERE title = 'Toy Story'));

SELECT DISTINCT name FROM people WHERE id IN (SELECT person_id FROM stars WHERE movie_id IN (SELECT id FROM movies WHERE year = 2004)) ORDER BY people.birth;

SELECT DISTINCT name FROM people WHERE id IN (SELECT person_id FROM directors WHERE movie_id IN (SELECT movie_id FROM ratings WHERE rating >= 9.0));

SELECT m.title FROM movies m
JOIN stars s ON m.id = s.movie_id
JOIN people p ON s.person_id = p.id
JOIN ratings r ON m.id = r.movie_id
WHERE p.name = 'Chadwick Boseman'
ORDER BY r.rating DESC
LIMIT 5;

SELECT title FROM movies WHERE (id IN (SELECT movie_id FROM stars WHERE person_id IN (SELECT id FROM people WHERE name = 'Bradley Cooper'))) AND (id IN (SELECT movie_id FROM stars WHERE person_id IN (SELECT id FROM people WHERE name = 'Jennifer Lawrence')));

SELECT p.name FROM people p
JOIN stars s ON p.id = s.person_id
JOIN movies m ON s.movie_id = m.id
WHERE m.id IN (
    SELECT m.id FROM movies m
    JOIN stars s ON m.id = s.movie_id
    JOIN people p ON s.person_id = p.id
    WHERE p.name = 'Kevin Bacon' AND p.birth = 1958
)   AND p.name != 'Kevin Bacon';
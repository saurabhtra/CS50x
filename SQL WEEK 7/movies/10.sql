-- 10.sql, write a SQL query to list the names of all people who have directed a movie that received a rating of at least 9.0.
-- Your query should output a table with a single column for the name of each person.
-- If a person directed more than one movie that received a rating of at least 9.0, they should only appear in your results once.
SELECT people.name from people where people.id IN (
    select person_id from directors where movie_id IN (
        SELECT movie_id from ratings where rating >= 9.0
    )
);
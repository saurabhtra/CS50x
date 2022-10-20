--  write a SQL query to list the names of all people who starred in Toy Story.
-- Your query should output a table with a single column for the name of each person.
-- You may assume that there is only one movie in the database with the title Toy Story.
SELECT name from people where people.id IN (
    SELECT person_id from stars where movie_id  IN (SELECT movies.id from movies where title = "Toy Story")
);
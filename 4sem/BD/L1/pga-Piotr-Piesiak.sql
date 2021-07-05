-- Piotr Piesiak, grupa Paweł Garncarek, pga

-- Zadanie 1

SELECT name,count(DISTINCT island)
FROM Country JOIN geo_sea ON(country.code = geo_sea.country) LEFT JOIN islandin USING(sea)
GROUP BY country.name,country.code
ORDER BY count(DISTINCT island) DESC, name ASC;

-- Zadanie 2

SELECT POM.name, e.percentage
FROM (SELECT country.code, country.name
FROM Country JOIN EthnicGroup AS e ON(country.code = e.country)
WHERE country.code IN (SELECT country FROM EthnicGroup WHERE name = 'Polish')
GROUP BY country.name,country.code
HAVING count(DISTINCT e.name) >= 10) AS POM JOIN EthnicGroup AS e ON(POM.code = e.country)
WHERE e.name = 'Polish';

-- Zadanie 3

CREATE TEMP TABLE B AS (
(SELECT country2 AS a,country1 AS b FROM borders) UNION 
(SELECT country1 AS a,country2 AS b FROM borders));

WITH RECURSIVE Path(a,b) AS (
(SELECT a, b FROM B)
UNION (SELECT B.a, p.b FROM B JOIN Path p ON (B.b = p.a)))

SELECT DISTINCT country.*
FROM Path p JOIN Country ON(p.a = country.code)
WHERE p.b = 'PL'
ORDER BY country.name;

-- Zadanie 4

SELECT POM.name, ROUND(POM.pop*100/country.population) as per
FROM
(SELECT country.name, SUM(city.population) AS pop
FROM Country JOIN City ON (country.code = city.country)
GROUP BY country.name) AS POM JOIN Country ON(POM.name=country.name)
WHERE POM.pop*100/country.population > 75
ORDER BY per DESC;



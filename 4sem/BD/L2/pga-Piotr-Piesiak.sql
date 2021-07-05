-- Piotr Piesiak, grupa Paweł Garncarek, pga

-- Zadanie 1
CREATE VIEW Sea_airports(iatacode,name,city,province,country,sea) AS
SELECT iatacode, airport.name, airport.city, airport.province, airport.country,sea  FROM
airport JOIN city ON(airport.city = city.name AND airport.country = city.country AND airport.province = city.province) JOIN located ON(city.name = located.city AND located.country = city.country AND located.province = city.province) 
WHERE sea IS NOT NULL AND city.elevation > 200;

-- Zadanie 1 (ale powinno być 2)
ALTER TABLE city DROP CONSTRAINT citykey;

ALTER TABLE city ADD COLUMN id SERIAL;
ALTER TABLE city ADD CONSTRAINT pk_city
	PRIMARY KEY(id);
	
ALTER TABLE airport ADD COLUMN City_Id int;

UPDATE airport SET City_Id = c.id
	FROM city c JOIN airport a ON(c.name = a.city) WHERE a.city = airport.city;

ALTER TABLE airport ADD CONSTRAINT fk_airport
	FOREIGN KEY (City_Id) REFERENCES city(id) DEFERRABLE;
	
INSERT INTO airport(iatacode,name,country,city,province,latitude,longitude,
elevation, City_Id)
	SELECT 'IEG', 'Babimost', city.country, city.name, city.province,
 	city.latitude, city.longitude, city.elevation, city.id
	FROM city WHERE name = 'Zielona Góra';

-- Zadanie 3

INSERT INTO CountryPops(country, year, population) 
	SELECT country.code, extract(year FROM current_date), country.population 
	FROM country;

-- Zadanie 4

ALTER TABLE Country ADD COLUMN popPeakCount numeric;
ALTER TABLE Country ADD COLUMN popPeakYear numeric;

UPDATE Country SET popPeakCount =
	(SELECT max(population) FROM countrypops WHERE Country.code = 		countrypops.country);
UPDATE Country SET popPeakYear = 
	(SELECT min(year) FROM countrypops WHERE countrypops.population = 			Country.popPeakCount);



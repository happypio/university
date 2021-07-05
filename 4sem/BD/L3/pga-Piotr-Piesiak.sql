-- Piotr Piesiak, grupa Paweł Garncarek, pga

-- Zadanie 0
CREATE TABLE sunken_city (LIKE city);
ALTER TABLE sunken_city ADD COLUMN sinking_date date;

-- Zadanie 1
CREATE OR REPLACE FUNCTION sea_level(level int)
	RETURNS VOID
	AS $X$

	DECLARE c city;

	BEGIN
    	
    	DROP TABLE IF EXISTS saved_level;
    	CREATE TABLE saved_level(level INT);
    	INSERT INTO saved_level(level) VALUES(level);
    
    	DELETE FROM airport WHERE elevation < level;
    
    	FOR c IN SELECT * FROM city
    	LOOP
    		IF (c.elevation < level) AND EXISTS(SELECT city FROM city JOIN airport ON(city.name = airport.city AND city.country = airport.country) WHERE city.name = c.name AND city.country = c.country AND city.province = c.province AND city.latitude = c.latitude AND city.longitude = c.longitude AND city.elevation = c.elevation)
    		THEN
    			UPDATE airport SET city = NULL WHERE city = c.name AND country = c.country AND province = c.province;
    		END IF; 
    		IF (c.elevation < level)
    		THEN 
    			INSERT INTO sunken_city(name,country,province, population, latitude, longitude, elevation, sinking_date) 
    			VALUES(c.name, c.country, c.province, c.population, c.latitude, c.longitude, c.elevation, current_date);
    		END IF;
    		IF (c.elevation < level)
    		THEN
    			DELETE FROM city WHERE city.name = c.name AND city.country = c.country AND city.province = c.province AND city.latitude = c.latitude AND city.longitude = c.longitude AND city.elevation = c.elevation;
    		END IF;
    	END LOOP;
	END
$X$ LANGUAGE plpgsql;

--TESTY:
SELECT city.* FROM city WHERE elevation < 10; -- 321 rows
SELECT sea_level(10);
SELECT city.* FROM city WHERE elevation < 10; -- 0 rows
SELECT * FROM sunken_city; -- 321 rows;

--sprawdzmy jakie miasta maja lotniska polozone wyzej
SELECT airport.name, airport.city, city.elevation, airport.elevation
FROM city JOIN airport ON (city.name=airport.name);
WHERE (city.elevation < airport.elevation);

--sprawdzmy dla Palermo (city.elev = 14, airp.elev = 20)
SELECT sea_level(15);
SELECT city.name FROM city WHERE city.name = 'Palermo'; -- 0 rows
SELECT airport.* FROM airport WHERE airport.name = 'Palermo'; -- city = NULL

-- Zadanie 2
CREATE OR REPLACE FUNCTION check_ins_city()
	RETURNS TRIGGER AS $X$
	DECLARE l INT;
	BEGIN
		SELECT level INTO l FROM saved_level;
		IF (NEW.elevation >= l) THEN RETURN NEW;
		ELSE INSERT INTO sunken_city(name,country,province,population,latitude,
			longitude,elevation,sinking_date)
			VALUES(NEW.name,NEW.country,NEW.province,NEW.population,
			NEW.latitude,NEW.longitude,NEW.elevation,CURRENT_DATE); 
		END IF;
	RETURN NULL;
	END
	$X$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION check_upd_city()
	RETURNS TRIGGER AS $X$
	DECLARE l INT;
	BEGIN
		SELECT level INTO l FROM saved_level;
		IF (NEW.elevation >= l) THEN RETURN NEW;
		ELSE 
		DELETE FROM city WHERE name = OLD.name AND country = OLD.country AND province = OLD.province AND latitude = OLD.latitude AND longitude = OLD.longitude AND elevation = OLD.elevation;
		INSERT INTO sunken_city(name,country,province,population,latitude,
			longitude,elevation,sinking_date)
			VALUES(NEW.name,NEW.country,NEW.province,NEW.population,
			NEW.latitude,NEW.longitude,NEW.elevation,CURRENT_DATE); 
		END IF;
	RETURN NULL;
	END
	$X$ LANGUAGE plpgsql;
	
CREATE TRIGGER on_insert_to_city BEFORE INSERT ON city
FOR EACH ROW EXECUTE PROCEDURE check_ins_city();

CREATE TRIGGER on_update_to_city BEFORE UPDATE ON city
FOR EACH ROW EXECUTE PROCEDURE check_upd_city();


--TESTY:
INSERT INTO city(name,country,province,population,latitude,
			longitude,elevation)
			VALUES('raz','rr','raza',100,20,30,14); -- 0 insert, weszlo do sunkencity
			
INSERT INTO city(name,country,province,population,latitude,
			longitude,elevation)
			VALUES('dwa','dd','dwaa',100,20,30,16);
UPDATE city SET elevation = 14 WHERE name = 'dwa'; -- 0 update, usunelo z city i weszlo do sunken_city

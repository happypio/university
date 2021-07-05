-- Piotr Piesiak, grupa Paweł Garncarek, pga

-- Zadanie 1

CREATE VIEW temp AS
SELECT country1,country2,i1,i2 FROM (SELECT country1,country2,p1.independence as i1,p2.independence as i2 FROM borders JOIN Politics p1 ON(p1.country = country1) JOIN Politics p2 ON(p2.country = country2)
WHERE p1.independence IS NOT NULL AND p2.independence IS NOT NULL) AS pom 
WHERE extract(year FROM pom.i1) - extract(year FROM pom.i2) > 580 OR
	extract(year FROM pom.i2) - extract(year FROM pom.i1) > 580;


SELECT DISTINCT m.organization FROM isMember m JOIN temp ON(m.country = temp.country1)
WHERE temp.country2 IN (SELECT country FROM isMember WHERE isMember.organization = m.organization);

-- Zadanie 2
 
CREATE TABLE city_log (
    change_id serial PRIMARY KEY,
    type_of_change text,
    user_id text NOT NULL,
    change_date timestamp default current_timestamp,
    is_accepted boolean default true
);

-- Zadanie 3

CREATE OR REPLACE FUNCTION update_city_log()
    RETURNS TRIGGER AS $X$
    BEGIN
    INSERT INTO city_log(type_of_change, user_id, change_date, is_accepted) VALUES('update', current_user, current_date, true);
    RETURN NEW;
    END
    $X$ LANGUAGE plpgsql;
    

CREATE OR REPLACE FUNCTION insert_city_log()
    RETURNS TRIGGER AS $X$
    BEGIN
    INSERT INTO city_log(type_of_change, user_id, change_date, is_accepted) VALUES('insert', current_user, current_date, true);
    RETURN NEW;
    END
    $X$ LANGUAGE plpgsql;
    
CREATE OR REPLACE FUNCTION delete_city_log()
    RETURNS TRIGGER AS $X$
    BEGIN
    INSERT INTO city_log(type_of_change, user_id, change_date, is_accepted) VALUES('delete', current_user, current_date, true);
    RETURN OLD;
    END
    $X$ LANGUAGE plpgsql;

CREATE TRIGGER city_update BEFORE UPDATE ON city
FOR EACH ROW EXECUTE PROCEDURE update_city_log();

CREATE TRIGGER city_insert BEFORE INSERT ON city
FOR EACH ROW EXECUTE PROCEDURE insert_city_log();

CREATE TRIGGER city_delete BEFORE DELETE ON city
FOR EACH ROW EXECUTE PROCEDURE delete_city_log();

-- Zadanie 4

CREATE OR REPLACE FUNCTION insert_city_log()
RETURNS TRIGGER AS
$X$
BEGIN
    IF ((SELECT count(*) FROM (SELECT * FROM city_log ORDER BY change_id DESC LIMIT 10) AS pom WHERE user_id=current_user) < 10) THEN
        INSERT INTO city_log(type_of_change, user_id, change_date, is_accepted)
        VALUES ('insert', current_user, current_date, true);
        RETURN NEW;
    ELSE
        INSERT INTO city_log(type_of_change, user_id, change_date, is_accepted)
        VALUES ('insert', current_user, current_date, false);
        RETURN NULL;
    END IF;
END;
$X$
LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION update_city_log()
RETURNS TRIGGER AS
$X$
BEGIN
    IF ((SELECT count(*) FROM (SELECT * FROM city_log ORDER BY change_id DESC LIMIT 10) AS pom WHERE user_id=current_user) < 10) THEN
        INSERT INTO city_log(type_of_change, user_id, change_date, is_accepted)
        VALUES ('update', current_user, current_date, true);
        RETURN NEW;
    ELSE
        INSERT INTO city_log(type_of_change, user_id, change_date, is_accepted)
        VALUES ('update', current_user, current_date, false);
        RETURN NULL;
    END IF;
END;
$X$
LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION delete_city_log()
RETURNS TRIGGER AS
$X$
BEGIN
    IF ((SELECT count(*) FROM (SELECT * FROM city_log ORDER BY change_id DESC LIMIT 10) sub WHERE user_id=current_user) < 10) THEN
        INSERT INTO city_log(type_of_change, user_id, change_date, is_accepted)
        VALUES ('delete', current_user, current_date, true);
        RETURN OLD;
    ELSE
        INSERT INTO city_log(type_of_change, user_id, change_date, is_accepted)
        VALUES ('delete', current_user, current_date, false);
        RETURN NULL;
    END IF;
END;
$X$
LANGUAGE plpgsql;

-- DROP TRIGGER city_update ON city;
-- DROP TRIGGER city_insert ON city;
-- DROP TRIGGER city_delete ON city;

CREATE TRIGGER city_insert BEFORE INSERT ON city
FOR EACH ROW EXECUTE PROCEDURE insert_city_log();

CREATE TRIGGER on_city_update BEFORE UPDATE ON city
FOR EACH ROW EXECUTE PROCEDURE update_city_log();

CREATE TRIGGER city_delete BEFORE DELETE ON city
FOR EACH ROW EXECUTE PROCEDURE delete_city_log();

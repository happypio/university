-- Piotr Piesiak, grupa Paweł Garncarek, pga

-- Zadanie 1
SELECT DISTINCT City.*
FROM City JOIN Airport ON (City.name=Airport.city)
WHERE City.elevation < 100 AND City.country = 'PL'
ORDER BY City.name;

-- Zadanie 2

SELECT DISTINCT Sea.name, Sea.area
FROM Sea JOIN River ON (Sea.name=River.sea) JOIN geo_river ON (geo_river.river=River.name)
WHERE River.length > 800 AND geo_river.country = 'F'
ORDER BY Sea.area desc;

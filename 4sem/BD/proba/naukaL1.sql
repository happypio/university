(SELECT kod_uz,imie,nazwisko FROM 
uzytkownik JOIN grupa USING(kod_uz)
WHERE rodzaj_zajec = 'w') 
EXCEPT (SELECT kod_uz,imie,nazwisko FROM
uzytkownik JOIN grupa USING(kod_uz)
WHERE rodzaj_zajec = 's');

SELECT  DISTINCT A.kod_uz,A.imie,A.nazwisko FROM 
(SELECT kod_uz,imie,nazwisko FROM uzytkownik JOIN grupa USING(kod_uz)
WHERE rodzaj_zajec = 'w') A
LEFT JOIN (SELECT kod_uz FROM
uzytkownik JOIN grupa USING(kod_uz)
WHERE rodzaj_zajec = 's') B USING(kod_uz)
WHERE B.kod_uz IS NULL;

SELECT nazwa, COUNT(DISTINCT wybor.kod_uz)

FROM przedmiot JOIN przedmiot_semestr USING (kod_przed) JOIN grupa USING(kod_przed_sem) LEFT JOIN wybor USING (kod_grupy)

GROUP BY nazwa;

SELECT DISTINCT u.kod_uz, imie, nazwisko
FROM uzytkownik AS u JOIN grupa USING(kod_uz) JOIN wybor USING(kod_grupy)
GROUP BY u.kod_uz, imie, nazwisko, kod_grupy
HAVING count(*) > max_osoby;

SELECT DISTINCT u.kod_uz, imie, nazwisko
FROM uzytkownik AS u JOIN wybor USING(kod_uz) JOIN grupa USING(kod_grupy) JOIN przedmiot_semestr AS a USING(kod_przed_sem) JOIN przedmiot USING(kod_przed)
WHERE przedmiot.nazwa LIKE 'Algorytmy i struktury danych%' AND
a.semestr_id < ANY(SELECT semestr_id FROM uzytkownik JOIN wybor USING(kod_uz) JOIN grupa USING(kod_grupy) JOIN przedmiot_semestr USING(kod_przed_sem) JOIN przedmiot USING(kod_przed)
WHERE przedmiot.nazwa LIKE 'Matematyka dyskretna%' AND uzytkownik.kod_uz = u.kod_uz);

SELECT DISTINCT u.kod_uz, imie, nazwisko
FROM uzytkownik AS u JOIN wybor USING(kod_uz) JOIN grupa USING(kod_grupy) JOIN przedmiot_semestr AS a USING(kod_przed_sem) JOIN przedmiot USING(kod_przed)
WHERE przedmiot.nazwa LIKE 'Algorytmy i struktury danych%' AND
a.semestr_id < ANY(SELECT semestr_id FROM uzytkownik JOIN wybor USING(kod_uz) JOIN grupa USING(kod_grupy) JOIN przedmiot_semestr USING(kod_przed_sem) JOIN przedmiot USING(kod_przed)
WHERE przedmiot.nazwa LIKE 'Matematyka dyskretna%' AND uzytkownik.kod_uz = u.kod_uz);

SELECT DISTINCT p.nazwa, count(DISTINCT wybor.kod_uz) as a
FROM przedmiot AS p JOIN przedmiot_semestr USING(kod_przed) JOIN grupa USING(kod_przed_sem) JOIN wybor USING(kod_grupy)
WHERE p.rodzaj = 'p' AND grupa.rodzaj_zajec = 'w'
GROUP BY p.nazwa;

SELECT DISTINCT s.semestr_id, uzytkownik.nazwisko
FROM semestr AS s JOIN przedmiot_semestr USING(semestr_id) JOIN grupa USING(kod_przed_sem) JOIN wybor USING(kod_grupy) JOIN uzytkownik ON(uzytkownik.kod_uz = wybor.kod_uz)
WHERE s.nazwa LIKE '%letni%' AND wybor.data <= ALL(SELECT data FROM wybor JOIN grupa USING(kod_grupy) JOIN przedmiot_semestr USING(kod_przed_sem) JOIN semestr USING(semestr_id)
WHERE semestr_id = s.semestr_id);


SELECT Avg(POM.num)
FROM
(SELECT DISTINCT p.nazwa, count(DISTINCT wybor.kod_uz) as num
FROM przedmiot AS p JOIN przedmiot_semestr USING(kod_przed) JOIN semestr USING (semestr_id) JOIN grupa USING(kod_przed_sem) JOIN wybor USING(kod_grupy)

WHERE semestr.nazwa LIKE 'Semestr letni 2016/2017' AND grupa.rodzaj_zajec = 'w'
GROUP BY p.nazwa) as POM;

SELECT DISTINCT nazwisko
FROM uzytkownik JOIN grupa AS g USING(kod_uz) JOIN przedmiot_semestr USING(kod_przed_sem) JOIN przedmiot AS p USING(kod_przed) JOIN semestr AS s USING(semestr_id)
WHERE g.rodzaj_zajec = 'w' AND uzytkownik.kod_uz IN (SELECT kod_uz FROM uzytkownik JOIN grupa USING(kod_uz) JOIN przedmiot_semestr USING(kod_przed_sem) JOIN przedmiot USING(kod_przed) JOIN semestr USING(semestr_id)
WHERE grupa.kod_grupy != g.kod_grupy AND przedmiot.kod_przed = p.kod_przed AND s.semestr_id = semestr_id
GROUP BY kod_uz
HAVING count(DISTINCT grupa.kod_grupy) > 1);

grupa.rodzaj_zajec != 'w'

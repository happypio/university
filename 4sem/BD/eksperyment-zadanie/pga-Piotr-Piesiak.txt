--18, SP-GIST, box_ops, @> --Piotr Piesiak, 318000

--SP-GIST jest indeksem, który ułatwia przeszukiwania niezbalansowanych struktur.
--Najlepiej sprawdza się przy przeszukiwaniach, które dzielą przestrzeń 
--na różnego rozmiaru, nieprzecinające się części.
--box_ops @> - operator służący do porównania, czy dany obiekt
--w tym wypadku box zawiera jakiś obiekt geometryczny.

--tworzymy 1 000 000 losowych prostokątów
CREATE TABLE rectangles(b BOX);
INSERT INTO rectangles(b)
	SELECT box(point(random()*100, random()*100), point(random()*100, random()*100))
	FROM generate_series(1,1000000);
	
	
--zapytanie selektywne (kilkaset (okolo 300) krotek)
EXPLAIN ANALYZE SELECT b FROM rectangles WHERE b @> box '(1,1),(10,10)';

--wynik:
-- Gather  (cost=1000.00..13661.33 rows=1000 width=32) (actual time=0.506..57.841 rows=291 loops=1)
--   Workers Planned: 2
--   Workers Launched: 2
--   ->  Parallel Seq Scan on rectangles  (cost=0.00..12561.33 rows=417 width=32) (actual time=0.290..49.421 rows=97 loops=3)
--         Filter: (b @> '(10,10),(1,1)'::box)
--         Rows Removed by Filter: 333236
-- Planning Time: 0.095 ms
-- Execution Time: 57.915 ms
--(8 rows)

--zapytanie mało selektywne (około 1/4 miliona krotek)
EXPLAIN ANALYZE SELECT b FROM rectangles WHERE b @> point '(50,50)';

--wynik:
-- Gather  (cost=1000.00..13661.33 rows=1000 width=32) (actual time=0.459..52.451 rows=250220 loops=1)
--   Workers Planned: 2
--   Workers Launched: 2
--   ->  Parallel Seq Scan on rectangles  (cost=0.00..12561.33 rows=417 width=32) (actual time=0.014..28.674 rows=83407 loops=3)
--         Filter: (b @> '(50,50)'::point)
--         Rows Removed by Filter: 249927
-- Planning Time: 0.073 ms
-- Execution Time: 59.513 ms
--(8 rows)


CREATE INDEX ON rectangles USING SPGIST(b box_ops);
VACUUM ANALYZE rectangles;

--zapytanie selektywne
EXPLAIN ANALYZE SELECT b FROM rectangles WHERE b @> box '(1,1),(10,10)';

--wynik:
-- Index Only Scan using rectangles_b_idx on rectangles  (cost=0.29..49.78 rows=1000 width=32) (actual time=0.084..1.557 rows=291 loops=1)
--   Index Cond: (b @> '(10,10),(1,1)'::box)
--   Heap Fetches: 0
-- Planning Time: 0.089 ms
-- Execution Time: 1.620 ms
--(5 rows)


--zapytanie mało selektywne
set enable_seqscan=off;
EXPLAIN ANALYZE SELECT b FROM rectangles WHERE b @> point '(50,50)';
--wynik:
-- Index Only Scan using rectangles_b_idx on rectangles  (cost=0.29..47276.29 rows=1000 width=32) (actual time=2.225..142.492 rows=250220 loops=1)
--   Filter: (b @> '(50,50)'::point)
--   Rows Removed by Filter: 749780
--   Heap Fetches: 0
-- Planning Time: 0.098 ms
-- Execution Time: 148.044 ms
--(6 rows)
set enable_seqscan=on;

--WNIOSKI Z EKSPERYMENTU:
--Przeszukiwania z indeksem są o wiele szybsze jeśli chodzi o zapytania selektywne
--jest to różnica ~60ms do ~1.5ms, stąd wnioskuję, że indeks całkiem dobrze sobie radzi.
--Zapytania mało selektywne nie są już tak efektywne wykorzystując indeksy.
--PSQL domyślił się natury pytania i chciał wybrać równoległe skanowanie, które działa nieco szybciej.



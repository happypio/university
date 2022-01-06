#lang racket
;Praca grupowa: Marcin Badowski, Maurycy Borkowski, Filip Komorowski, Piotr Piesiak

(provide philosopher)

(define (run-concurrent . thunks)
  (define threads (map thread thunks))
  (for-each thread-wait threads))
(define (random-sleep)
  (sleep (/ (random) 100)))
(define (with-random-sleep proc)
  (lambda args
    (random-sleep)
    (apply proc args)))


(define (philosopher dining-table k)
  (let ([first  (if (= k 4) 0 k)]
        [second (if (= k 4) 4 (+ k 1))])
    (random-sleep)
    (begin

      (with-random-sleep ((dining-table 'pick-fork) first))

      (with-random-sleep ((dining-table 'pick-fork) second))

      (with-random-sleep ((dining-table 'put-fork) second))

      (with-random-sleep ((dining-table 'put-fork) first))

      )))


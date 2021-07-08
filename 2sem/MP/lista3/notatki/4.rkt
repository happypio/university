#lang racket

(define lista (list 1 2 4 5 6))
(define lista2 (list 2 5 6 7 8 2))

(define (insert xs n)
  (define (insert-pom pre suf)
    (if (null? suf)
        (append pre (list n))
        (if (< n (car suf))
           (append pre (list n) suf)
           (insert-pom (append pre (list (car suf))) (cdr suf)))))
  (insert-pom null xs))


(define (sortowanie lista)
  (define (sortowanie-pom sorted rest)
    (if (null? rest)
        sorted
        (sortowanie-pom (insert sorted (car rest)) (cdr rest))))
  (sortowanie-pom null lista))
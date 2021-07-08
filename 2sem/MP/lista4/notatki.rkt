#lang racket
(define lista (cons null (cons null (cons null null))))
(define (accumulate op initial sequence)
  (if (null? sequence)
  	initial
  	(op (car sequence)
            (accumulate op initial (cdr sequence)))))

(define (concatMap proc seq)
  (accumulate append null (map proc seq)))
(define pusta '())
(define pusta2 (append null null))
(define liscik1 (list '() '()))
(define liscik2 (list 5 4 3 2 1))
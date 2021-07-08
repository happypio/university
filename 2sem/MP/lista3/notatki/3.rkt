#lang racket
;(define (reverse lista)
  ;(if (null? lista)
  ;    null
 ;     (append (reverse-r (cdr lista)

(define lista (cons 1 (cons 2 (cons 4 null))))
(define tescik (list 1 2 3 4 5 6 7))

(define (reverse-r lista)
  (if (null? lista)
      null
      (append (reverse-r (cdr lista)) (list (car lista)))))

(define nulik (append null (list 1 2)))

(define (reverse-i lista)
  (define (iter l1 l-result)
    (if (null? l1)
        l-result
        (iter (cdr l1) (cons (car l1) l-result))))
  (iter lista null))


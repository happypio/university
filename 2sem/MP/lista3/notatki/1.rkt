#lang racket
(define (make-vect a b) (cons a b))
(define (vect-begin a) (car a))
(define (vect-end a) (cdr a))
(define (make-point a b) (cons a b))

(define (point x y)(cons x y))

(define (vect? x)
  (if (and (pair? (car x)) (pair? (cdr x)))
      1
      0))

(define (vect-length x)
  

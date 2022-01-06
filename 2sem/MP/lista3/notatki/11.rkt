#lang racket
(define xs (list 2 3 1))
(define ys (list 0 5 3))
(map (lambda (x) (* x x)) (append xs ys))
(filter natural? (append xs ys))
(filter natural? (list 420 69 9/11 -5))
(map (lambda (x y) (+ x (* 2 y)))
(list 1 2 3)
(list 4 5 6))

( define ( list? x )
(or ( null? x )
(and ( pair? x )
( list? ( cdr x ) ) ) ) )

(define przyklad (cons null (cons 1 null)))

(list? (map (lambda (x) (* x x)) (cons xs ys)))
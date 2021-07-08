#lang racket
; Posilkowalem sie kodem, ktory byl na wykladzie
(provide cube-root)
(define (cube-root x)
  (define (newton x y) (/ (+ x y) 3))
  (define (good-enough? guess)
    (define (szescian) (* guess guess guess))
    (< (abs (- x (szescian)))
       0.0001))
  (define (improve guess)
    (define (square) (* guess guess))
    (newton (/ x (square)) (* 2 guess)))
  (define (iter guess)
    (if (good-enough? guess)
        guess
        (iter (improve guess))))
  (if (= x 0)
      0
      (iter 1.0)))
    
    
#lang racket
(provide cont-frac)

(define (good-enough? now before)
  (< (abs (- now before))
      0.0001))

(define (cont-frac num den)
  (define (iter a1 a2 b1 b2 n before)
    (define an (+ (* (den n) a1)
                  (* (num n) a2)))
    (define bn (+ (* (den n) b1)
                  (* (num n) b2)))
    (define now (/ an bn))
    (if (good-enough? now before)
        now
        (iter an a1 bn b1 (+ n 1) now)))
    (iter 0 1 1 0 1 0))

(define (atan-cf x)
  (define num
    (lambda (n) (* (* n x) (* n x))))
  (define den
    (lambda (n) (+ (* 2.0 n) 1)))
  (/ x (+ 1 (cont-frac num den))))
  
; TESTY
;(atan-cf 8)
;(atan 8)

;(atan-cf -10)
;(atan -10)

;(atan-cf -12)
;(atan -12)

;(atan-cf 0)
;(atan 0)

;(atan-cf 3)
;(atan 3)

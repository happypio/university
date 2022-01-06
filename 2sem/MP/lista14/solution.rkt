#lang racket
;;PRACA GRUPOWA MARCIN BADOWSKI MAURYCY BORKOWSKI PIOTR PIESIAK
(require racklog)

(provide solve)

;; transpozycja tablicy zakodowanej jako lista list
(define (transpose xss)
  (cond [(null? xss) xss]
        ((null? (car xss)) (transpose (cdr xss)))
        [else (cons (map car xss)
                    (transpose (map cdr xss)))]))

;; procedura pomocnicza
;; tworzy listę n-elementową zawierającą wyniki n-krotnego
;; wywołania procedury f
(define (repeat-fn n f)
  (if (eq? 0 n) null
      (cons (f) (repeat-fn (- n 1) f))))

;; tworzy tablicę n na m elementów, zawierającą świeże
;; zmienne logiczne
(define (make-rect n m)
  (repeat-fn m (lambda () (repeat-fn n _))))
;; predykat binarny
;; (%row-ok xs ys) oznacza, że xs opisuje wiersz (lub kolumnę) ys



(define %row-ok
  (%rel (xs ys x zs y)
        [(null null)]
        [(xs (cons y ys))
         (%is y '_)
         (%row-ok xs ys)]
        [((cons x xs) ys)
         (%remove-block ys zs x)
         (%row-ok xs zs)]))


(define %remove-block
  (%rel (xs ys zs n m)
        [(null null 0)]
        [((cons '_ xs) (cons '_ xs) 0)]
        [((cons '* xs) ys n)
         (%remove-block xs ys m)
         (%is n (+ m 1))]
        ))



;(%which () (%block-length '(* * * _ _ *) 2))
;(%which () (%row-ok '(2 4) '(* * _ _ * * * * _ _)))
(define %rows-ok
  (%rel (x y xs ys)
        [(null null)]
        [((cons x xs) (cons y ys))
         (%row-ok x y)
         (%rows-ok xs ys)]))
;; funkcja rozwiązująca zagadkę
(define (solve rows cols)
  (define board (make-rect (length cols) (length rows)))
  (define tboard (transpose board))
  (define ret (%which (xss yss) 
                      (%= xss board)
                      (%rows-ok rows xss)
                      (%= yss tboard)
                      (%rows-ok cols yss)))
                      
  (and ret (cdar ret)))

;; testy
(equal? (solve '((2) (1) (1)) '((1 1) (2)))
        '((* *)
          (_ *)
          (* _)))

(equal? (solve '((2) (2 1) (1 1) (2)) '((2) (2 1) (1 1) (2)))
        '((_ * * _)
          (* * _ *)
          (* _ _ *)
          (_ * * _)))

#|(equal? (solve '((4) (6) (2 2) (2 2) (6) (4) (2) (2) (2))
               '((9) (9) (2 2) (2 2) (4) (4)))
        '((* * * * _ _)
          (* * * * * *)
          (* * _ _ * *)
          (* * _ _ * *)
          (* * * * * *)
          (* * * * _ _)
          (* * _ _ _ _)
          (* * _ _ _ _)
          (* * _ _ _ _)))
|#

;; TODO: możesz dodać własne testy

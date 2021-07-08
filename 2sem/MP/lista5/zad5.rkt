#lang racket
(define (eval-formula f val)
  (cond
    [(null? val) (error "Zmienna nie występuje w wartościowaniu")]
    [(and (var? f) (eq? f (car (first val)))) (cadr (first val))]
    [(var? f) (eval-formula f (cdr val))]
    [(neg? f) (not (eval-formula (neg-subf f) val))]
    [(conj? f) (and
                (eval-formula (conj-left f) val)
                (eval-formula (conj-rght f) val))]
    [(disj? f) (or
                (eval-formula (disj-left f) val)
                (eval-formula (disj-rght f) val))]))

(define (falsifiable-formula? f)
  (define (check-if-false vals)
    (if (null? vals)
        #f
        (if (eval-formula f (car vals)) 
            (check-if-false (cdr vals))
            (car vals))))
  (check-if-false (gen-vals (free-vars f))))
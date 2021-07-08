#lang racket
;Praca grupowa Filip Komorowski Marcin Badowski Maurycy Borkowski Piotr Piesiak
(require "props.rkt")
(provide falsifiable-cnf? convert-to-cnf convert-to-nnf clause? prop? free-vars gen-vals eval-formula literal? nnf?)


(define (prop? f)
   (or (var? f)
       (and (neg? f)
            (prop? (neg-subf f)))
       (and (disj? f)
            (prop? (disj-left f))
            (prop? (disj-right f)))
       (and (conj? f)
            (prop? (conj-left f))
            (prop? (conj-right f)))))

(define (free-vars f)
  (define vars
  (cond [(var? f) (list f)]
    	[(neg? f)  (free-vars (neg-subf f))]
    	[(disj? f) (append (free-vars (disj-left f)) (free-vars (disj-right f)))]
    	[(conj? f) (append (free-vars (conj-left f)) (free-vars (conj-right f)))]))
  (remove-duplicates vars))


(define (gen-vals xs )
   (if (null? xs )
       (list null )
       (let*
            ((vss (gen-vals (cdr xs ) ) )
             (x (car xs ) )
             (vst (map (lambda (vs ) (cons (list x true ) vs) ) vss))
             (vsf (map (lambda (vs ) (cons (list x false ) vs) ) vss)))
          (append vst vsf ) ) ) )


(define (eval-formula f val)
  (cond
    [(null? val) (error "Zmienna nie występuje w wartościowaniu")]
    [(and (var? f) (eq? f (car (first val)))) (cadr (first val))]
    [(var? f) (eval-formula f (cdr val))]
    [(neg? f) (not (eval-formula (neg-subf f) val))]
    [(conj? f) (and
                (eval-formula (conj-left f) val)
                (eval-formula (conj-right f) val))]
    [(disj? f) (or
                (eval-formula (disj-left f) val)
                (eval-formula (disj-right f) val))]))

(define (falsifiable-formula? f)
  (define (check-if-false vals)
    (if (null? vals)
        #f
        (if (eval-formula f (car vals)) 
            (check-if-false (cdr vals))
            (car vals))))
  (check-if-false (gen-vals (free-vars f))))

(define (literal? f)
  (or (var? f)
      (and (neg? f) (var? (neg-subf f)))))

(define (nnf? f)
  (or
   (literal? f)
   (and (conj? f)
        (nnf? (conj-left f))
        (nnf? (conj-right f)))
   (and (disj? f)
        (nnf? (disj-left f))
        (nnf? (disj-right f)))))

(define (convert-to-nnf f)
  (define (convert-neg g)
    (cond [(var? g) (neg g)]
          [(neg? g) (convert-to-nnf (neg-subf g))]
          [(conj? g) (disj (convert-neg (conj-left g))
                           (convert-neg (conj-right g)))]
          [(disj? g) (conj (convert-neg (disj-left g))
                           (convert-neg (disj-right g)))]))
  (cond [(var? f) f]
        [(neg? f) (convert-neg (neg-subf f))]
        [(conj? f) (conj (convert-to-nnf (conj-left f))
                         (convert-to-nnf (conj-right f)))]
        [(disj? f) (disj (convert-to-nnf (disj-left f))
                         (convert-to-nnf (disj-right f)))]))
(define (clause? x)
  (cond [(conj? x) #f]
        [(literal? x) #t]
        [else (and (clause? (disj-left x)) (clause? (disj-right x)))]))


(define (cnf? x)
   (and (list? x)
         (andmap clause? x)))

(define (convert-to-cnf f)
  (cond [(clause? f) f]
        [(conj? f) (conj (convert-to-cnf (conj-left f))
                         (convert-to-cnf (conj-right f)))]
        [(disj? f) (cond [(conj? (disj-right f))
                          (conj
                           (convert-to-cnf (disj
                                            (convert-to-cnf (disj-left f))
                                            (convert-to-cnf (conj-left (disj-right f)))))
                           (convert-to-cnf (disj
                                            (convert-to-cnf (disj-left f))
                                            (convert-to-cnf (conj-right (disj-right f))))))]
                         [(conj? (disj-left f))
                          (conj
                           (convert-to-cnf (disj
                                            (convert-to-cnf (conj-left (disj-left f)))
                                            (convert-to-cnf (disj-right f))))
                           (convert-to-cnf (disj
                                            (convert-to-cnf (conj-right (disj-left f)))
                                            (convert-to-cnf (disj-right f)))))]
                         [(or (disj? (disj-left f)) (disj? (disj-right f)))
                          (convert-to-cnf (disj (convert-to-cnf (disj-right f)) (convert-to-cnf (disj-left f))))])]))

(define (eval-cnf f val)
  (define (eval-clause c val)
    (cond
    [(null? val) (error "lipa")]
    [(and (var? c) (eq? c (car (first val)))) (cadr (first val))]
    [(var? c) (eval-clause c (cdr val))]
    [(neg? c) (not (eval-clause (neg-subf c) val))]
    [(disj? c) (or
                (eval-clause (disj-left c) val)
                (eval-clause (disj-right c) val))]))
  (cond
    [(clause? f) (eval-clause f val)]
    [(conj? f)(and
               (eval-cnf (conj-left f) val)
               (eval-cnf (conj-right f) val))]))


(define (falsifiable-cnf? f)
  (define cnf (convert-to-cnf (convert-to-nnf f)))
     	(define (check-if-false vals clause)
       	(if (null? vals)
           	#f
           	(if (eval-cnf clause (car vals))
               	(check-if-false (cdr vals) clause)
               	(car vals))))
  (if (clause? cnf)
  	(check-if-false (gen-vals (free-vars cnf)) cnf)
  	(or (falsifiable-cnf? (conj-left cnf)) (falsifiable-cnf? (conj-right cnf)))))


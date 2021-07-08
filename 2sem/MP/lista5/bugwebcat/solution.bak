#lang racket
;(require "props.rkt")
(provide falsifiable-cnf?)
(provide tautol?)
(provide check)
(provide eval-cnf)
(provide convert-to-cnf)
(provide clause?)
(provide convert-to-nnf)
(provide nnf?)
(provide literal?)
(provide falsifiable-formula?)
(provide eval-formula)
(provide gen-vals)
(provide free-vars)
(provide prop?)
(provide disj-right)
(provide disj-left)
(provide conj-right)
(provide conj-left)
(provide neg-subf)
(provide disj)
(provide conj)
(provide neg)
(provide disj?)
(provide conj?)
(provide neg?)
(provide var?)
( define ( var? t )
   ( symbol? t ) )
( define ( neg? t )
   ( and ( list? t )
         (= 2 ( length t ) )
         ( eq? 'neg ( car t ) ) ) )
( define ( conj? t )
   ( and ( list? t )
         (= 3 ( length t ) )
         ( eq? 'conj ( car t ) ) ) )
( define ( disj? t )
   ( and ( list? t )
         (= 3 ( length t ) )
         ( eq? 'disj ( car t ) ) ) )

(define (neg f)
  (list 'neg f))

(define (conj f1 f2)
  (list 'conj f1 f2))

(define (disj f1 f2)
  (list 'disj f1 f2))

(define (neg-subf f)
  (second f))

(define (conj-left f)
  (second f))

(define (conj-right f)
  (third f))

(define (disj-left f)
  (second f))

(define (disj-right f)
  (third f))

( define ( prop? f )
   (or ( var? f )
       (and ( neg? f )
            ( prop? ( neg-subf f ) ) )
       (and ( disj? f )
            ( prop? ( disj-left f ) )
            ( prop? ( disj-right f ) ) )
       (and ( conj? f )
            ( prop? ( conj-left f ) )
            ( prop? ( conj-right f ) ) ) ) )

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
                  



;(define lol (disj (neg 'm) (conj 'p 'q)))
;(define k (convert-to-nnf '(neg (disj (neg p) (conj q r)))))
;(define tescior (conj (disj 'p 'q) (conj (neg 'p) (disj (neg 'q) 'r))))
;(define tescior2 (disj (disj 'p (conj 'p 'r)) (disj 'q 's)))
;(define test (disj (conj 'p 'm) (conj 'r 'q)))
;(define f (disj (conj 'p 'm) 'r))
;(define f1 (disj 'r (conj 'p 'm)))
;(define czyzby (disj 'p (conj 'p 'r)))

;(define czyzby2 (disj (conj (disj 'p 'p) (disj 'p 'r)) (disj 'p 's)))


(define (eval-cnf f val)
  (define (eval-clause c val)
    (cond
    [(null? val) (error "CHWDP")]
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

(define (check val list)
  (if (null? list)
      #f
      (if (eq? val (car (first list)))
          #t
          (check val (cdr list)))))

(define (tautol? vals)
  (if (null? vals)
      #f
      (if (check (car (first vals)) (cdr vals))
          #t
          (tautol? (cdr vals)))))


(define (falsifiable-cnf? f)
  (define cnf (convert-to-cnf (convert-to-nnf f)))
  (define (falsifiable-clause c)
    (cond
      [(var? c) (list (cons c #f))]
      [(neg? c) (list (cons (neg-subf c) #t))]
      [(disj? c) (append (falsifiable-clause (disj-left c)) (falsifiable-clause (disj-right c)))]))
  (define (falsifiable-clause-pom cnfik)
    (cond
      [(clause? cnfik)
       (define clause (remove-duplicates (falsifiable-clause cnfik)))
       (cond
         [(tautol? clause) #f]
         [else clause])]
      [else
       (define left (falsifiable-clause-pom (conj-left cnfik)))
       (if (list? left)
           left
           (falsifiable-clause-pom (conj-right cnfik)))]))
  (falsifiable-clause-pom cnf))

(define lol (disj (neg 'm) (conj 'p 'q)))
(define k (convert-to-nnf '(neg (disj (neg p) (conj q r)))))
(define tescior (conj (disj 'p 'q) (conj (neg 'p) (disj (neg 'q) 'r))))
(define tescior2 (disj (disj 'p (conj 'p 'r)) (disj 'q 's)))
(define test (disj (conj 'p 'm) (conj 'r 'q)))
(define f (disj (conj 'p 'm) 'r))
(define f1 (disj 'r (conj 'p 'm)))
(define czyzby (disj 'p (conj 'p 'r)))
(define czyzby2 (disj (conj (disj 'p 'p) (disj 'p 'r)) (disj 'p 's)))

(define tescior3 (disj 'p (neg 'p)))
(define tescior4 (conj (disj 'q (disj 'p (disj (neg 'p) (neg 'q)))) (disj 'r (neg 'r))))



;(display "Test dla formuly: ")(display lol)(display " po przeksztalceniu: ")(falsifiable-cnf? lol)
;(display "Test dla formuly: ")(display k)(display " po przeksztalceniu: ")(falsifiable-cnf? k)
;(display "Test dla formuly: ")(display tescior)(display " po przeksztalceniu: ")(falsifiable-cnf? tescior)
;(display "Test dla formuly: ")(display tescior2)(display " po przeksztalceniu: ")(falsifiable-cnf? tescior2)
;(display "Test dla formuly: ")(display test)(display " po przeksztalceniu: ")(falsifiable-cnf? test)
;(display "Test dla formuly: ")(display f)(display " po przeksztalceniu: ")(falsifiable-cnf? f)
;(display "Test dla formuly: ")(display f1)(display " po przeksztalceniu: ")(falsifiable-cnf? f1)
;(display "Test dla formuly: ")(display czyzby)(display " po przeksztalceniu: ")(falsifiable-cnf? czyzby)
;(display "Test dla formuly: ")(display tescior3)(display " po przeksztalceniu: ")(falsifiable-cnf? tescior3)
;(display "Test dla formuly: ")(display tescior4)(display " po przeksztalceniu: ")(falsifiable-cnf? tescior4)

(display "Test dla formuly: ")(display lol)(display " po przeksztalceniu: ")(falsifiable-formula? lol)
(display "Test dla formuly: ")(display k)(display " po przeksztalceniu: ")(falsifiable-formula? k)
(display "Test dla formuly: ")(display tescior)(display " po przeksztalceniu: ")(falsifiable-formula? tescior)
(display "Test dla formuly: ")(display tescior2)(display " po przeksztalceniu: ")(falsifiable-formula? tescior2)
(display "Test dla formuly: ")(display test)(display " po przeksztalceniu: ")(falsifiable-formula? test)
(display "Test dla formuly: ")(display f)(display " po przeksztalceniu: ")(falsifiable-formula? f)
(display "Test dla formuly: ")(display f1)(display " po przeksztalceniu: ")(falsifiable-formula? f1)
(display "Test dla formuly: ")(display czyzby)(display " po przeksztalceniu: ")(falsifiable-formula? czyzby)
(display "Test dla formuly: ")(display tescior3)(display " po przeksztalceniu: ")(falsifiable-formula? tescior3)
(display "Test dla formuly: ")(display tescior4)(display " po przeksztalceniu: ")(falsifiable-formula? tescior4)






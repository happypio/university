#lang racket
( struct const ( val )  #:transparent )
( struct binop ( op l r ) #:transparent )
( define ( eval e )
   ( match e
      [( const n ) n ]
      [( binop op l r ) (( op->proc op ) ( eval l ) ( eval r ) ) ]) )
( define ( op->proc op )
   ( match op ['+ +] ['- -] ['* *] ['/ /]) )
(define (cont-frac-expr num den k)
  (define (go acc i)
    (if (= i 0)
        acc
        (go (binop '/ (const (num i)) (binop '+ (const (den i)) acc)) (- i 1))))
  (go (const 0) k))

(define (pi-expr k)
  (binop '+
         (const 3.0)
         (cont-frac-expr
          (lambda (n) (sqr (- (* 2 n) 1)))
          (lambda _ 6)
          k)))
(define 2+2*2 (binop '+ (const 2)
                     (binop '* (const 2)
                            (const 2))))
(eval 2+2*2)
(define 2+2+2 (binop '+ (const 2)
                     (binop '+ (const 2)
                            (const 2))))

(eval 2+2+2)

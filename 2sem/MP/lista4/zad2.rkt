#lang racket
;z2
(define (accumulate op initial sequence)
  (if (null? sequence)
  	initial
  	(op (car sequence)
      	(accumulate op initial (cdr sequence)))))

(define (concatMap proc seq)
  (accumulate append null (map proc seq)))

(define (from-to low high)
  (if (> low high)
  	null
  	(cons low (from-to (+ 1 low) high))))

(define(safe? k positions)
  (define bad-row (cdr (car positions)))
  (define (iter-pom rest act)
    (if (null? rest)
        #t
        (cond
          ((= (cdr (car rest)) bad-row) #f)
          ((= (abs (- bad-row (cdr (car rest)))) act) #f)
          (else (iter-pom (cdr rest) (+ 1 act))))))
  (iter-pom (cdr positions) 1))
  






(define(queens  board-size)
  (define (empty-board) null)
  
  (define (adjoin-position  row  col  rest)
    (cons (cons col row) rest))
  
  (define(queen-cols k)
    (if(= k 0)
       (list (empty-board))
       (filter
        (lambda (positions) (safe? k positions))
        ( concatMap
          ( lambda ( new-row )
             ( map ( lambda ( rest-of-queens )
                      ( adjoin-position new-row k rest-of-queens ) )
                   ( queen-cols (- k 1) ) ) )
          ( from-to 1 board-size ) ))))
  (queen-cols  board-size))
(queens 4)
(define lista (list 1 2 3 4 5))
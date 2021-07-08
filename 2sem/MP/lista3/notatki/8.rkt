#lang racket

(define lista (list 1 5 6 2 235 250 0 9 2 2 1))

(define (merge lista1 lista2)
  (define (merge-helper l1 l2 result)
    (cond
      ((and (null? l1) (null? l2))
            result)
       ((null? l1)
        (merge-helper l1 null (append result l2)))
       ((null? l2)
        (merge-helper null l2 (append result l1)))
       ((<= (car l1) (car l2))
        (merge-helper (cdr l1) l2 (append result (list (car l1)))))
       (else
        (merge-helper l1 (cdr l2) (append result (list (car l2)))))))
  (merge-helper lista1 lista2 null))

(define (partition n xs)
  (define (pom lista small big)
	(if (null? lista)
    	(cons small big)
    	(if (<= (car lista) n)
        	(pom (cdr lista) (append small (list (car lista))) big)
        	(pom (cdr lista) small (append big (list (car lista)))))))
  (pom xs null null))

(define (quicksort l)
  (if (null? l)
  	l
  	(if (null? (cdr l))
      	l
      	(append (append (quicksort (car (partition (car l) (cdr l)))) (list (car l))) (quicksort (cdr (partition (car l) (cdr l))))))))


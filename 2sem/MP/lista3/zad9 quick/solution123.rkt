#lang racket
;Praca grupowa
;Maurycy Borkowski, Filip Komorowski, Pior Piesiak, Marcin Badowski
(provide partition quicksort)

(define unsorted (list 1 -10 21 69 2 0 1))

(define (length items)
  (if (null? items)
      0
      (+ 1 (length (cdr items)))))

;9
(define (partition n xs)
  (define (iter small big L)
    (if (null? L)
        (cons small big)
        (if (<= (car L) n)
            (iter (append small (list (car L))) big (cdr L))
            (iter small (append  big (list (car L))) (cdr L)))))
  (iter null null xs))

(partition 10 unsorted)

(define (quicksort L)
  (if (null? L)
      L
      (append
       (append
        (quicksort (car (partition (car L) (cdr L)))) (list (car L)))
       (quicksort (cdr (partition (car L) (cdr L)))))))

(quicksort unsorted)

        
  
  

  
       
             
      

  





#lang racket
(define (btree? t)
  (or (eq? t 'leaf)
      (and(list? t)
          (= 4 (length t))
          (eq? (car t) 'node)
          (btree? (caddr t))
          (btree? (cadddr t)))))

(define (mirror tree)
  (if (eq? tree 'leaf)
      tree
      (list (car tree) (cadr tree) (mirror (cadddr tree))  (mirror (caddr tree)))))
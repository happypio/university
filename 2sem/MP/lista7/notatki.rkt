#lang racket
(struct node (data l r) #:transparent)
(if (if (> 3 2)
    (list 1 2)
    #f)
    2
    #f)
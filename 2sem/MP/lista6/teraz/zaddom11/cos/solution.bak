#lang racket

(provide (struct-out const) (struct-out binop) rpn->arith)

(struct stack (xs))

(define empty-stack (stack null))
(define (empty-stack? s) (null? (stack-xs s)))
(define (top s) (car (stack-xs s)))
(define (push a s) (stack (cons a (stack-xs s))))
(define (pop s) (stack (cdr (stack-xs s))))

(define (rpn-expr? e)
  (and (list? e)
       (pair? e)
       (andmap (lambda (x) (or (number? x) (member x '(+ - * /))))
               e)))


(struct const (val)    #:transparent)
(struct binop (op l r) #:transparent)

(define (arith-expr? e)
  (match e
    [(const n) (number? n)]
    [(binop op l r)
     (and (symbol? op) (arith-expr? l) (arith-expr? r))]
    [_ false]))


(define (rpn->arith e)
  (define (rpn-iter e stack)
    (cond
      [(null? e) (top stack)]
        [(number? (car e)) (rpn-iter (cdr e) (push (const (car e)) stack))]
        [(symbol? (car e)) (let ([x (car e)] [a (top stack)] [b (top (pop stack))])
                                        (let ([binopik (binop x a b)])
                                          (rpn-iter (cdr e) (push binopik (pop (pop stack))))))]))
  (rpn-iter e empty-stack))
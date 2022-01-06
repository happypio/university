#lang racket
;PRACA GRUPOWA PIOTR PIESIAK MARCIN BADOWSKI MAURYCY BORKOWSKI FILIP KOMOROWSKI
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

(define (rpn->arith e_rpn)
  (define (rpn->arith-it e stos)
	(cond
  	[(null? e) (top stos)]
  	[(number? (car e)) (rpn->arith-it (cdr e) (push (const (car e)) stos))]
  	[(symbol? (car e)) (let* ([r (top stos)]
                  	[l (top (pop stos))]
                  	[expr (binop (car e) l r)])
                  	(rpn->arith-it (cdr e) (push expr (pop (pop stos)))))]))
  (rpn->arith-it e_rpn empty-stack))



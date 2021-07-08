#lang racket
;Praca grupowa Marcin Badowski, Maurycy Borkowski, Piotr Piesiak, Filip Komorowski

(provide (struct-out const) (struct-out binop) (struct-out var-expr) (struct-out let-expr) (struct-out pos) (struct-out var-free) (struct-out var-bound) annotate-expression)


(struct pos (file line col)     #:transparent)  
(struct const    (val)          #:transparent)
(struct binop    (op l r)       #:transparent)
(struct var-expr (id)           #:transparent)
(struct let-expr (loc id e1 e2) #:transparent)
; -------------
; Wolne zmienne
; -------------


( struct environ ( xs ) )
( define env-empty ( environ null ) )
( define ( env-add x v env )
   ( environ ( cons ( cons x v ) ( environ-xs env ) ) ) )
( define ( env-lookup x env )
   ( define ( assoc-lookup xs )
      ( cond [( null? xs ) #f ]
             [( eq? x ( car ( car xs ) ) ) ( cdr ( car xs ) ) ]
             [ else ( assoc-lookup ( cdr xs ) ) ]) )
   ( assoc-lookup ( environ-xs env ) ) )


(define (free-vars-env e env)
  (match e
    [(const n) (set)]
    [(binop op l r)
     (set-union (free-vars-env l env)
                (free-vars-env r env))]
    [(let-expr loc x e1 e2)
     (set-union (free-vars-env e1 env)
                (free-vars-env e2 (env-add x env)))]
    [(var-expr x)
     (if (env-lookup x env)
         (set) (list->set (list x)))]))

(define (free-vars e)
  (set->list (free-vars-env e env-empty)))

(define (test-free-vars)
  (free-vars (parse
    '(let [x (+ 2 y)]
       (let [z (+ z x)] ; tu zmienna z jest wolna!
         z)))))


;; ---------------
;; Jezyk wejsciowy
;; ---------------


(define (expr? e)
  (match e
    [(const n)      (number? n)]
    [(binop op l r) (and (symbol? op) (expr? l) (expr? r))]
    [(var-expr x)   (symbol? x)]
    [(let-expr loc x e1 e2)
     (and (pos? loc) (symbol? x) (expr? e1) (expr? e2))]
    [_ false]))

(define (make-pos s)
  (pos (syntax-source s)
       (syntax-line   s)
       (syntax-column s)))

(define (parse e)
  (let ([r (syntax-e e)])
    (cond
      [(number? r) (const r)]
      [(symbol? r) (var-expr r)]
      [(and (list? r) (= 3 (length r)))
       (match (syntax-e (car r))
         ['let (let* ([e-def (syntax-e (second r))]
                      [x     (syntax-e (first e-def))])
                 (let-expr (make-pos (first e-def))
                           (if (symbol? x) x (error "parse error!"))
                           (parse (second e-def))
                           (parse (third r))))]
         [op   (binop op (parse (second r)) (parse (third r)))])]
      [else (error "parse error!")])))

;; ---------------
;; Jezyk wyjsciowy
;; ---------------

(struct var-free  (id)     #:transparent)
(struct var-bound (pos id) #:transparent)

(define (expr-annot? e)
  (match e
    [(const n)         (number? n)]
    [(binop op l r)    (and (symbol? op) (expr-annot? l) (expr-annot? r))]
    [(var-free x)      (symbol? x)]
    [(var-bound loc x) (and (pos? loc) (symbol? x))]
    [(let-expr loc x e1 e2)
     (and (pos? loc) (symbol? x) (expr-annot? e1) (expr-annot? e2))]
    [_ false]))

(define (annotate-expression e)
  (define (iter env expr)
    (match expr
      [(const expr) (const expr)]
      [(binop op l r) (binop op (iter env l) (iter env r))]
      [(var-expr expr)
       (define lookup (env-lookup expr env))
       (if lookup
           (var-bound lookup expr)
           (var-free expr))]
      [(let-expr loc x e1 e2) (let-expr loc x (iter env e1) (iter (env-add x loc env) e2))]))
  (iter env-empty e))

                      
;(display "parse\n")
;(parse #'(let [x 5] (* y x)))
(display "annotate\n")
(annotate-expression (parse #'(let [x 5] (let [x 3] (* y x)))))


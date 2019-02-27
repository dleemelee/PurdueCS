; Evalutes x+y
(define (add x y) 
  (ifz y x                       ; if y==0, x+y=x
      (add (inc x) (dec y))))   ; otherwise x+y = (x+1) + (y-1)

(define (sub x y) 
  (ifz y x                      ; if y==0, x-y = x
       (ifz x (halt)            ; else if x==0, we halt because the result is negative
            (sub (dec x) (dec y)))))  ; else x-y = (x-1) - (y-1)


; Evaluets x * y
(define (mul x y)
  (ifz y 0                       ; if y==0, x*y=0
      (add (mul x (dec y)) x))) ; esle x*y = x + x*(y-1)

; Evaluates to 0 if x == y, and 1 otherwise
(define (eq x y)
  (ifz y 
    (ifz x 0 1) (ifz x
        (ifz y 0 1) (eq (dec x) (dec y)))))


; Evaluates to 0 if x < y, and 1 otherwise
(define (lt x y)
 (ifz y 1                       ; if y==0, x<y cannot be true, evaluates to 1
      (ifz x 0                  ; else if x==0, it must be x<y, evaluates to 0 
           (lt (dec x) (dec y))))) ; else x<y if and only if x-1 < y-1

; Evaluates least common multiple of x and y
(define (lcm x y)
  (ifz (eq x y) x
    (ifz (lt x y) (lcms x y (add x x) y)
        (lcms x y x (add y y)))))

(define (lcms v w x y)
  (ifz (eq x y) x
    (ifz (lt x y) (lcms v w (add v x) y)
        (lcms v w x (add y w)))))

(define (square x)
  (mul x x))

(define (sroots x y)
  (ifz (eq (square x) y) x
    (ifz (lt y (square x)) x
        (sroots (inc x) y))))

;Evaluates largest possible integer y, where y^2 = z
(define (sroot y)
  (ifz y 0 
    (ifz (eq (square 1) y) 1
        (sroots 2 y))))

(define (rem x y)
  (ifz y (halt)                  ; Division by 0
       (ifz (lt x y) x           ; if x<y, x mod y = x
            (rem (sub x y) y)))) ; else x mod y = (x-y) mod y

(define (minvs x y z)
  (ifz (eq (rem (mul x y) z) 1) y
    (minvs x (inc y) z)))

; Evaluates the smallest possible integer y such that xy % z = 1
(define (minv x z)
  (ifz (eq (rem x z) 1) 1
    (minvs x 2 z)))


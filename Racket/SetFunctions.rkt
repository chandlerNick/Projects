#lang racket

;Membership
;Determines if x is a member of L
;Input: an element x and a list L
;Output: true if x is a member of L, false otherwise
(define (member? x L)
  (cond
    [(null? L) #f]
    ;is it a list?
    ;[(and (list? x) (list? (car L)) (not(set-equal? x (car L)))) #f];error is here!
    [(and (list? x) (list? (car L)) (set-equal? x (car L))) #t]
    [(eq? x (car L)) #t]
    [else (member? x (cdr L))]))

;Subset
;Determines if L1 is a subset of L2
;Input: 2 lists, L1 and L2
;Output: true if L1 is a subset of L2, false otherwise
(define (subset? L1 L2)
  (cond
    [(eq? L1 L2) #t]
    [(eq? L1 '()) #t]
    [(> (length L1) (length L2)) #f]
    [(not(member? (car L1) L2)) #f]
    [else (subset? (cdr L1) L2)]))

;Set Equivalence
;Determines set equivalence
;Input: 2 lists L1 and L2
;Output: true if L1 is equal to L2, false otherwise
;Example (set-equal? '(1) '(3)) => #f
(define (set-equal? L1 L2)
  (cond
    [(eq? L1 L2) #t]
    [(not(eq? (length L1) (length L2))) #f]
    [(and (subset? L1 L2) (subset? L2 L1)) #t]
    [else #f]))

#|
Bag Difference
Takes difference of two bag objects
Input: Two bag objects (unordered lists)
Output: A list containing the elements of the first minus the second
|#

(define (bag-difference L1 L2)
  (cond
    [(empty? L1) '()]
    [(empty? L2) L1]
    [(member? (car L2) L1) (bag-difference (remove(car L2) L1) (cdr L2))]
    [else (bag-difference L1 (cdr L2))]))

#|Passes these tests
(display "bag-difference\n")
(bag-difference '(a a b a) '(b a a))
(bag-difference '(a b a a) '(a b c))
(bag-difference '(a b c) '(a b a a)) 
(bag-difference '(a b c) '(a b c))
(bag-difference '() '(a b a a))
(bag-difference '(a b a a) '())
|#

#|
bag-union
Contains the maximum number of elements of each bag
eg.) '(a a a b) '(a b) -> '(a a a b)
Input: Two bags to be "united"
Output: One bag with the maximum number of any shared element
|#

(define bag-union
  (lambda (L1 L2)
    (if (> (length L1) (length L2))
        (bag-un L1 L2 L1)
        (bag-un L2 L1 L2))))

#|Helper method for above, refer to doc there|#
(define (bag-un L1 L2 L3)
  (cond
    [(empty? L1) L3]
    [(empty? L2) L3]
    [(set-equal? L1 L2) L1]
    [(member? (car L2) L1) (bag-un L1 (cdr L2) L3)]
    [else (bag-un L1 (cdr L2) (cons (car L2) L3))]))

#| Passes these tests
(display "bag-union\n")
(bag-union '(a a b a) '(b a a))
(bag-union '(a b a a) '(a b c)) 
(bag-union '(a b c) '(a b a a))
(bag-union '(a b c) '(a b c))
(bag-union '() '(a b a a))
(bag-union '(a b a a) '())
|#

#|
bag-intersection
Contains the intersection with the min number of elements from each
Inputs: two bags
Outputs: one bag intersection
'(a b c c) '(a b c) -> '(c c)
|#
(define bag-intersection
  (lambda (L1 L2)
    (if (> (length L1) (length L2))
        (bag-in L1 L2 '())
        (bag-in L2 L1 '()))))

#|Helper method for above function, refer to doc there|#
(define (bag-in L1 L2 L3) 
  (cond
    [(empty? L1) L3]
    [(empty? L2) L3]
    [(set-equal? L1 L2) L1]
    [(member? (car L2) L1) (bag-in L1 (cdr L2) (cons (car L2) L3))]
    [else (bag-in L1 (cdr L2) L3)]))


#|Passes these tests
(display "bag-intersection\n")
(bag-intersection '(a a b a) '(b a a))
(bag-intersection '(a b a a) '(a b c))
(bag-intersection '(a b c) '(a b a a))
(bag-intersection '(a b c) '(a b c))
(bag-intersection '() '(a b a a))
(bag-intersection '(a b a a) '())
|#



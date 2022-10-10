#lang racket
;Lab 6 -- New Material Begins on line 223


#| ^^^ READ ME ^^^ |#

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

;#3 - Set Equivalence
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



;#4 - Union & Intersection

;Union
;Mathematical Union
;Input: 2 "sets" made from lists
;Output: 1 "set" that is the mathematical union of the sets
;Example: (union '(1 2) '(3)) => '(1 2 3)
(define (union S1 S2)
  (cond
    [(empty? S1) S2]
    [else (if (member? (car S1) S2)
                  (union (cdr S1) S2); member -- yes
                  (union (cdr S1) (cons (car S1) S2)); member -- no
              )
     ]
    )
  )
                                                                  
;Intersection
;Mathematical Intersection
;Input: 2 "sets" made from lists
;Output: 1 "set" that is the mathematical intersection of the sets
;Example: (intersect '(1 2) '(1)) => '(1)
(define (intersect S1 S2)
  (cond
    [(empty? S1) empty]
    [(empty? S2) S2]
    [else (if (member? (car S1) S2)
              (cons (car S1) (intersect (cdr S1) S2))
              (intersect (cdr S1) S2))]))

;False
(define (false?)
  #f)

;True
(define (true?)
  #t)

;Is-Relation?
;Inputs: two lists L and S
;Outputs: boolean literal, #t if L is a relation on S, #f otherwise.
(define (Is-Relation? L S)
  (cond
    [(empty? L) #t]
    [else (if (and (member? (car (car L)) S) (member? (car (cdr (car L))) S))
              (Is-Relation? (cdr L) S)
              (false?))]))

;Reflexive? 
;Determines if a relation on a set has the reflexive quality
;Input: a list of pairs L and a list S
;Output: #t if L is a reflexive relation over S and #f otherwise
(define (Reflexive? L S)
  (if (and (Is-Relation? L S) (Reflex? L S))
      #t
      #f))

;Reflexive? 
;Determines if a relation on a set has the reflexive quality
;Input: a list of pairs L and a list S
;Output: #t if L is a reflexive relation over S and #f otherwise
(define (Reflex? L S)
  ;base case S is empty or L is empty
  (cond
    [(and (empty? L) (empty? S)) #t]
    [(empty? L) #f];the null relation is not reflexive
    [(empty? S) #f]
    [else (if (member? (list (car S) (car S)) L)
              (if (set-equal? (cdr S) '())
                  (true?) ;evaluates to #t
                  (Reflex? L (cdr S)))
              (false?))]));evaluates to #f


;Ordered Membership
;membership but order matters
;Refer to spec on member at top of page
(define (ordered-member? x L)
    (cond
    [(null? L) #f]
    [(equal? x (car L)) #t]
    [else (ordered-member? x (cdr L))]))
    


;Symmetric?
;Inputs: a list L
;Outputs: #t if the set L has the symmetric quality, #f otherwise
(define Symmetric?
  (lambda (L)
    (Sym? L L)))

;Sym?
;Inputs: two identical lists
;Outputs: #t if L is symmetric, #f otherwise.
(define (Sym? L L1)
  (cond
    [(empty? L) #t]
    [else (if (ordered-member? (pair-flip (car L)) L1)
              (Sym? (cdr L) L1)
              (false?))]))


;Pair Flip
;2 element list reverses order
;(1 2) -> (2, 1)
(define (pair-flip L)
  (list (car (cdr L)) (car L)))


;Transitive?
;Inputs: a list L
;Outputs: #t if the list L has the transitive quality, false otherwise.
(define Transitive?
  (lambda (L)
    (Tran? L L)))

(define (Tran? L L1) 
  (cond
    [(empty? L) #t]
    [else (if (det? (car L) L1)
              (Tran? (cdr L) L1)
              (false?))]))


;Puts in three input vals with a copy of the original list for detect?
;Nothing interesting
(define det?
  (lambda (P L)
    (detect? P L L)))


;Detect
;Inputs: P1 is a pair, L2 is a list of pairs, L3 is the original list
;Outputs: #t if the P1 pair is transitive with the rest of the list, #f otherwise
(define (detect? P1 L2 L3)
  (cond
    [(empty? L2) #t]
    [else (if (or (B!=C P1 (car L2)) (ordered-member? (new-pair P1 (car L2)) L3))
              (detect? P1 (cdr L2) L3)
              (false?))]))


;new-pair
;Takes two pairs of the form (A,B), (C,D) and creates one (A,D)
;Input (A,B), (C,D)
;Output: (A,D)
(define (new-pair p1 p2)
  (list (car p1) (cadr p2)))


;B!=C
;Takes two pairs, (A,B) and (C,D) and determines if B == C
;Input: Two pairs, (A,B) (C,D)
;Output: #t if B!=C, #f otherwise
(define (B!=C L1 L2)
  (cond
    [(empty? L1) #t]
    [(empty? L2) #t]
    [else (if (equal? (cadr L1) (car L2))
              (false?)
              (true?))]))

#|
Secret method!!!
This one determines whether a relation is an equivalence relation
Input: A set and a relation set on the initial
Output: #t if it is an equivalence relation and #f otherwise
|#
(define Equivalence?
  (lambda (R A)
    (if (and (and (Reflexive? R A) (Symmetric? R)) (Transitive? R))
    (true?)
    (false?)
    )))

#|
Reflexive-Closure
Adds elementts to the set to make it reflexive
Input: A list of relations L on the set S and the set S
Output: A set of relations on the set S to fulfill the reflexive property
|#
(define (Reflexive-Closure L S)
      (cond
        [(empty? S) L]
        [(Reflexive? L S) L]
        [else
         (let ([p (list (car S) (car S))])
         (if (ordered-member? p L)
                  (Reflexive-Closure L (cdr S))
                  (Reflexive-Closure (cons p L) (cdr S))
                  ))]))

#|
Rev Pair
Reverses the pair ordering
Input: 1 pair
Output: 1 pair
(x,y) -> (y,x)
|#
(define RevPair (lambda (P)
                  (list (cadr P) (car P))))
  

#|
Symmetric-Closure
Given a Relation L, Symmetric-Closure makes the Relation Symmetric
Input: A relation defined as a list
Output: A set of relations that have the Symmetric Property.
|#
(define Symmetric-Closure
  (lambda (L)
    (Symmetric-C L L)))

(define (Symmetric-C L LO)
  (cond
    [(Symmetric? L) L]
    [(empty? LO) L]
    [else
     (let ([p (RevPair (car LO))])
     (if (ordered-member? (RevPair (car LO)) L)
              (Symmetric-C L (cdr LO))
              (Symmetric-C (cons p L) (cdr LO))))]))

#|
Transitive-Closure
Takes a relation and adds elements to make it transitive
Input: A list of ordered pairs
Output: A transitive relation
|#
(define Transitive-Closure
  (lambda (L)
    (Trance L L L L)))

(define (Trance L1 L2 L3 L4) 
  (cond
    [(empty? L1) L3] ;outer loop
    [(empty? L2) (Trance (cdr L1) L4 L3 L4)] ;inner loop - problem lies here (L2 is empty)
    [else (cond
            [(B!=C (car L1)(car L2))(Trance L1 (cdr L2) L3 L4)]
            [else (if (ordered-member? (new-pair (car L1) (car L2)) L3)
                      (Trance L1 (cdr L2) L3 L4)
                      (Trance L1 (cdr L2) (cons (new-pair (car L1) (car L2)) L3) L4))])]))
    

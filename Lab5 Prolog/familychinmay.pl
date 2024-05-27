male(john).
male(abhram).
male(david).
male(mike).
female(miya).
female(lisa).
female(jiya).
female(susan).
female(emma).
parent(emma,david).
parent(mike,david).
parent(david,abhram).
parent(abhram,jiya).
parent(lisa,mike).
parent(susan,emma).
parent(john,susan).
parent(john,miya).


sister(X, Y) :- parent(Z, X), 
parent(Z, Y),     female(X), 
    X \== Y. 
 
mother(X, Y) :- parent(X, Y),     female(X). 
father(X, Y) :- parent(X, Y),     male(X). 
brother(X, Y) :- parent(Z, X), parent(Z, Y),
 male(X),     X \== Y.

grandfather(X, Y) :- 
    father(X, Z), 
    parent(Z, Y).

grandmother(X,Y) :-
    mother(X,Z),
    parent(Z,Y).
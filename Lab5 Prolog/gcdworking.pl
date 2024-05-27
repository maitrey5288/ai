:- initialization(main).

main :-
    gcd(5, 10, G),
    write('Greatest Common Divisor of 5 and 10: '),
    write(G),
    nl,
    halt.

gcd(A,B,X):- A=0, X=B. % base case
gcd(A,B,X):- B=0, X=A. % base case
gcd(A,B,X):- A>B, gcd(B, A, X).
gcd(A,B,X):- A<B, T is B mod A, gcd(A, T, X).
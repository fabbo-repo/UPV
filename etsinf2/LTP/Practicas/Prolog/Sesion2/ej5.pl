% Exercise 5. Wrong version of myappend, to correct:
myappend([],L,L).
myappend([E|L1],L2,[X|L3]) :- X = E, myappend(L1,L2,L1).


flatten([],[]).
flatten([X|L],[X|P]) :- atomic(X), flatten(L,P).
flatten([X|L],P) :- not(atomic(X)), flatten(X,P_X), flatten(L,P_L), append(P_X,P_L,P).        


prefix(P,L) :- append(P,_,L).
suffix(P,L) :- append(_,P,L).
sublist(S,L) :- suffix(L1,L),prefix(S,L1).
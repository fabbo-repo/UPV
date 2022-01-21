% Exercise 4. Wrong version of mymember, to correct:
mymember(E,[E|_]).
mymember(E,[H|L]) :- mymember(H,L).
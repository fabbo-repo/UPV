(deffacts data
	(number 7)
	(number 18)
	(list 2 14 90))

(defrule R1
	(number ?x)
	(number ?y)
=>
	(assert (list ?x ?y)))

(defrule R2
	(list $?x ?num $?y)
=>
	(printout t "The number is " ?num crlf))
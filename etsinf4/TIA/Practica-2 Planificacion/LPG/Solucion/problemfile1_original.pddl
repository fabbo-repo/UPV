(define (problem emisionesV-P-1)
	(:domain emisionesV)

	(
		:objects
			pedido1 - pedido
			pedido2 - pedido
			pedido3 - pedido
			pedido4 - pedido
			pedido5 - pedido

			camion1 - camion
			camion2 - camion

			furgoneta1 - furgoneta
			furgoneta2 - furgoneta
			
			puntoA - punto
			puntoB - punto
			puntoC - punto
			puntoD - punto
			puntoE - punto
			puntoF - punto
	)

	(
		:init
			(vehiculo-en puntoC camion1)
			(vehiculo-en puntoC camion2)

			(vehiculo-en puntoB furgoneta1)
			(vehiculo-en puntoB furgoneta2)
			
			(noeszle puntoC)
			(noeszle puntoD)
			(noeszle puntoE)
			(noeszle puntoF)
			
			(pedido-en pedido1 puntoA)
			(pedido-en pedido2 puntoB)
			(pedido-en pedido3 puntoF)
			(pedido-en pedido4 puntoD)
			(pedido-en pedido5 puntoE)
			
			(esintercambiador puntoC)
			(esintercambiador puntoD)
			(esintercambiador puntoE)
			
			; Distancias de A a A, B, C, D, E, F
			(= (distancia puntoA puntoA) 0)
			(= (distancia puntoA puntoB) 4)
			(= (distancia puntoA puntoC) 6)
			(= (distancia puntoA puntoD) 10)
			(= (distancia puntoA puntoE) 52)
			(= (distancia puntoA puntoF) 100)
			
			; Distancias de B a A, B, C, D, E, F
			(= (distancia puntoB puntoA) 4)
			(= (distancia puntoB puntoB) 0)
			(= (distancia puntoB puntoC) 4)
			(= (distancia puntoB puntoD) 16)
			(= (distancia puntoB puntoE) 20)
			(= (distancia puntoB puntoF) 40)
			
			; Distancias de C a A, B, C, D, E, F
			(= (distancia puntoC puntoA) 6)
			(= (distancia puntoC puntoB) 4)
			(= (distancia puntoC puntoC) 0)
			(= (distancia puntoC puntoD) 28)
			(= (distancia puntoC puntoE) 55)
			(= (distancia puntoC puntoF) 30)
			
			; Distancias de D a A, B, C, D, E, F
			(= (distancia puntoD puntoA) 10)
			(= (distancia puntoD puntoB) 16)
			(= (distancia puntoD puntoC) 28)
			(= (distancia puntoD puntoD) 0)
			(= (distancia puntoD puntoE) 30)
			(= (distancia puntoD puntoF) 10)
			
			; Distancias de E a A, B, C, D, E, F
			(= (distancia puntoE puntoA) 52)
			(= (distancia puntoE puntoB) 20)
			(= (distancia puntoE puntoC) 55)
			(= (distancia puntoE puntoD) 30)
			(= (distancia puntoE puntoE) 0)
			(= (distancia puntoE puntoF) 160)
			
			; Distancias de F a A, B, C, D, E, F
			(= (distancia puntoF puntoA) 100)
			(= (distancia puntoF puntoB) 40)
			(= (distancia puntoF puntoC) 30)
			(= (distancia puntoF puntoD) 10)
			(= (distancia puntoF puntoE) 160)
			(= (distancia puntoF puntoF) 0)

			(= (distancia-total-restante) 70)
			(= (presupuesto) 40)
			(= (total-dinero-extra) 0) ; dinero gastado
			(= (precio-derechos-emisiones) 20)
			(= (distancia-derechos-emisiones) 20)
	)

	(
		:goal 
			(and
				(pedido-en pedido1 puntoF)
				(pedido-en pedido2 puntoE)
				(pedido-en pedido3 puntoD)
				(pedido-en pedido4 puntoE)
				(pedido-en pedido5 puntoA))
	)

	(:metric minimize (+ (* 0.8 (total-time)) (* 0.2 (total-dinero-extra))))
)

(define (domain emisionesV)

        (
                :requirements 
                :durative-actions 
                :typing 
                :fluents
        )

        ; Vehiculo y Punto heredan de object y Camión y Furgoneta heredan de Vehiculo
        (
                :types 
                        vehiculo punto pedido - object 
                        camion furgoneta - vehiculo
        )

        (
                :predicates 
                        (vehiculo-en ?pt - punto ?v - vehiculo)
                        (noeszle ?pt - punto)
                        (pedido-en ?pd - pedido ?l - (either punto vehiculo))
                        (esintercambiador ?pt - punto)
        )

        (       
                :functions 
                        (distancia ?pt1 - punto ?pt2 - punto)
                        (distancia-total-restante)
                        (presupuesto)
                        (total-dinero-extra)
                        (precio-derechos-emisiones)
                        (distancia-derechos-emisiones)
        )

        ; -------------------------------------------------------------------------------------------------------
        (
                :durative-action transportar-camion
                :parameters (?pt1 - punto ?pt2 - punto ?v - camion)
                :duration (= ?duration (/ (distancia ?pt1 ?pt2) 4))
                :condition 
                        (and 
                                (at start (vehiculo-en ?pt1 ?v))
                                (at start (noeszle ?pt2))
                                (at start (>= (distancia-total-restante) (distancia ?pt1 ?pt2))))
                :effect
                        (and 
                                (at start (not (vehiculo-en ?pt1 ?v))) ; el vehiculo al principio deja de estar en pt1
                                (at end (vehiculo-en ?pt2 ?v)) ; el vehiculo pasa a estar estar en pt2
                                (at end (decrease (distancia-total-restante) (distancia ?pt1 ?pt2))))
        )

        ; -------------------------------------------------------------------------------------------------------
        (
                :durative-action transportar-furgoneta
                :parameters (?pt1 - punto ?pt2 - punto ?v - furgoneta)
                :duration (= ?duration (distancia ?pt1 ?pt2))
                :condition 
                        (at start (vehiculo-en ?pt1 ?v))
                :effect 
                        (and 
                                (at start (not (vehiculo-en ?pt1 ?v))) ; el vehiculo al principio deja de estar en pt1
                                (at end (vehiculo-en ?pt2 ?v))) ; el vehiculo pasa a estar estar en pt2
        )

        ; -------------------------------------------------------------------------------------------------------
        (
                :durative-action incrementar
                :parameters (?pd - pedido ?l - (either punto vehiculo))
                :duration (= ?duration 1)
                :condition 
                        (and
                                (at start (>= (presupuesto) (+ (total-dinero-extra) (precio-derechos-emisiones))))
                                (at start (pedido-en ?pd ?l)))
                :effect 
                        (and 
                                (at end (increase (distancia-total-restante) (distancia-derechos-emisiones)))
                                (at end (increase (total-dinero-extra) (precio-derechos-emisiones))))
        )

        ; -------------------------------------------------------------------------------------------------------
        (
                :durative-action recoger 
                :parameters (?pd - pedido ?v - vehiculo ?pt - punto)
                :duration (= ?duration 1)
                :condition
                        (and
                                (over all (vehiculo-en ?pt ?v))
                                (at start (pedido-en ?pd ?pt)))
                :effect 
                        (and
                                (at end (not (pedido-en ?pd ?pt)))
                                (at end (pedido-en ?pd ?v)))
        )

        ; -------------------------------------------------------------------------------------------------------
        (
                :durative-action entregar 
                :parameters (?pd - pedido ?v - vehiculo ?pt - punto)
                :duration (= ?duration 2)
                :condition
                        (and
                                (over all (vehiculo-en ?pt ?v))
                                (at start (pedido-en ?pd ?v)))
                :effect 
                        (and
                                (at end (not (pedido-en ?pd ?v)))
                                (at end (pedido-en ?pd ?pt)))
        ) 

        ; -------------------------------------------------------------------------------------------------------
        (
                :durative-action intercambiar
                :parameters (?pd - pedido ?v1 - vehiculo ?v2 - vehiculo ?pt - punto)
                :duration (= ?duration 3)
                :condition
                        (and
                                (over all (vehiculo-en ?pt ?v1))
                                (over all (vehiculo-en ?pt ?v2))
                                (at start (esintercambiador ?pt))
                                (at start(pedido-en ?pd ?v1)))
                :effect 
                        (and
                                (at end (not (pedido-en ?pd ?v1)))
                                (at end (pedido-en ?pd ?v2)))
        ) 

)

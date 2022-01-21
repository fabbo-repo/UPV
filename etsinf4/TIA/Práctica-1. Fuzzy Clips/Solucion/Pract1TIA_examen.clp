;--------------------------------------------------------------------------------------------------------
; Fuzzify:
;--------------------------------------------------------------------------------------------------------
(deffunction fuzzify (?fztemplate ?value ?delta)

        (bind ?low (get-u-from ?fztemplate))
        (bind ?hi  (get-u-to   ?fztemplate))

        (if (<= ?value ?low)
          then
            (assert-string
              (format nil "(%s (%g 1.0) (%g 0.0))" ?fztemplate ?low ?delta))
          else
            (if (>= ?value ?hi)
              then
                (assert-string
                   (format nil "(%s (%g 0.0) (%g 1.0))"
                               ?fztemplate (- ?hi ?delta) ?hi))
              else
                (assert-string
                   (format nil "(%s (%g 0.0) (%g 1.0) (%g 0.0))"
                               ?fztemplate (max ?low (- ?value ?delta))
                               ?value (min ?hi (+ ?value ?delta)) ))
            )
        )
)

;--------------------------------------------------------------------------------------------------------
; Variables difusas:
;--------------------------------------------------------------------------------------------------------
(deftemplate distancia                          
    0 50 metros                                 ; Rango [0, 50] m
    (
        (cerca (0 1) (5 1) (15 0))              ; Valores difusos: cerca, medio, lejos
        (medio (10 0) (20 1) (30 1) (35 0))
        (lejos (30 0) (35 1) (50 1))
    )
)

(deftemplate velocidad                          
    -30 30 kmh                                  ; Rango [-30, 30] km/h
    (                                           
        (alejando (-30 1) (0 0))                ; Valores difusos: alejando, constante, acercando
        (constante (-10 0) (0 1) (15 0))
        (acercando (0 0) (30 1))
    )
)

(deftemplate fuerza_aceleracion                 
    0 100 porcien                               ; Rango [0, 100] %
    (                                           
        (nula (0 0) (0 1) (0 0))                ; Valores difusos: nula, baja, media, alta
        (baja (0 1) (5 1) (20 0))
        (media (10 0) (40 1) (60 1) (70 0))
        (alta (60 0) (100 1))
    )
)

(deftemplate presion_freno                      
    0 100 porcien                               ; Rango [0, 100] %
    (                                           
        (nula (0 0) (0 1) (0 0))                ; Valores difusos: nula, baja, media, alta
        (baja (0 1) (5 1) (20 0))
        (media (10 0) (40 1) (60 1) (70 0))
        (alta (60 0) (100 1))
    )
)

; EXTENSION:
(deftemplate visibilidad                      
    0 100 grado                               ; Rango [0, 100] grado
    (                                           
        (baja (0 1) (25 1) (35 0))                ; Valores difusos: baja, media, alta
        (media (30 0) (35 1) (65 1) (75 0))
        (alta (65 0) (80 1) (100 1))
    )
)
;--------------------------------------------------------------------------------------------------------
; Clases:
;--------------------------------------------------------------------------------------------------------
(deftemplate vehiculo
    (slot id (type SYMBOL))
    (slot distancia (type INTEGER))
    (slot velocidad (type INTEGER))
    (slot potencia (type INTEGER))
    (slot fuerza_aceleracion_max (type FLOAT))
    (slot fuerza_aceleracion_mom (type FLOAT))
    (slot presion_freno_max (type FLOAT))
    (slot presion_freno_mom (type FLOAT))
)


;--------------------------------------------------------------------------------------------------------
; Reglas:
;--------------------------------------------------------------------------------------------------------
; Aceleración:
(defrule aceleracion1
    (distancia cerca)
    (velocidad alejando)
    =>
    (assert (fuerza_aceleracion media))
)
(defrule aceleracion2
    (distancia cerca)
    (velocidad constante)
    =>
    (assert (fuerza_aceleracion nula))
)
(defrule aceleracion3
    (distancia cerca)
    (velocidad acercando)
    =>
    (assert (fuerza_aceleracion nula))
)
(defrule aceleracion4
    (distancia medio)
    (velocidad alejando)
    =>
    (assert (fuerza_aceleracion more-or-less alta))
)
(defrule aceleracion5
    (distancia medio)
    (velocidad constante)
    =>
    (assert (fuerza_aceleracion media))
)
(defrule aceleracion6
    (distancia medio)
    (velocidad acercando)
    =>
    (assert (fuerza_aceleracion nula))
)
(defrule aceleracion7
    (distancia lejos)
    (velocidad alejando)
    =>
    (assert (fuerza_aceleracion very alta))
)
(defrule aceleracion8
    (distancia lejos)
    (velocidad constante)
    =>
    (assert (fuerza_aceleracion alta))
)
(defrule aceleracion9
    (distancia lejos)
    (velocidad acercando)
    =>
    (assert (fuerza_aceleracion very baja))
)
; Freno:
(defrule freno1
    (distancia cerca)
    (velocidad alejando)
    =>
    (assert (presion_freno nula))
)
(defrule freno2
    (distancia cerca)
    (velocidad constante)
    =>
    (assert (presion_freno very baja))
)
(defrule freno3
    (distancia cerca)
    (velocidad acercando)
    =>
    (assert (presion_freno alta))
)
(defrule freno4
    (distancia medio)
    (velocidad alejando)
    =>
    (assert (presion_freno nula))
)
(defrule freno5
    (distancia medio)
    (velocidad constante)
    =>
    (assert (presion_freno nula))
)
(defrule freno6
    (distancia medio)
    (velocidad acercando)
    =>
    (assert (presion_freno more-or-less media))
)
(defrule freno7
    (distancia lejos)
    (velocidad alejando)
    =>
    (assert (presion_freno nula))
)
(defrule freno8
    (distancia lejos)
    (velocidad constante)
    =>
    (assert (presion_freno nula))
)
(defrule freno9
    (distancia lejos)
    (velocidad acercando)
    =>
    (assert (presion_freno very baja))
)

; EXTENSION
(defrule aceleracion10
    (distancia cerca)
    (visibilidad baja)
    =>
    (assert (fuerza_aceleracion baja))
)
(defrule freno10
    (distancia lejos)
    (visibilidad alta)
    =>
    (assert (presion_freno more-or-less baja))
)


(defrule inicial                ;lee de consola los valores crisp
    (initial-fact)
    =>
    (printout t "Introduzca el identificador: ")
    (bind ?id (read))
    (printout t "Introduzca la distancia (metros): ")
    (bind ?distancia (read))
    (printout t "Introduzca la velocidad (km/h): ")
    (bind ?velocidad (read))
    (printout t "Introduzca la visibilidad (grados): ")
    (bind ?visibilidad (read))
    (printout t "Introduzca la potencia (Kw): ")
    (bind ?potencia (read))
    (fuzzify distancia ?distancia 0.0)
    (fuzzify velocidad ?velocidad 0.0)
    (fuzzify visibilidad ?visibilidad 0.0)
    (assert (vehiculo (id ?id) (distancia ?distancia) (velocidad ?velocidad) 
        (potencia ?potencia)
        (fuerza_aceleracion_max 0.0) (fuerza_aceleracion_mom 0.0)
        (presion_freno_max 0.0) (presion_freno_mom 0.0)))
)

; EXTENSION
(defrule alerta-critica
    ?vehiculo <- (vehiculo (id ?id) (distancia ?d) (velocidad ?v)
        (potencia ?potencia)
        (fuerza_aceleracion_max 0.0) (fuerza_aceleracion_mom 0.0) 
        (presion_freno_max 0.0) (presion_freno_mom 0.0))
    ?fuer_acel <- (fuerza_aceleracion ?)
    (test (> ?potencia 200))
    (test (> (moment-defuzzify ?fuer_acel) 70.0))
    =>
    (printout t crlf crlf)
    (printout t "Situacion Critica: peligro de deslizamiento" crlf)
)

(defrule mostrar-resultado
    (declare (salience -1))
    ?distancia <- (distancia ?)
    ?velocidad <- (velocidad ?)
    ?vehiculo <- (vehiculo (id ?id) (distancia ?d) (velocidad ?v) 
        (fuerza_aceleracion_max 0.0) (fuerza_aceleracion_mom 0.0) 
        (presion_freno_max 0.0) (presion_freno_mom 0.0))
    ?fuer_acel <- (fuerza_aceleracion ?)
    ?pres_fren <- (presion_freno ?)
    =>
    (bind ?maxac (maximum-defuzzify ?fuer_acel))
    (bind ?momac (moment-defuzzify ?fuer_acel))
    (bind ?maxpf (maximum-defuzzify ?pres_fren))
    (bind ?mompf (moment-defuzzify ?pres_fren))
    (printout t crlf crlf)
    (printout t "Valor de fuerza de aceleracion para vehiculo " ?id " :" crlf)
    (printout t "Maximum: " ?maxac crlf)
    (printout t "Momentum: " ?momac crlf crlf)
    (printout t "Valor de presion de freno para vehiculo " ?id " :" crlf)
    (printout t "Maximum: " ?maxpf crlf)
    (printout t "Momentum: " ?mompf crlf crlf)
    (retract ?distancia ?velocidad ?fuer_acel ?pres_fren)
    (modify ?vehiculo (fuerza_aceleracion_max ?maxac) (fuerza_aceleracion_mom ?momac)
        (presion_freno_max ?maxpf) (presion_freno_mom ?mompf))
    ;(assert (initial-fact))
)
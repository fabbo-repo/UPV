;; <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
;; <<<<<<<<<<<<<<<<<< Robot Practica 1 >>>>>>>>>>>>>>>>>>>>>
;; Miembros: Lishuang Sun (Maria), Fabian Scherle Carboneres
;; >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

;; Variables globales
(defglobal ?*nodos_gen* = 0) ;; Numero de nodos generados

;; Hechos
;; Informacion estatica:
(deffacts escaleras 	               ;; Informacion de las escaleras
  (escalera 3 1)
  (escalera 7 1)
  (escalera 2 2)
  (escalera 10 2)
  (escalera 1 3)
  (escalera 7 3)
  (escalera 11 3))
  ;; No puede haber enemigo ni caja en la casilla donde 
  ;; parta o llegue una escalera
(deffacts huecos      	             ;; Informacion de los huecos
  (hueco xy 5 2 xy 3 3 xy 8 3 xy 4 4 xy 5 4 xy 6 4))
(deffacts info_cuadricula            ;; Informacion de la cuadricula
  (cuadricula 11 4))

;; Reglas
(defrule derecha
  (robot ?x ?y disparos ?d cajasres ?c nivel ?n mov ?m enemigos $?enem cajas $?cajas)
  (hueco $?h)
  (profundidadMaxima ?profM)
  (cuadricula ?maxX ?)
  (test (<= (+ ?x 1) ?maxX))
  (test (not (member$ (create$ xy (+ ?x 1) ?y) $?h)))
  (test (not (member$ (create$ xy (+ ?x 1) ?y) $?enem)))
  (test (neq ?m izquierda))
  (test (< ?n ?profM))
  =>
  (assert (robot (+ ?x 1) ?y disparos ?d cajasres ?c nivel (+ ?n 1) mov derecha enemigos $?enem cajas $?cajas))
  (bind ?*nodos_gen* (+ ?*nodos_gen* 1))
)


(defrule izquierda
  (robot ?x ?y disparos ?d cajasres ?c nivel ?n mov ?m enemigos $?enem cajas $?cajas)
  (hueco $?h)
  (profundidadMaxima ?profM)
  (test (> (- ?x 1) 0))
  (test (not (member$ (create$ xy (- ?x 1) ?y) $?h)))
  (test (not (member$ (create$ xy (- ?x 1) ?y) $?enem)))
  (test (neq ?m derecha))
  (test (< ?n ?profM))
  =>
  (assert (robot (- ?x 1) ?y disparos ?d cajasres ?c nivel (+ ?n 1) mov izquierda enemigos $?enem cajas $?cajas))
  (bind ?*nodos_gen* (+ ?*nodos_gen* 1))
)


(defrule subir_planta
  (robot ?x ?y disparos ?d cajasres ?c nivel ?n mov ?m $?o)
  (escalera ?x ?y)
  (profundidadMaxima ?profM)
  (cuadricula ? ?maxY)
  (test (<= (+ ?y 1) ?maxY))
  (test (neq ?m bajar_planta))
  (test (< ?n ?profM))
  =>
  (assert (robot ?x (+ ?y 1) disparos ?d cajasres ?c nivel (+ ?n 1) mov subir_planta $?o))
  (bind ?*nodos_gen* (+ ?*nodos_gen* 1))
)


(defrule bajar_planta
  (robot ?x ?y disparos ?d cajasres ?c nivel ?n mov ?m $?o)
  (escalera ?escX ?escY)
  (profundidadMaxima ?profM)
  (cuadricula ? ?maxY)
  (test (> (- ?y 1) 0))
  (test (and (= ?x ?escX) (= ?y (+ ?escY 1))))
  (test (neq ?m subir_planta))
  (test (< ?n ?profM))
  =>
  (assert (robot ?x (- ?y 1) disparos ?d cajasres ?c nivel (+ ?n 1) mov bajar_planta $?o))
  (bind ?*nodos_gen* (+ ?*nodos_gen* 1))
)


(defrule recoger_caja
  (robot ?x ?y disparos ?d cajasres ?c nivel ?n mov ? enemigos $?o1 cajas $?o2 xy ?x ?y $?o3)
  (profundidadMaxima ?profM)
  (test (< ?n ?profM))
  =>
  (assert(robot ?x ?y disparos ?d cajasres (- ?c 1) nivel (+ ?n 1) mov recoger enemigos $?o1 cajas $?o2 $?o3))
  (bind ?*nodos_gen* (+ ?*nodos_gen* 1))    
)


(defrule disparar_enemigo
  (robot ?x ?y disparos ?d cajasres ?c nivel ?n mov ?m enemigos $?o1 $?enem $?o2 cajas $?o3)
  (profundidadMaxima ?profM)
  (test (< ?n ?profM))
  (test (> ?d 0))
  (test (or (eq (create$ xy (- ?x 1) ?y) $?enem) (eq (create$ xy (+ ?x 1) ?y) $?enem)))
  =>
  (assert (robot ?x ?y disparos (- ?d 1) cajasres ?c nivel (+ ?n 1) mov ?m enemigos $?o1 $?o2 cajas $?o3))
  (bind ?*nodos_gen* (+ ?*nodos_gen* 1))
)


;; Objetivo:
;; Recoger todas las cajas
(defrule objetivo
  (declare (salience 10))
  (robot ?x ?y disparos ?d cajasres 0 nivel ?n $?)
  =>
  (printout t "Solucion en el nivel: " ?n crlf)
  (printout t "Numero de nodos generados: " ?*nodos_gen* crlf)
  (printout t "Objetivo: 0 cajas restantes." crlf)
    
  (halt)
)

(defrule no_solucion
  (declare (salience -10))
  (robot $?)
  =>
  (printout t "Solucion no encontrada" crlf)
  (printout t "Numero de nodos generados: " ?*nodos_gen* crlf)
    
  (halt)
)		

;; >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

(deffunction main()
  (reset)
  ;; Se pide escribir nivel de profundidad del arbol
	(printout t "Nivel de profundidad maximo: " )
	(bind ?profM (read))

  ;; Se pide seleccionar la estrategia de busqueda para resolver el SBR
	(printout t "Tipo de busqueda " crlf "    1-> Anchura" crlf "    2-> Profundidad" crlf )
	(bind ?a (read))
	(if (= ?a 1)
	       then (set-strategy breadth)
	       else (set-strategy depth))
  
  (printout t " Ejecuta run para poner en marcha el programa " crlf)
	(assert (profundidadMaxima ?profM))

  ;; Informacion dinamica:
  (assert (robot 1 1 disparos 2 cajasres 3 nivel 0 mov null 
    enemigos xy 4 2 xy 8 2 xy 8 4 
    cajas xy 11 2 xy 4 3 xy 3 4))
  ;; robot x y diparos d cajasres c nivel n mov n
  ;; enemigo xy eX eY 
  ;; cajas xy cX cY
  ;; x -> posicion horizontal en la cuadricula
  ;; y -> posicion vertical en la cuadricula
  ;; d -> cantidad de disparos
  ;; c -> cantidad de cajas que faltan por recoger
  ;; n -> nivel de profundidad
  ;; m -> ultimo movimiento realizado
  ;; xy -> indica que a continuacion existe un par x e y
  ;; eX -> posicion horizontal en la cuadricula de un enemigo
  ;; eY -> posicion vertical en la cuadricula de un enemigo
  ;; cX -> posicion horizontal en la cuadricula de una caja
  ;; cY -> posicion vertical en la cuadricula de una caja
)
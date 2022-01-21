(deftemplate tanque 
    0 80 litros
    (
        (bajo (10 1)(30 0))
        (medio (20 0)(35 1)(45 1)(60 0))
        (alto (50 0)(70 1))
    )
)

(defrule danger
    (tanque extremely alto)
    =>
    (printout t "El tanque puede desbordarse. PELIGRO!" crlf)
    (assert (alarma))
)

(defrule inicial ;lee de consola un valor crisp y aserta su valor fusificado
    (initial-fact)
    =>
    (assert (tanque alto))
)

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

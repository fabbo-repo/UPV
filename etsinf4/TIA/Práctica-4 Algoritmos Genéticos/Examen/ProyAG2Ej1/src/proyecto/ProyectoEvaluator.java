package proyecto;

import java.util.ArrayList;

import org.opt4j.core.Objectives;
import org.opt4j.core.Objective.Sign;
import org.opt4j.core.problem.Evaluator;

public class ProyectoEvaluator implements Evaluator<ArrayList<TTramo>>{
	public Objectives evaluate(ArrayList<TTramo> phenotype) {
		double befSUM = 0; // Beneficio total
		// Productos de tramos diurnos:
		int numPT12 = 0;
		// Consumos para comprobar restriccion:
		double consumoT1 = 0; double consumoT2 = 0; double consumoT3 = 0;
		
		for(int i = 0; i < phenotype.size(); i++) {
			int tramo = 0;
			switch(phenotype.get(i)) {
				case TRAMO1:
					tramo = 1; consumoT1 += Data.consumoProductos[i];
					break;
				case TRAMO2:
					tramo = 2; consumoT2 += Data.consumoProductos[i];
					break;
				case TRAMO3:
					tramo = 3; consumoT3 += Data.consumoProductos[i]; 
					break;
				case NULO:
					break;
			}
			if(tramo != 0)
				befSUM += Data.beneficioProductos[i] - 
					(Data.duracionTramos[tramo-1] * Data.precioTramos[tramo-1] *
					Data.consumoProductos[i]);
			if(tramo == 1 || tramo == 2) numPT12++;
			
			// Restriccion de potencia maxima:
			// En caso de no cumplirse, esta solucion no se toma en cuenta,
			// al maximizar se devuelve un -INF
			if(consumoT1 > Data.potenciaMaxima[0] 
					|| consumoT2 > Data.potenciaMaxima[1]
					|| consumoT3 > Data.potenciaMaxima[2]) {
				befSUM = Double.NEGATIVE_INFINITY; break;
			}
		}
		// Bonificacion;
		if(consumoT1 <= 0.9*Data.potenciaMaxima[0] 
				|| consumoT2 <= 0.9*Data.potenciaMaxima[1]
				|| consumoT3 <= 0.9*Data.potenciaMaxima[2]) {
			befSUM += 10;
		}
		Objectives objectives = new Objectives();
		objectives.add("Beneficio total: ", Sign.MAX, befSUM);
		objectives.add("Productos tramos diurnos: ", Sign.MAX, numPT12);
		return objectives;
	}

}

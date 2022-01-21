package proyecto;

import java.util.Random;

import org.opt4j.core.genotype.SelectGenotype;
import org.opt4j.core.problem.Creator;

public class ProyectoCreator implements Creator<SelectGenotype<TTramo>> {
	public SelectGenotype<TTramo> create() {
		TTramo[] tramos = TTramo.values();
		SelectGenotype<TTramo> genotype = new SelectGenotype<TTramo>(tramos);
		// El genotipo estara formado por "numeroProductos" de tramos al azar
		// Si hay 4 productos sera una lista estilo: 
		// [TRAMO1, TRAMO3, TRAMO1, TRAMO2, NULO]
		genotype.init(new Random(), Data.numeroProductos);
		return genotype;
	}
}

package proyecto;

import java.util.ArrayList;

import org.opt4j.core.genotype.SelectGenotype;
import org.opt4j.core.problem.Decoder;

public class ProyectoDecoder implements Decoder<SelectGenotype<TTramo>, ArrayList<TTramo>>{
	public ArrayList<TTramo> decode(SelectGenotype<TTramo> genotype) {
		ArrayList<TTramo> phenotype = new ArrayList<TTramo>();
		// Para este caso, el genotipo se mantiene igual como fenotipo 
		for(int i = 0; i < genotype.size(); i++)
			phenotype.add(genotype.getValue(i));
		return phenotype;
	}
}
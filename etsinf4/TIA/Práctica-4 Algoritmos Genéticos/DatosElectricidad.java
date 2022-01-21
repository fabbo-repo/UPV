package proyectoElectricidad;

public class DatosElectricidad 
{	
	public static final int NUM_TRAMOS	= 3;
	public static final int NUM_PEDIDOS	= 20;
	
	// consumo para los 20 pedidos
	public static final double[] consumo =
		{
				1.9, 2.1, 3.0, 0.7, 1.5, 3.3, 4.2, 2.6, 2.3, 3.2, 4.5, 4.2, 2.7, 1.9, 3.5, 2.7, 3.4, 4.5, 6.2, 2.3
		};
	
	// beneficio para los 20 pedidos
	public static final double[] beneficio =
		{
				3, 5, 6, 1, 3, 4, 9, 3, 4, 4, 8, 7, 4, 3, 4, 5, 4, 6, 9, 4
		};	
	
	// horas de cada uno de los tramos (el tramo 0 es ficticio)
	public static final int[] horasTramo =
		{
				0, 4, 4, 4
		};
	
	// potencia maxima contratada para cada tramo  (el tramo 0 es ficticio)
	public static final double[] potenciaMaximaTramo =
		{
				0, 15, 18, 25
		};
	
	// precio del kWh para cada tramo  (el tramo 0 es ficticio)
	public static final double[] preciokWhTramo =
		{
				0, 0.26, 0.18, 0.13
		};
}

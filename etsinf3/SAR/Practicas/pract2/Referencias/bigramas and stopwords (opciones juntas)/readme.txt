Hola,

En la práctica 2 "Cuenta palabras" hay una combinación de opciones que no está totalmente especificada en el boletín.

Se trata de combinar la eliminación de las stopwords y los bigramas.

El siguiente ejemplo muestra que el momento de eliminar las stopwords afecta al resultado. Imaginemso que una parte de una frase contiene estas palabras:

casa del barbero

Y que del es una stopword.

Opción a) Eliminamos las stopwords primero y calculamos las stopwords después:

Tras eliminar las stopwords nos quedaría:

casa barbero

Y se generaría el bigrama (casa,barbero).

Opción b) Generamos los bigramas y descaratmos los que contengan alguna stopword:

Generamos los bigramas (casa,del) y (del,barbero).

Ambos se eliminan y NO se genera el bigrama (casa,barbero).

Las referencias que había en poliformat correspondían a esta segunda opción.

Lo que hemos hecho es añadir en poliformat 2 juegos de referencias con ambas opciones. Ambas opciones serán válidas siempre que se sea consistente con una de ellas (no sirve mezclar una con otra al tuntún, o una o la otra).

Disculpad por las molestias que haya podido causar esta ambigüedad en la descripción de esta parte de la práctica.

Saludos,

los profesores de prácticas
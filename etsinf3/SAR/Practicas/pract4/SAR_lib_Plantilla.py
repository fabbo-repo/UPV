import json
from nltk.stem.snowball import SnowballStemmer
import os
import re


class SAR_Project:
    """
    Prototipo de la clase para realizar la indexacion y la recuperacion de noticias
        
        Preparada para todas las ampliaciones:
          parentesis + multiples indices + posicionales + stemming + permuterm + ranking de resultado

    Se deben completar los metodos que se indica.
    Se pueden añadir nuevas variables y nuevos metodos
    Los metodos que se añadan se deberan documentar en el codigo y explicar en la memoria
    """

    # lista de campos, el booleano indica si se debe tokenizar el campo
    # NECESARIO PARA LA AMPLIACION MULTIFIELD
    fields = [("title", True), ("date", False),
              ("keywords", True), ("article", True),
              ("summary", True)]
    
    
    # numero maximo de documento a mostrar cuando self.show_all es False
    SHOW_MAX = 10


    def __init__(self):
        """
        Constructor de la classe SAR_Indexer.
        NECESARIO PARA LA VERSION MINIMA

        Incluye todas las variables necesaria para todas las ampliaciones.
        Puedes añadir más variables si las necesitas 

        """
        self.index = {} # hash para el indice invertido de terminos --> clave: termino, valor: posting list.
                        # Si se hace la implementacion multifield, se pude hacer un segundo nivel de hashing de tal forma que:
                        # self.index['title'] seria el indice invertido del campo 'title'.
        self.sindex = {} # hash para el indice invertido de stems --> clave: stem, valor: lista con los terminos que tienen ese stem
        self.ptindex = {} # hash para el indice permuterm.
        self.docs = {} # diccionario de documentos --> clave: entero(docid),  valor: ruta del fichero.
        self.weight = {} # hash de terminos para el pesado, ranking de resultados. puede no utilizarse
        self.news = {} # hash de noticias --> clave entero (newid), valor: la info necesaria para diferenciar la noticia dentro de su fichero (doc_id y posición dentro del documento)
        self.tokenizer = re.compile("\W+") # expresion regular para hacer la tokenizacion
        self.stemmer = SnowballStemmer('spanish') # stemmer en castellano
        self.show_all = False # valor por defecto, se cambia con self.set_showall()
        self.show_snippet = False # valor por defecto, se cambia con self.set_snippet()
        self.use_stemming = False # valor por defecto, se cambia con self.set_stemming()
        self.use_ranking = False  # valor por defecto, se cambia con self.set_ranking()


    ###############################
    ###                         ###
    ###      CONFIGURACION      ###
    ###                         ###
    ###############################


    def set_showall(self, v):
        """

        Cambia el modo de mostrar los resultados.
        
        input: "v" booleano.

        UTIL PARA TODAS LAS VERSIONES

        si self.show_all es True se mostraran todos los resultados el lugar de un maximo de self.SHOW_MAX, no aplicable a la opcion -C

        """
        self.show_all = v


    def set_snippet(self, v):
        """

        Cambia el modo de mostrar snippet.
        
        input: "v" booleano.

        UTIL PARA TODAS LAS VERSIONES

        si self.show_snippet es True se mostrara un snippet de cada noticia, no aplicable a la opcion -C

        """
        self.show_snippet = v


    def set_stemming(self, v):
        """

        Cambia el modo de stemming por defecto.
        
        input: "v" booleano.

        UTIL PARA LA VERSION CON STEMMING

        si self.use_stemming es True las consultas se resolveran aplicando stemming por defecto.

        """
        self.use_stemming = v


    def set_ranking(self, v):
        """

        Cambia el modo de ranking por defecto.
        
        input: "v" booleano.

        UTIL PARA LA VERSION CON RANKING DE NOTICIAS

        si self.use_ranking es True las consultas se mostraran ordenadas, no aplicable a la opcion -C

        """
        self.use_ranking = v




    ###############################
    ###                         ###
    ###   PARTE 1: INDEXACION   ###
    ###                         ###
    ###############################


    def index_dir(self, root, **args):
        """
        NECESARIO PARA TODAS LAS VERSIONES
        
        Recorre recursivamente el directorio "root" e indexa su contenido
        los argumentos adicionales "**args" solo son necesarios para las funcionalidades ampliadas

        """

        self.multifield = args['multifield']
        self.positional = args['positional']
        self.stemming = args['stem']
        self.permuterm = args['permuterm']

        for dir, subdirs, files in os.walk(root):
            for filename in files:
                if filename.endswith('.json'):
                    fullname = os.path.join(dir, filename)
                    self.index_file(fullname)

        ##########################################
        ## COMPLETAR PARA FUNCIONALIDADES EXTRA ##
        ##########################################
        

    def index_file(self, filename):
        """
        NECESARIO PARA TODAS LAS VERSIONES

        Indexa el contenido de un fichero.

        Para tokenizar la noticia se debe llamar a "self.tokenize"

        Dependiendo del valor de "self.multifield" y "self.positional" se debe ampliar el indexado.
        En estos casos, se recomienda crear nuevos metodos para hacer mas sencilla la implementacion

        input: "filename" es el nombre de un fichero en formato JSON Arrays (https://www.w3schools.com/js/js_json_arrays.asp).
                Una vez parseado con json.load tendremos una lista de diccionarios, cada diccionario se corresponde a una noticia

        """

        with open(filename) as fh:
            jlist = json.load(fh)

        #
        # "jlist" es una lista con tantos elementos como noticias hay en el fichero,
        # cada noticia es un diccionario con los campos:
        #      "title", "date", "keywords", "article", "summary"
        #
        # En la version basica solo se debe indexar el contenido "article"
        #
        #
        #
        #################
        ### COMPLETAR ###
        #################



    def tokenize(self, text):
        """
        NECESARIO PARA TODAS LAS VERSIONES

        Tokeniza la cadena "texto" eliminando simbolos no alfanumericos y dividientola por espacios.
        Puedes utilizar la expresion regular 'self.tokenizer'.

        params: 'text': texto a tokenizar

        return: lista de tokens

        """
        return self.tokenizer.sub(' ', text.lower()).split()



    def make_stemming(self):
        """
        NECESARIO PARA LA AMPLIACION DE STEMMING.

        Crea el indice de stemming (self.sindex) para los terminos de todos los indices.

        self.stemmer.stem(token) devuelve el stem del token

        """
        
        pass
        ####################################################
        ## COMPLETAR PARA FUNCIONALIDAD EXTRA DE STEMMING ##
        ####################################################


    
    def make_permuterm(self):
        """
        NECESARIO PARA LA AMPLIACION DE PERMUTERM

        Crea el indice permuterm (self.ptindex) para los terminos de todos los indices.

        """
        pass
        ####################################################
        ## COMPLETAR PARA FUNCIONALIDAD EXTRA DE STEMMING ##
        ####################################################




    def show_stats(self):
        """
        NECESARIO PARA TODAS LAS VERSIONES
        
        Muestra estadisticas de los indices
        
        """
        pass
        ########################################
        ## COMPLETAR PARA TODAS LAS VERSIONES ##
        ########################################

        








    ###################################
    ###                             ###
    ###   PARTE 2.1: RECUPERACION   ###
    ###                             ###
    ###################################


    def solve_query(self, query, prev={}):
        """
        NECESARIO PARA TODAS LAS VERSIONES

        Resuelve una query.
        Debe realizar el parsing de consulta que sera mas o menos complicado en funcion de la ampliacion que se implementen


        param:  "query": cadena con la query
                "prev": incluido por si se quiere hacer una version recursiva. No es necesario utilizarlo.


        return: posting list con el resultado de la query

        """

        if query is None or len(query) == 0:
            return []

        ########################################
        ## COMPLETAR PARA TODAS LAS VERSIONES ##
        ########################################

 


    def get_posting(self, term, field='article'):
        """
        NECESARIO PARA TODAS LAS VERSIONES

        Devuelve la posting list asociada a un termino. 
        Dependiendo de las ampliaciones implementadas "get_posting" puede llamar a:
            - self.get_positionals: para la ampliacion de posicionales
            - self.get_permuterm: para la ampliacion de permuterms
            - self.get_stemming: para la amplaicion de stemming


        param:  "term": termino del que se debe recuperar la posting list.
                "field": campo sobre el que se debe recuperar la posting list, solo necesario se se hace la ampliacion de multiples indices

        return: posting list

        """
        pass
        ########################################
        ## COMPLETAR PARA TODAS LAS VERSIONES ##
        ########################################



    def get_positionals(self, terms, field='article'):
        """
        NECESARIO PARA LA AMPLIACION DE POSICIONALES

        Devuelve la posting list asociada a una secuencia de terminos consecutivos.

        param:  "terms": lista con los terminos consecutivos para recuperar la posting list.
                "field": campo sobre el que se debe recuperar la posting list, solo necesario se se hace la ampliacion de multiples indices

        return: posting list

        """
        pass
        ########################################################
        ## COMPLETAR PARA FUNCIONALIDAD EXTRA DE POSICIONALES ##
        ########################################################


    def get_stemming(self, term, field='article'):
        """
        NECESARIO PARA LA AMPLIACION DE STEMMING

        Devuelve la posting list asociada al stem de un termino.

        param:  "term": termino para recuperar la posting list de su stem.
                "field": campo sobre el que se debe recuperar la posting list, solo necesario se se hace la ampliacion de multiples indices

        return: posting list

        """
        
        stem = self.stemmer.stem(term)

        ####################################################
        ## COMPLETAR PARA FUNCIONALIDAD EXTRA DE STEMMING ##
        ####################################################


    def get_permuterm(self, term, field='article'):
        """
        NECESARIO PARA LA AMPLIACION DE PERMUTERM

        Devuelve la posting list asociada a un termino utilizando el indice permuterm.

        param:  "term": termino para recuperar la posting list, "term" incluye un comodin (* o ?).
                "field": campo sobre el que se debe recuperar la posting list, solo necesario se se hace la ampliacion de multiples indices

        return: posting list

        """

        ##################################################
        ## COMPLETAR PARA FUNCIONALIDAD EXTRA PERMUTERM ##
        ##################################################




    def reverse_posting(self, p):
        """
        NECESARIO PARA TODAS LAS VERSIONES

        Devuelve una posting list con todas las noticias excepto las contenidas en p.
        Util para resolver las queries con NOT.


        param:  "p": posting list


        return: posting list con todos los newid exceptos los contenidos en p

        """
        
        pass
        ########################################
        ## COMPLETAR PARA TODAS LAS VERSIONES ##
        ########################################



    def and_posting(self, p1, p2):
        """
        NECESARIO PARA TODAS LAS VERSIONES

        Calcula el AND de dos posting list de forma EFICIENTE

        param:  "p1", "p2": posting lists sobre las que calcular


        return: posting list con los newid incluidos en p1 y p2

        """
        
        pass
        ########################################
        ## COMPLETAR PARA TODAS LAS VERSIONES ##
        ########################################



    def or_posting(self, p1, p2):
        """
        NECESARIO PARA TODAS LAS VERSIONES

        Calcula el OR de dos posting list de forma EFICIENTE

        param:  "p1", "p2": posting lists sobre las que calcular


        return: posting list con los newid incluidos de p1 o p2

        """

        
        pass
        ########################################
        ## COMPLETAR PARA TODAS LAS VERSIONES ##
        ########################################


    def minus_posting(self, p1, p2):
        """
        OPCIONAL PARA TODAS LAS VERSIONES

        Calcula el except de dos posting list de forma EFICIENTE.
        Esta funcion se propone por si os es util, no es necesario utilizarla.

        param:  "p1", "p2": posting lists sobre las que calcular


        return: posting list con los newid incluidos de p1 y no en p2

        """

        
        pass
        ########################################################
        ## COMPLETAR PARA TODAS LAS VERSIONES SI ES NECESARIO ##
        ########################################################





    #####################################
    ###                               ###
    ### PARTE 2.2: MOSTRAR RESULTADOS ###
    ###                               ###
    #####################################


    def solve_and_count(self, query):
        """
        NECESARIO PARA TODAS LAS VERSIONES

        Resuelve una consulta y la muestra junto al numero de resultados 

        param:  "query": query que se debe resolver.

        return: el numero de noticias recuperadas, para la opcion -T

        """
        result = self.solve_query(query)
        print("%s\t%d" % (query, len(result)))
        return len(result)  # para verificar los resultados (op: -T)


    def solve_and_show(self, query):
        """
        NECESARIO PARA TODAS LAS VERSIONES

        Resuelve una consulta y la muestra informacion de las noticias recuperadas.
        Consideraciones:

        - En funcion del valor de "self.show_snippet" se mostrara una informacion u otra.
        - Si se implementa la opcion de ranking y en funcion del valor de self.use_ranking debera llamar a self.rank_result

        param:  "query": query que se debe resolver.

        return: el numero de noticias recuperadas, para la opcion -T
        
        """
        result = self.solve_query(query)
        if self.use_ranking:
            result = self.rank_result(result, query)   

        ########################################
        ## COMPLETAR PARA TODAS LAS VERSIONES ##
        ########################################




    def rank_result(self, result, query):
        """
        NECESARIO PARA LA AMPLIACION DE RANKING

        Ordena los resultados de una query.

        param:  "result": lista de resultados sin ordenar
                "query": query, puede ser la query original, la query procesada o una lista de terminos


        return: la lista de resultados ordenada

        """

        pass
        
        ###################################################
        ## COMPLETAR PARA FUNCIONALIDAD EXTRA DE RANKING ##
        ###################################################

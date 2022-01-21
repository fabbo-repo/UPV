import json
from nltk.stem.snowball import SnowballStemmer
import os
import re
import math


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

        # Indexar todos los ficheros .json (documentos) dentro de root
        for dir, subdirs, files in os.walk(root):
            for filename in files:
                if filename.endswith('.json'):
                    # Obtener path+filename
                    fullname = os.path.join(dir, filename)
                    # Indexar el documento de noticias
                    self.index_file(fullname)
        # Crear indice permuterm si se solicita
        if(self.permuterm): self.make_permuterm()
        # Crear indice stemming si se solicita
        if(self.stemming): self.make_stemming()
        
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

            # "jlist" es una lista con tantos elementos como noticias hay en el fichero,
            # cada noticia es un diccionario con los campos:
            #      "title", "date", "keywords", "article", "summary"
            #
            # En la version basica solo se debe indexar el contenido "article"
            #
            
            # Añadir un docid por cada fichero .json (documento)
            docid = len(list(self.docs)) 
            self.docs[docid] = filename
            # Posición inicial en el documento
            pos = 0
            
            # EXTRAER noticias del documento
            for new in jlist:
                # Añadir un newid a cada noticia
                newid = len(list(self.news))
                self.news[newid] = [docid,pos]
                pos += 1 # La posición de siguiente noticia en jlist

                # En caso de que se tome en cuenta la funcionaldad extra 
                # de multifield tendremos que revisar todos los fields de news
                # que corresponden a los campos de cada artículo, caso contrario
                # solo hay que revisar el field 'article'
                campos = [i[0] for i in self.fields] if self.multifield else ['article']
                for campo in campos:
                    # En caso de que no exista campo en index, 
                    # se crea su clave
                    if(campo not in self.index): self.index[campo] = {}

                    
                    content = new[campo]
                    tokens = content.split(" ")
                    # En caso de que no se deba tokenizar dicho campo
                    # se solo se toma el valor de content
                    if((campo, True) in self.fields):
                        tokens = self.tokenize(content)
                    
                    if(self.positional): self.indexPositionalTerms(tokens, campo, newid)
                    else: self.indexTerms(tokens, campo, newid)

    # Additional Method
    def indexTerms(self, tokens, campo, newid):
        # Para cada término del articulo, añadir docid del documento (filename) donde aparece dicho término
        # No repetir el mismo newid en la misma posting list
        for t in tokens:
            # Añadir al índice invertido la noticia donde aparece dicho término
            if t not in self.index[campo]:
                self.index[campo][t] = [newid]
            elif newid not in self.index[campo][t]: 
                self.index[campo][t].append(newid)

    # Additional Method
    def indexPositionalTerms(self, tokens, campo, newid):
        posTerm = 0
        for t in tokens:
            # Añadir al índice invertido la noticia donde aparece dicho término
            if t not in self.index[campo]:
                self.index[campo][t] = {newid:[posTerm]}
            elif newid not in self.index[campo][t]:
                self.index[campo][t][newid] = [posTerm]
            else:
                self.index[campo][t][newid].append(posTerm)
            posTerm += 1

    def tokenize(self, text):
        """
        NECESARIO PARA TODAS LAS VERSIONES

        Tokeniza la cadena "texto" eliminando simbolos no alfanumericos y dividiendola por espacios.
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
        for campo in self.index:
            for termino in self.index[campo]:
                stem = self.stemmer.stem(termino)
                # stem contiene el stem o verbo base del termino
                # llamamos a or_posting para obtener una posting list que contenga los
                # los ids de las noticias que contienen el stem y las que contienen 
                # el termino original sin hacer el stemmming
                if(campo not in self.sindex):
                    self.sindex[campo] = {}
                if(stem not in self.sindex[campo]):
                    self.sindex[campo][stem] = [termino]
                elif(termino not in self.sindex[campo][stem]):
                    self.sindex[campo][stem].append(termino)   
    
    
    def make_permuterm(self):
        """
        NECESARIO PARA LA AMPLIACION DE PERMUTERM

        Crea el indice permuterm (self.ptindex) para los terminos de todos los indices.

        """
        """ Para los términos del índice self.index"""
        for campo in self.index:
            for term in self.index[campo]:
                if campo not in self.ptindex:
                    self.ptindex[campo] = {}
                if term not in self.ptindex[campo]:
                    self.ptindex[campo][term] = self.permutar(term)

    # Additional Method
    def permutar(self, term):
        """
        Devuelve el índice permuterm en forma de lista
        """
        # permuterm cuyo simbolo especial es el dollar
        wildTerm = term+'$'
        # El índice permuterm de un término mide nº caracteres + 1
        res = [wildTerm]
        aux = wildTerm
        for _ in range(len(wildTerm)-1): # while i < len(wildTerm)-1:
            aux = aux[1:] + aux[0:1]
            res.append(aux)
        return res


    def show_stats(self):
        """
        NECESARIO PARA TODAS LAS VERSIONES
        
        Muestra estadisticas de los indices
        
        """
        
        print("========================================")
        print("Number of indexed days: "+str(len(list(self.docs))))
        print("----------------------------------------")
        print("Number of indexed news: "+str(len(list(self.news))))
        print("----------------------------------------")
        print("TOKENS:")
        for field in self.index:
            print("\t# of tokens in '"+field+"': "+str(len(list(self.index[field]))))
        print("----------------------------------------")
        
        print("PERMUTERM:")
        for field in self.ptindex:
            cont = 0
            for t in self.ptindex[field]: cont+=len(list(self.ptindex[field][t]))
            print("\t# of tokens in '"+field+"': "+str(cont))
        print("----------------------------------------")
        
        if(self.stemming):
            print("STEMS:")
            for field in self.sindex:
                print("\t# of stems in '"+field+"': "+str(len(list(self.sindex[field]))))
            print("----------------------------------------")
            
        p = "NOT" if not self.positional else ""
        print("Positional queries are "+p+" allowed.")
        print("========================================")


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
 
        res = []
        qpartes = query.split()
        i = len(qpartes) - 1
        busquedapos = False
 
        if len(qpartes) <= 2: #Dos opciones: o es un NOT término o es un término
            if len(qpartes) == 2 and qpartes[0] == "NOT": #NOT término
                res = self.solve_query(qpartes[1])
                res = self.reverse_posting(res)
            else: #solo un término
                qpartes[0] = qpartes[0].lower()
                if ':' in qpartes[0]:
                    prefqpartes = qpartes[0].split(':')
                    res = self.get_posting(prefqpartes[1], prefqpartes[0])
                else:
                    res = self.get_posting(qpartes[0])
                res = list(res)
                res.sort()
        else: #Para todo lo que es mayor que el simple término o su negación
            zonaderecha = qpartes[i]
            if ')' in qpartes[i]: #SI HAY UN PARÉNTESIS
                parentesis = len(re.split(r'(\))', qpartes[i])[1:])/2 #Calculamos el número de paréntesis en la primera palabra con regex, eliminamos el primer elemento del split ya que es la primera palabra, y dividimos entre dos ya que después de cada paréntesis hay un espacio en blanco
                j = i
                while parentesis > 0:
                    j -= 1
                    if ')' in qpartes[j]:
                        parentesis += len(re.split(r'(\))', qpartes[j])[1:])/2 #Si hay otro paréntesis dentro del nuestro, le sumamos uno a la variable de paréntesis que buscamos
                    if '(' in qpartes[j]:
                        parentesis -= len(re.split(r'(\()', qpartes[j])[1:])/2
                qpartes[j] = qpartes[j][1:]#Con esto y el siguiente eliminamos los dos paréntesis que hemos tomado, para cuando vayamos a calcular lo que hay dentro
                qpartes[i] = qpartes[i][:len(qpartes[i]) - 1]
                zonaderecha = qpartes[j:i+1]
                i = j #Ahora el puntero se encuentra al principio del paréntesis, por lo que podemos considerar todo este como un solo término calculado a partir de ahora y que actue como tal
                zonaderecha = " ".join(zonaderecha)
            if '"' in qpartes[i]: #BUSQUEDA POSICIONAL
                j = i
                enposicional = True
                while enposicional:
                    j -= 1
                    if '"' in qpartes[j]:
                        enposicional = False
                posicional = qpartes[j:i+1]
                res = self.get_posting(" ".join(posicional))
                i = j
                busquedapos = True
            if(busquedapos == False):
                res = self.solve_query(zonaderecha) #Sea el resultado de un paréntesis o un solo término, todo se ha calculado aquí
            if i == 0: #El paréntesis de apertura se encuentra en la primera palabra, por lo que todo lo de la derecha es el resultado que buscamos
                return res
            if qpartes[i-1] == "NOT":
                res = self.reverse_posting(res)
                if i-1 == 0:#Si el NOT es la primera palabra de la query, devolvemos la inversa de lo calculado
                    return res
                else:
                     i -= 1 #Restamos uno a i, y así realizamos el res como si nada posteriormente
            zonaizquierda = self.solve_query( " ".join(qpartes[:i-1]))
            if qpartes[i-1] == "AND":
                res = self.and_posting(zonaizquierda, res)
            elif qpartes[i-1] == "OR":
                res = self.or_posting(zonaizquierda, res)
        return res

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
        # Si term contiene más de una palabra y lleva comillas, se aplica get_positionals
        if len(term.split(" ")) > 1 and "\"" in term:
            return self.get_positionals(term.replace("\"","").split(" "), field)
        # Si term contiene más de una palabra y no lleva comillas, se aplica get_positionals
        elif len(term.split(" ")) > 1  and "\"" not in term:
            listTerm = term.split(" ")
            p = []
            for t in listTerm:
                p = self.and_posting(p, list(self.index[field][t]))
            return p
        # Si el término lleva algún comodin, se aplica get_permuterm
        elif "*" in term or "?" in term: 
            return self.get_permuterm(term, field)
        # Si se usa stemming y el término no lleva comillas, se aplica get_stemming
        elif self.use_stemming and "\"" not in term: 
            return self.get_stemming(term, field)
        # Para el caso de solo un término y solo se desea su posting list:
        else:
            # Si el término no se encuentra indexado devolvemos []
            if(term.replace("\"","") not in self.index[field]): return []
            # En caso de que se haya implementado la funcionalidad positional,
            # cada termino contiene un diccionario, si se indexa con positional 
            # este metodo debe devolver solo las claves de dicho diccionario, 
            # con list(...) se obtienen las claves en una lista, y si se indexa sin
            # positional cada termino tendra una lista por lo que al aplicar list(...)
            # se mantiene en una lista
            else: return list(self.index[field][term.replace("\"","")])



    def get_positionals(self, terms, field='article'):
        """
        NECESARIO PARA LA AMPLIACION DE POSICIONALES
 
        Devuelve la posting list asociada a una secuencia de terminos consecutivos.
 
        param:  "terms": lista con los terminos consecutivos para recuperar la posting list.
                "field": campo sobre el que se debe recuperar la posting list, solo necesario se se hace la ampliacion de multiples indices
 
        return: posting list
 
        """
        res = []
        # Si la lista de terms contiene algún termino
        if (len(terms)): 
            # subList contendrá todos los terminos menos el primero
            subList = terms[1:]
            
            # Se obtiene la posting list de todos los terminos de terms, aplicando
            # la intersección
            post = list(self.index[field][terms[0]])
            for t in subList: 
                post = self.and_posting(post, list(self.index[field][t]))
            # Se recorre la posting list de los terminos obtenida anteriormente
            for new in post:
                # Se recorre las posiciones del primer termino en cada noticia
                for pos in self.index[field][terms[0]][new]:
                    cont = 1
                    # Se recorren todos los terminos menos el primero
                    for t in subList:
                        # Se comprueba que las posiciones de los terminos sean sucesivas
                        if pos+cont in self.index[field][t][new]:
                            cont += 1
                        # Si el termino no se encuentra en la posición siguiente a la anterior,
                        # se salta a la siguiente posición del primer término
                        else: break
                    # Si cont es igual a la cantidad de terminos significa que todos los terminos
                    # van juntos, por lo que se añade dicha noticia al resultado
                    if cont == len(terms): 
                        res.append(new)
                        break # Si se añade una vez no hay que seguir con la misma noticia
        return res
        


    def get_stemming(self, term, field='article'):
        """
        NECESARIO PARA LA AMPLIACION DE STEMMING

        Devuelve la posting list asociada al stem de un termino.

        param:  "term": termino para recuperar la posting list de su stem.
                "field": campo sobre el que se debe recuperar la posting list, solo necesario se se hace la ampliacion de multiples indices

        return: posting list

        """
        stem = self.stemmer.stem(term)
        postingList = []
        # Si existe el stem en la lista de stems indexados, devolvemos la posting list
        if(stem in self.sindex[field]):
            termList = self.sindex[field][stem]
            for t in termList:
                postingList = self.or_posting(postingList, list(self.index[field][t]))
        # Si no existe el stem, devolvemos una lista vacía "postingList = []" 
        return postingList

    def get_permuterm(self, term, field='article'):
        """
        NECESARIO PARA LA AMPLIACION DE PERMUTERM

        Devuelve la posting list asociada a un termino utilizando el indice permuterm.

        param:  "term": termino para recuperar la posting list, "term" incluye un comodin (* o ?).
                "field": campo sobre el que se debe recuperar la posting list, solo necesario se se hace la ampliacion de multiples indices

        return: posting list

        """
        res = []
        flag = 0
        for t in self.ptindex[field]:
            for pTerm in self.ptindex[field][t]:
                if "?" in term: flag = True
                elif "*" in term: flag = False

                wildcardAlFinal = self.final(term,flag)
                # Si es prefijo de pTerm.
                if wildcardAlFinal[0:-1] == pTerm[0:len(wildcardAlFinal)-1]:
                    # Si le falta solo una letra ?
                    if flag and len(wildcardAlFinal) == len(pTerm):
                        res = self.or_posting(res, list(self.index[field][t]))
                    # Si le falta ninguna o más *
                    elif not flag and len(wildcardAlFinal)-1 <= len(pTerm):
                        res = self.or_posting(res, list(self.index[field][t]))
        return res

    # Additional Method
    def final(self, wildTerm, flag):
        """
        Deja el comodín al final. Por ejemplo, h*la$ -> la$h*
        """
        permTerm = wildTerm + "$"
        aux = []
        try:
            indiceWild = permTerm.find("?") if flag else permTerm.find("*")
        except: print("No se ha encontrado el símbolo ? o * en el wildTerm")
        for c in permTerm[indiceWild+1:]:
            aux.append(c) # la$
        for c in permTerm[0:indiceWild+1]:
            aux.append(c) # h*
        aux = "".join(aux) # la$h*
        return aux


    def reverse_posting(self, p):
        """
        NECESARIO PARA TODAS LAS VERSIONES

        Devuelve una posting list con todas las noticias excepto las contenidas en p.
        Util para resolver las queries con NOT.


        param:  "p": posting list


        return: posting list con todos los newid exceptos los contenidos en p

        """
        
        newsbutid = []
        newsids = list(self.news.keys())
        i = 0
        j = 0
        newsids.sort()
        while( i < len(p) and j < len (newsids)):
            if(p[i] == newsids[j]):
                i += 1; j += 1
            elif(p[i]<newsids[j]):
                i += 1
            else:
                newsbutid.append(newsids[j])
                j += 1
        if(i == len(p)):
            # Ha terminado de recorrer la lista p#
            while(j<len(newsids)):
                newsbutid.append(newsids[j])
                j += 1
        return newsbutid



    def and_posting(self, p1, p2):
        """
        NECESARIO PARA TODAS LAS VERSIONES

        Calcula el AND de dos posting list de forma EFICIENTE

        param:  "p1", "p2": posting lists sobre las que calcular


        return: posting list con los newid incluidos en p1 y p2

        """
        
        res = []
        i = 0; j = 0
        while(i<len(p1) and j<len(p2)):
            if(p1[i]==p2[j]):
                res.append(p2[j])
                i += 1; j += 1
            elif(p1[i]<p2[j]):
                i += 1
            else:
                j += 1
        return res

    def or_posting(self, p1, p2):
        """
        NECESARIO PARA TODAS LAS VERSIONES

        Calcula el OR de dos posting list de forma EFICIENTE

        param:  "p1", "p2": posting lists sobre las que calcular


        return: posting list con los newid incluidos de p1 o p2

        """
        res = []
        i = 0; j = 0
        while(i < len(p1) and j < len(p2)):
            if (p1[i] == p2[j]):
                res.append(p1[i])
                i += 1; j += 1
            elif (p1[i] > p2[j]):
                res.append(p2[j])
                j += 1
            else:
                res.append(p1[i])
                i += 1
        while(i < len(p1)):
            res.append(p1[i])
            i += 1
        while(j < len(p2)):
            res.append(p2[j])
            j += 1
        return res


    def minus_posting(self, p1, p2):
        """
        OPCIONAL PARA TODAS LAS VERSIONES

        Calcula el except de dos posting list de forma EFICIENTE.
        Esta funcion se propone por si os es util, no es necesario utilizarla.

        param:  "p1", "p2": posting lists sobre las que calcular


        return: posting list con los newid incluidos de p1 y no en p2

        """
        posting_list = []
        
        i = 0; j = 0
        while i < len(p1) and j < len(p2):
            if p1[i] == p2[j]:
                i += 1; j += 1
            elif p1[i] > p2[j]:
                j += 1
            else:
                posting_list.append(p1[i])
                i += 1
        while i < len(p1):
            posting_list.append(p1[i])
            i += 1
        
        return posting_list


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
        print("========================================")
        print("Query: "+query)
        result = self.solve_query(query)
        if self.use_ranking:
            result = self.rank_result(result, query)
        print("Number of results: "+str(len(result)))
        print("--------------------")
        ind = 1; 
        # En caso de que self.show_all sea True, se muestran todas las noticias, sino 100
        maximo = len(result) if self.show_all else min(100, len(result))
        for newid in result:
            if ind > maximo: break
            # Posicion de la noticia en el documento
            pos = self.news[newid][1]
            # Se obtiene el path del documento a través de su docId
            path = self.docs[self.news[newid][0]]
            with open(path) as fh:
                jlist = json.load(fh)
            # Se calcula la puntuación, si no se usa el ranking entonces es 0
            score = self.weight[query][newid] if self.use_ranking else 0
            print("#"+str(ind)+"\n"+str(score)+"\n"+str(newid)+"\ndate: "
                +jlist[pos]['date']+"\ntitle: "+jlist[pos]['title']
                +"\nkeywords: "+jlist[pos]['keywords'])
            ind += 1
            
            if self.show_snippet:
                fields = [i[0] for i in self.fields]
                qterms = self.procesarQuery(query.split(" "))
                field='article' # Para el snippet solo considero el campo articulo
                
                content = self.tokenize(jlist[pos][field])
                first = None; last = None; pos2 = 0
                for t in content:
                    if t in qterms and first is None: first = pos2
                    if t in qterms: last = pos2; 
                    pos2+=1
                posIni1 = 0 if first-3<0 else first-3
                posFin1 = len(content)-1 if first+6>len(content)-1 else first+6
                res = ""
                posIni2 = 0 if last-7<0 else last-7
                posFin2 = len(content)-1 if last+2>len(content)-1 else last+2
                for i in list(range(posIni1,posFin1+1)): res += content[i]+" "
                res+=" ... "
                for i in list(range(posIni2,posFin2+1)): res += content[i]+" "
                print("snippet: "+res)
                print("--------------------")
        
        return len(result)  # para verificar los resultados (op: -T)

    # Adittional term, falta considerar comillas, stemming y comodines
    def procesarQuery(self, query):
        qterms = query
        while "AND" in qterms: qterms.remove("AND") 
        while "OR" in qterms: qterms.remove("OR") 
        while "NOT" in qterms: qterms.remove("NOT") 
        i = 0 
        while i < len(qterms): 
            if ":" in qterms[i]: qterms.pop(i) # Si está : significa que es otro campo diferente de article
            else: i+=1
        tam = range(len(qterms))
        for i in tam:
            # Eliminar parentesis
            if ")" in qterms[i]: qterms[i] = qterms[i].replace(")","") 
            if "(" in qterms[i]: qterms[i] = qterms[i].replace("(","")
            # Transformar términos con comodines
            if "*" in qterms[i] or "?" in qterms[i]:
                fields = [i[0] for i in self.fields]
                field='article' if qterms[0] not in fields else qterms[0]
                for t in self.ptindex[field]:
                    for pTerm in self.ptindex[field][t]:
                        if "?" in qterms[i]: flag = True
                        elif "*" in qterms[i]: flag = False
                        wildcardAlFinal = self.final(qterms[i],flag)
                        # Si es prefijo de pTerm.
                        if wildcardAlFinal[0:-1] == pTerm[0:len(wildcardAlFinal)-1]:
                            # Si le falta solo una letra ?
                            if flag and len(wildcardAlFinal) == len(pTerm):
                                qterms.append(t)
                            # Si le falta ninguna o más *
                            elif not flag and len(wildcardAlFinal)-1 <= len(pTerm):
                                qterms.append(t)
            elif self.use_stemming and "\"" not in qterms[i]: 
                qterms.append(self.stemmer.stem(qterms[i]))
            # Eliminar comillas
            if "\"" in qterms[i]: qterms[i] = qterms[i].replace("\"","")  
        return qterms
    
    
    def rank_result(self, result, query):
        """
        NECESARIO PARA LA AMPLIACION DE RANKING

        Ordena los resultados de una query.

        param:  "result": lista de resultados sin ordenar
                "query": query, puede ser la query original, la query procesada o una lista de terminos


        return: la lista de resultados ordenada

        """
        totaldocs = len(self.news.keys())
        terminos = self.tokenize(query)
        
        for termino in terminos:
            idf = math.log10(totaldocs/len(self.get_posting(termino))) #idf
            for newid in result:
                if ':' in termino:
                    divter = termino.split(':')
                    tf = 1+math.log10(len(self.index[divter[0]][divter[1]][newid])) if newid in self.index[divter[0]][divter[1]] else 0 #tf
                else:
                    tf = 1+math.log10(len(self.index['article'][termino][newid])) if newid in self.index['article'][termino] else 0 #tf
                if query not in self.weight:
                    self.weight[query] = {}
                    self.weight[query][newid] = tf * idf
                else:
                    if newid not in self.weight[query]:
                        self.weight[query][newid] = tf * idf
                    else:
                        self.weight[query][newid] += tf * idf

        result = sorted(self.weight[query], key=self.weight[query].get)

        return result[len(result)-1::-1]

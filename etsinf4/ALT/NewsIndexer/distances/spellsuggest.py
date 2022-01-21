# -*- coding: utf-8 -*-
import re
import sys
try :
    import threshold_distances as distan
    import trie_distances as trie_distan
    from utils.trie import Trie
except :
    import distances.threshold_distances as distan
    import distances.trie_distances as trie_distan
    from distances.utils.trie import Trie
    
class SpellSuggester:

    """
    Clase que implementa el método suggest para la búsqueda de términos.
    """

    def __init__(self, vocab_file_path):
        """Método constructor de la clase Spelluggester

        Construye una lista de términos únicos (vocabulario),
        que además se utiliza para crear un trie.

        Args:
            vocab_file (str): ruta del fichero de texto para cargar el vocabulario.

        """

        self.vocabulary  = self.build_vocab(vocab_file_path, tokenizer=re.compile("\W+"))

    def build_vocab(self, vocab_file_path, tokenizer):
        """Método para crear el vocabulario.

        Se tokeniza por palabras el fichero de texto,
        se eliminan palabras duplicadas y se ordena
        lexicográficamente.

        Args:
            vocab_file (str): ruta del fichero de texto para cargar el vocabulario.
            tokenizer (re.Pattern): expresión regular para la tokenización.
        """
        with open(vocab_file_path, "r", encoding='utf-8') as fr:
            vocab = set(tokenizer.split(fr.read().lower()))
            vocab.discard('') # por si acaso
            return sorted(vocab)

    def count_distance(self, word1, word2) :
        distance = 0; lista=[]; d1=d2={}
        for c in word1: 
            if c not in d1 : d1[c]=1
            else: d1[c]+=1

        for c in word2: 
            if c not in d2 : d2[c]=1
            else: d2[c]+=1

        # In lista we save the keys of the dictionaries d1 and d2
        lista = set(d1).union(set(d2))
        for c in lista: 
            if c in d1 and c in d2 and d1[c] != d2[c]: distance += abs(d1[c]-d2[c])
            elif c not in d1: distance += d2[c]
            elif c not in d2: distance += d1[c]
        
        return distance

    def suggest(self, term, distance="levenshtein", threshold=2):

        """Método para sugerir palabras similares siguiendo la tarea 3.

        Args:
            term (str): término de búsqueda.
            distance (str): algoritmo de búsqueda a utilizar
                {"levenshtein", "restricted", "intermediate", "trielevenshtein"}.
            threshold (int): threshold para limitar la búsqueda
                puede utilizarse con los algoritmos de distancia mejorada de la tarea 2
                o filtrando la salida de las distancias de la tarea 2
        """

        assert distance in ["levenshtein", "restricted", "intermediate","trielevenshtein"]
        
        results = {} # diccionario termino:distancia
        # Check the type of edit distance its given
        if distance == 'levenshtein':
            callAux =  distan.dp_levenshtein_threshold
        elif distance == 'restricted':
            callAux = distan.dp_restricted_damerau_threshold
        elif distance == 'intermediate':
            callAux = distan.dp_intermediate_damerau_threshold
        elif distance == "trielevenshtein" :
            return trie_distan.dp_levenshtein_trie(term, self.trie, threshold)
        
        # Loop to check the distance between each word on the vocabulary 
        # and the term we have on the arguments
        for word in self.vocabulary:
            # Optimistic level of difference between lengths
            if(abs(len(word)-len(term)) > threshold) : 
                distancia = threshold+1
            # Optimistic level based on the number of ocurrences of each character
            elif(distance == 'levenshtein' and \
                self.count_distance(word,term) > threshold) : 
                distancia = threshold+1
            else : 
                distancia = callAux(word,term,threshold)
            
            # Check if the actual distance is lower than the threshold, 
            # if not, get the next word
            if distancia <= threshold:
                if word in results:
                    results[word].append(distancia)
                else:
                    results[word] = distancia
        
        return results

    

class TrieSpellSuggester(SpellSuggester):
    """
    Clase que implementa el método suggest para la búsqueda de términos y añade el trie
    """
    def __init__(self, vocab_file_path):
        super().__init__(vocab_file_path)
        self.trie = Trie(self.vocabulary)
    
if __name__ == "__main__":
    try:
        if(len(sys.argv) != 3) :
            print('\nFaltan argumentos, deben ser 2:\
                \n\t1- path del fichero a analizar\
                \n\t2- distancia a usar \
                (levenshtein, restricted, intermediate, trielevenshtein)\
                \n\nPrueba con:\
                \n\tpython spellsuggest.py ../corpora/quijote.txt levenshtein\n')
            exit()
        path = sys.argv[1]
        option = sys.argv[2]
        spellsuggester = TrieSpellSuggester(path)
        print(spellsuggester.suggest("casa",option))
        # cuidado, la salida es enorme print(suggester.trie)
    except Exception as err:
        print("\n spellsuggest class error :",sys.exc_info[0])
        sys.exit(-1)

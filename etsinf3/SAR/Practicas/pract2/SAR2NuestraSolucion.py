#! -*- encoding: utf8 -*-

## Nombres: 
# - Lishuang Sun (María)
# - Fabián Scherle Carboneres

########################################################################
########################################################################
###                                                                  ###
###  Todos los métodos y funciones que se añadan deben documentarse  ###
###                                                                  ###
########################################################################
########################################################################

import argparse
import re
import sys
import os
from operator import itemgetter

def sort_dic_by_values(d, asc=True):
    return sorted(d.items(), key=lambda a: (-a[1], a[0]))

class WordCounter:

    def __init__(self):
        """
           Constructor de la clase WordCounter
        """
        self.clean_re = re.compile(r'\w+')

    def write_stats(self, filename, stats, use_stopwords, bigrams, full):
        """
        Este método escribe en fichero las estadísticas de un texto
            
        :param 
            filename: el nombre del fichero destino.
            stats: las estadísticas del texto.
            use_stopwords: booleano, si se han utilizado stopwords
            bigrams: booleano, si se deben calcular bigramas *se ha añadido*
            full: boolean, si se deben mostrar las stats completas
        :return: None
        """

        with open(filename, 'w', encoding='utf-8') as fh:
            npalabras = stats['nwords']; nlineas = stats['nlines']
            simbolos = stats['symbol']; palabras = stats['word'] # vocabulario
            
            res = "Lines: " + str(nlineas) + "\n" 
            res += "Number words (including stopwords): " + str(npalabras) + "\n"
            
            # En caso de que se utilicen stopwords, para excluirlas se recorre 
            # el vocabulario (no las incluye) para sumar las ocurrencias de cada palabra
            if(use_stopwords): 
                res += "Number words (without stopwords): "
                sum = 0
                for aux in palabras.values() : sum += aux
                res += str(sum) + "\n"
            
            res += "Vocabulary size: " + str(len(palabras)) + "\n"
            
            res += "Number of symbols: " 
            sum = 0
            for aux in simbolos.values() : sum += aux
            res += str(sum) + "\n"

            res += "Number of different symbols: " + str(len(simbolos)) + "\n"

            res += "Words (alphabetical order):" + "\n"
            i = 0
            # Con sorted se ordena alfabéticamente el diccionario de palabras (vocabulario)
            # y para cada elemento del diccionario se toma su clave y valor, en caso
            # de full se mostraran todos los elementos, caso contrario solo los primeros 20
            for clave, valor in sorted(palabras.items()) :
                res += "\t" + clave + ": " + str(valor) + "\n"
                if(not full):
                    i+=1
                    if i == 20: break
            res += "Words (by frequency):" + "\n"
            i = 0
            # En el sorted externo se utiliza key=itemgetter(1) para ordenar por ocurrencias
            # reverse = True indica que se ordena de mayor a menor
            # En el sorted interno se pretende ordenar alfabéticamente el diccionario, para que 
            # en caso de empate en el sorted externo se encuentren ordenados alfabéticamente
            for clave, valor in sorted(sorted(palabras.items()), key = itemgetter(1), reverse=True) :
                res += "\t" + clave + ": " + str(valor) + "\n"
                if(not full):
                    i+=1
                    if i == 20: break
                
            res += "Symbols (alphabetical order):" + "\n"
            i = 0
            for clave, valor in sorted(simbolos.items()) :
                res += "\t" + clave + ": " + str(valor) + "\n"
                if(not full):
                    i+=1
                    if i == 20: break
            res += "Symbols (by frequency):" + "\n"
            i = 0
            for clave, valor in sorted(sorted(simbolos.items()), key = itemgetter(1), reverse=True) :
                res += "\t" + clave + ": " + str(valor) + "\n"
                if(not full):
                    i+=1
                    if i == 20: break
            
            if(bigrams) :
                bipalabras=stats['biword']; bisimbolos=stats['bisymbol']

                res += "Word pairs (alphabetical order):" + "\n"
                i = 0
                for clave, valor in sorted(bipalabras.items()) :
                    res += "\t" + clave + ": " + str(valor) + "\n"
                    if(not full):
                        i+=1
                        if i == 20: break
                res += "Word pairs (by frequency):" + "\n"
                i = 0
                for clave, valor in sorted(sorted(bipalabras.items()), key = itemgetter(1), reverse=True) :
                    res += "\t" + clave + ": " + str(valor) + "\n"
                    if(not full):
                        i+=1
                        if i == 20: break

                res += "Symbol pairs (alphabetical order):" + "\n"
                i = 0
                for clave, valor in sorted(bisimbolos.items()) :
                    res += "\t" + clave + ": " + str(valor) + "\n"
                    if(not full):
                        i+=1
                        if i == 20: break
                res += "Symbol pairs (by frequency):" + "\n"
                i = 0
                for clave, valor in sorted(sorted(bisimbolos.items()), key = itemgetter(1), reverse=True) :
                    res += "\t" + clave + ": " + str(valor) + "\n"
                    if(not full):
                        i+=1
                        if i == 20: break

            fh.write(res)


    def file_stats(self, filename, lower, stopwordsfile, bigrams, full):
        """
        Este método calcula las estadísticas de un fichero de texto

        :param 
            filename: el nombre del fichero.
            lower: booleano, se debe pasar todo a minúsculas?
            stopwordsfile: nombre del fichero con las stopwords o None si no se aplican
            bigram: booleano, se deben calcular bigramas?
            full: booleano, se deben montrar la estadísticas completas?

        :return: None
        """

        stopwords = [] if stopwordsfile is None else open(stopwordsfile).read().split()

        # variables for results

        sts = {
                'nwords': 0,
                'nlines': 0,
                'word': {},
                'symbol': {}
                }

        if bigrams:
            sts['biword'] = {}
            sts['bisymbol'] = {}
        
        
        # Obtenemos una lista cuyo primer elemento es nombre del fichero 
        # y segundo elemento su extensión (si no tiene será '')
        path = os.path.splitext(filename)
        extra = ""
        if lower : extra += "l"
        if stopwordsfile is not None : extra += "s"
        if bigrams : extra += "b"
        if full : extra += "f"

        if len(extra) == 0 : new_filename = path[0] + "_stats" + path[1]
        else : new_filename = path[0] + "_" + extra + "_stats" + path[1]

        nPalabras = 0; nLineas = 0
        vocabulario = {}; simbolos = {}
        biwords = {}; bisymbols = {}

        with open(filename, 'r', encoding='utf-8') as fd :
            for line in fd:
                if lower: line = line.lower()
                lineWords = self.clean_re.findall(line)
                
                nPalabras += len(lineWords)
                nLineas += 1
                
                # Si es una stopword se elimina de lineWords.
                # stopwords puede ser una lista vacía si no se especifica el "-s path"
                for s in stopwords : 
                    while s in lineWords : lineWords.remove(s)
                    
                i = 0 # i contiene la posición de cada palabra en lineWords
                # Para cada una de las palabras en lineWords
                for w in lineWords :
                    # Si no existe la clave en el diccionario la crea con valor 1,
                    # caso contrario suma 1 a su valor
                    if w not in vocabulario : vocabulario[w] = 1
                    else: vocabulario[w] += 1
                    j = 0 # j contiene la posición de cada caracter en w
                    for char in w :
                        if char not in simbolos : simbolos[char] = 1
                        else : simbolos[char] += 1

                        if bigrams:
                            # Si char no es el último caracter de la palabra
                            if j < len(w)-1 :
                                if char+w[j+1] not in bisymbols: 
                                    bisymbols[char+w[j+1]] = 1
                                else: bisymbols[char+w[j+1]] += 1
                                j += 1
                    if bigrams :
                        # Si lineWords[i] es la primera palabra agregamos dicha palabra con '$' delante
                        if i == 0 : 
                            if '$ '+lineWords[i] not in biwords : 
                                biwords['$ '+lineWords[i]] = 1
                            else: biwords['$ '+lineWords[i]] += 1
                        # Si lineWords[i] no es la última palabra agregamos dicha palabra junto con su consecuente
                        if i < len(lineWords)-1 :
                            if lineWords[i]+' '+lineWords[i+1] not in biwords: 
                                biwords[lineWords[i]+' '+lineWords[i+1]] = 1
                            else: biwords[lineWords[i]+' '+lineWords[i+1]] += 1
                            i += 1
                        # Si lineWords[i] es la última palabra agregamos dicha palabra con '$' detrás
                        elif i == len(lineWords)-1 : 
                            if lineWords[i] + ' $' not in biwords : 
                                biwords[lineWords[i] + ' $'] = 1
                            else: biwords[lineWords[i] + ' $'] += 1
                        
        # Guardamos las estadísticas en el diccionario sts
        sts['nwords'] = nPalabras
        sts['nlines'] = nLineas
        sts['word'] = vocabulario
        sts['symbol'] = simbolos
        if bigrams:
            sts['biword'] = biwords
            sts['bisymbol'] = bisymbols
        
        self.write_stats(new_filename, sts, stopwordsfile is not None, bigrams, full)


    def compute_files(self, filenames, **args):
        """
        Este método calcula las estadísticas de una lista de ficheros de texto

        :param 
            filenames: lista con los nombre de los ficheros.
            args: argumentos que se pasan a "file_stats".

        :return: None
        """

        for filename in filenames:
            self.file_stats(filename, **args)

if __name__ == "__main__":

    parser = argparse.ArgumentParser(description='Compute some statistics from text files.')
    parser.add_argument('file', metavar='file', type=str, nargs='+',
                        help='text file.')

    parser.add_argument('-l', '--lower', dest='lower',
                        action='store_true', default=False, 
                        help='lowercase all words before computing stats.')

    parser.add_argument('-s', '--stop', dest='stopwords', action='store',
                        help='filename with the stopwords.')

    parser.add_argument('-b', '--bigram', dest='bigram',
                        action='store_true', default=False, 
                        help='compute bigram stats.')

    parser.add_argument('-f', '--full', dest='full',
                        action='store_true', default=False, 
                        help='show full stats.')

    args = parser.parse_args()
    wc = WordCounter()
    wc.compute_files(args.file,
                     lower=args.lower,
                     stopwordsfile=args.stopwords,
                     bigrams=args.bigram,
                     full=args.full)



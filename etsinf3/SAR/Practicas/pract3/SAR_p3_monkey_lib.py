#!/usr/bin/env python
#! -*- encoding: utf8 -*-
# 3.- Mono Library

import pickle
import random
import re
import sys

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



def sort_index(d):
    for k in d:
        l = sorted(((y, x) for x, y in d[k].items()), reverse=True)
        d[k] = (sum(x for x, _ in l), l)


class Monkey():

    def __init__(self):
        self.r1 = re.compile('[.;?!]')
        self.r2 = re.compile(r'\W+')


    def index_sentence(self, sentence, tri):
        #############
        # Tras el split en index_sentence() —> ' mundo' =>  ('' y 'mundo'). 
        # Por lo que hay que filtrar otra vez los x==''.
        line = ['$']; line.extend([x for x in self.r2.split(sentence) if x!='']) 
        line.append('$')
        # Una frase puede tener bigramas si tiene al menos tres palabras, incluidos los dos '$'
        if len(line) > 2 :
            bi = self.index['bi']
            # La i apunta hasta la penúltima palabra porque en cada iteración cogemos dos palabras
            for i in range(len(line)-1) :
                word1 = line[i]; word2 = line[i+1]
                if word1 not in bi : bi[word1] = {word2 : 1} 
                else :
                    if word2 not in bi[word1] : bi[word1][word2] = 1
                    else : bi[word1][word2] += 1
            # Índice de trigramas
            if tri:
                tri = self.index['tri']
                # La i apunta hasta la antepenúltima palabra porque en cada iteración cogemos tres palabras
                for i in range(len(line)-2) :
                    word1 = line[i]; word2 = line[i+1]; word3 = line[i+2]
                    if (word1,word2) not in tri : tri[(word1,word2)] = {word3 : 1} 
                    else :
                        if word3 not in tri[(word1,word2)] : tri[(word1,word2)][word3] = 1
                        else : tri[(word1,word2)][word3] += 1
                self.index['tri'] = tri
            self.index['bi'] = bi  
        #############

    def compute_index(self, filename, tri):
        self.index = {'name': filename, "bi": {}}
        if tri:
            self.index["tri"] = {}
        
        #############
        with open(filename, 'r', encoding='utf-8') as fd :
            line = fd.read()
            line = line.replace("\n\n", ".")
            # Se obtiene una lista al hacer split de r1 sobre line, separandola por 
            # por los diferentes símbolos de puntuación, en caso de que estén repetidos
            # como por ejemplo '...' o '??' obtendremos elementos vacios que se deben filtrar 
            # para ello se usa la siguiente expresión
            line = [x for x in self.r1.split(line.lower()) if x!='']
            for sentence in line :
                self.index_sentence(sentence,tri)
        #############

        sort_index(self.index['bi'])
        if tri:
            sort_index(self.index['tri'])
        

    def load_index(self, filename):
        with open(filename, "rb") as fh:
            self.index = pickle.load(fh)


    def save_index(self, filename):
        with open(filename, "wb") as fh:
            pickle.dump(self.index, fh)


    def save_info(self, filename):
        with open(filename, "w") as fh:
            print("#" * 20, file=fh)
            print("#" + "INFO".center(18) + "#", file=fh)
            print("#" * 20, file=fh)
            print("filename: '%s'\n" % self.index['name'], file=fh)
            print("#" * 20, file=fh)
            print("#" + "BIGRAMS".center(18) + "#", file=fh)
            print("#" * 20, file=fh)
            for word in sorted(self.index['bi'].keys()):
                wl = self.index['bi'][word]
                print("%s\t=>\t%d\t=>\t%s" % (word, wl[0], ' '.join(["%s:%s" % (x[1], x[0]) for x in wl[1]])), file=fh)
            if 'tri' in self.index:
                print(file=fh)
                print("#" * 20, file=fh)
                print("#" + "TRIGRAMS".center(18) + "#", file=fh)
                print("#" * 20, file=fh)
                for word in sorted(self.index['tri'].keys()):
                    wl = self.index['tri'][word]
                    print("%s\t=>\t%d\t=>\t%s" % (word, wl[0], ' '.join(["%s:%s" % (x[1], x[0]) for x in wl[1]])), file=fh)


    def generate_sentences(self, n=10):
        #############
        '''
        bi = self.index['bi']
        for i in range(n) :
            sentence = []
            for j in range(25) :
                if j == 0 : 
                    ini = bi['$']; words = dict(ini[1])
                    sentence.append((random.choices(list(words.values()), weights=list(words.keys()), k = 1))[0])
                elif sentence[j-1] == '$' :
                    sentence.remove('$'); break
                else : 
                    next = bi[sentence[j-1]]; words = dict(next[1])
                    sentence.append((random.choices(list(words.values()), weights=list(words.keys()), k = 1))[0])
        '''
        tri = self.index['tri']
        for i in range(n) :
            sentence = []
            for j in range(25) :
                if j == 0 :
                    # words es una lista de las palabras e2 que le siguen a '$'
                    words = [e2 for e1, e2 in tri if e1=='$']
                    # nums es la lista de las ocurrencias de dichos par de palabras ('$',e2)
                    nums = [tri[(e1,e2)][0] for e1, e2 in tri if e1=='$']
                    # Cuando j=1, podremos acceder a la lista de palabras que le siguen a ('$',e2), siendo e2 elegida aleatoriamente
                    sentence.append('$')
                    sentence.append((random.choices(words, weights=nums, k = 1))[0])
                elif sentence[j] == '$' :
                    # Eliminar el que añadimos al principio, y si la palabra random de la iteración anterior es '$', eliminarla
                    sentence.remove('$'); sentence.remove('$'); break
                else :
                    # Para j>0
                    # words es una lista de las palabras e2 que le siguen a la tupla de la iteración anterior, nums contiene las ocurrencias de e2
                    words = []; nums = []
                    for e1, e2 in tri[sentence[j-1], sentence[j]][1] :
                        nums.append(e1)
                        words.append(e2)
                    # Puede salir '$'
                    sentence.append((random.choices(words, weights=nums, k = 1))[0])
                    if j == 24 : 
                        # Si en la última iteración, eliminar el '$' añadido cuando j=0
                        sentence.remove('$')
                        if '$' in sentence : 
                            # En caso de que la última palabra producida sea '$', se elimina también 
                            sentence.remove('$')  
            print(" ".join(sentence))
        #############


if __name__ == "__main__":
    print("Este fichero es una librería, no se puede ejecutar directamente")



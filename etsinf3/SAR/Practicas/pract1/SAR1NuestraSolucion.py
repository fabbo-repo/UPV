#!/usr/bin/env python
#! -*- encoding: utf8 -*-

# 1.- Pig Latin
# Autores del código: Lishuang Sun (María) y Fabián Scherle Carboneres

import sys
import re
import os


class Translator():

    def __init__(self, punt=None):
        """
        Constructor de la clase Translator

        :param punt(opcional): una cadena con los signos de puntuación
                                que se deben respetar
        :return: el objeto de tipo Translator
        """
        if punt is None:
            punt = ".,;?!"
        self.re = re.compile(r"(\w+)([" + punt + r"]*)")

    def translate_word(self, word):
        """
        Recibe una palabra en inglés y la traduce a Pig Latin

        :param word: la palabra que se debe pasar a Pig Latin
        :return: la palabra traducida
        """
        
        # Si es cadena vacía o no comienza con una letra, se deja igual
        if len(word) == 0 or not word[0].isalpha() : return word
        
        vocales = 'aeiouy'
        # En new_word irá la palabra traducida
        aux = new_word = word.lower() # Se pasa a minúsculas

        # Comprobamos si empieza por vocal o consonante
        # -> en caso de vocal agrega 'yay'
        # -> en caso de consonante mueve la consonante al final y agrega 'ay' 
        i = 0
        while i < len(aux) and aux[i] not in vocales:
            new_word = new_word[1:] + aux[i]
            i += 1
        if i == 0: new_word = new_word +'yay'
        else: new_word = new_word +'ay'

        # Comprobamos si las letras de word están en mayúsculas o comienza con mayúscula 
        if word.isupper() :
            new_word = new_word.upper()
        elif word[0].isupper() :
            new_word = new_word.capitalize()
        return new_word

    def translate_sentence(self, sentence):
        """
        Recibe una frase en inglés y la traduce a Pig Latin

        :param sentence: la frase que se debe pasar a Pig Latin
        :return: la frase traducida
        """

        # En aux guardamos una lista de tuplas de las palabras de sentence
        # El primer elemento de la tupla son las letras de la palabra 
        # El segundo elemento de la tupla son los signos de puntuación,
        # incluidos en el re.compile definido en el constructor,
        # con los que finaliza la palabra
        aux = self.re.findall(sentence)
        # new_sentence contendrá la frase u oración traducida
        new_sentence = []

        # se traduce cada palabra
        for i in aux :
            new_sentence.append( self.translate_word(i[0]) + i[1] )
        
        new_sentence = ' '.join(new_sentence)
        
        return new_sentence

    def translate_file(self, filename):
        """
        Recibe un fichero y crea otro con su tradución a Pig Latin

        :param filename: el nombre del fichero que se debe traducir
        :return: True / False 
        """
        
        # En caso de algún error se devuelve False, caso contrario True
        try:
            # Obtengo una lista cuyo primer elemento es nombre del fichero 
            # y segundo elemento su extensión (si no tiene será '')
            pathList = os.path.splitext(filename)
            # Antes de la extensión debe ir la cadena '_latin'
            path = pathList[0] + '_latin' + pathList[1]
            
            with open(path,'w') as fModificado, open(filename,'r') as fOriginal :
                for line in fOriginal : # un for para traducir cada línea del fichero
                    fModificado.write(self.translate_sentence(line)+'\n')
        except: 
            return False
        return True

if __name__ == "__main__":
    if len(sys.argv) > 2:
        print(f'Syntax: python {sys.argv[0]} [filename]')
        exit()
    t = Translator()
    if len(sys.argv) == 2:
        if not t.translate_file(sys.argv[1]) :
            print('error')
    else:
        sentence = input("ENGLISH: ")
        while len(sentence) > 1:
            print("PIG LATIN:", t.translate_sentence(sentence))
            sentence = input("ENGLISH: ")

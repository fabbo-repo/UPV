#!/usr/bin/env python
#! -*- encoding: utf8 -*-

# 1.- Pig Latin

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
        # En new_word irá la palabra traducida
        new_word = ''
        
        if len(word) == 0 : return word
        
        # Si no comienza con una letra, se deja igual
        if not word[0].isalpha() : return word
        
        vocales = ['a','e','i','o','u','y']
        aux = word.lower()
        # Compruebo si empieza por vocal o consonante
        # En caso de vocal agrega 'yay'
        # En caso de consonante mueve la consonante al final y agrega 'ay' 
        if aux[0] in vocales :
            new_word = aux + "yay"
        else :
            i = 0
            while i < len(aux) and not (aux[i] in vocales) : i+=1
            if i == (len(aux)-1) : new_word = aux + 'ay'
            else : new_word = aux[i:len(aux)] + aux[0:i] + 'ay'

        # Compruebo si las letras de word están en mayúsculas o comienza con mayúscula 
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

        # En aux guardo una lista de tuplas de las palabras de sentence
        # EL primer elemento de la tupla son las letras de la palabra 
        # EL segundo elemento de la tupla son los símbolos de puntuación 
        # con los que finaliza la palabra
        aux = self.re.findall(sentence)
        # new_sentence contiene la palabra traducida
        new_sentence = ''

        # se traduce cada palabra
        for i in aux :
            new_sentence += self.translate_word(i[0]) + i[1] + ' '
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
            
            # fOriginal -> fichero del que se leerá el texto a traducir
            fOriginal = open(filename, "r")
            # fModificado -> fichero en el que se escribirá el texto traducido
            fModificado = open(path, "w")
            
            # En lines obtengo una lista con las líneas del fichero leido 
            lineas = list(fOriginal.read().split("\n"))
            # En res obtendré una lista con las líneas traducidas 
            res = []
            
            for i in range(len(lineas)) : # un for para traducir todas las líneas 
                res.append(self.translate_sentence((lineas[i]))+'\n')
            
            fModificado.writelines(res)

            fOriginal.close()
            fModificado.close()
            return True
        except IOError:
            return False
        else:
            fOriginal.close()
            fModificado.close()
            return False

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

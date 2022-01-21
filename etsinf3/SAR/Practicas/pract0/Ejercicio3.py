import string

def anagramaPerfecto(cadena1,cadena2):
    c1 = cadena1
    c2 = cadena2
    punt = ["?", "¿", "¡", "!", " ", ",", ".", ";", ":","-","_","\"","\'","[","]","{","}","(",")"]
    for p in punt:
        if c1.find(p)!=-1:
            c1 = c1.lower().replace(p,"")
        if c2.find(p)!=-1:
            c2 = c2.lower().replace(p,"")

    for c in c1:
        if(c1.count(c) != c2.count(c)):
            return False
        c1 = c1.replace(c,"")
        c2 = c2.replace(c,"")

    return c1==c2

print(anagramaPerfecto('Life on mars','alien forms'))

print(anagramaPerfecto('sadasda','fdgh fdg'))
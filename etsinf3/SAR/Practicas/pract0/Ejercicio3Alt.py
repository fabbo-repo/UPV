import string

def anagramaPerfecto(cadena1,cadena2):
    c1 = cadena1.lower()
    c2 = cadena2.lower()
    for i in c1:
        if not i.isalpha():
            c1 = c1.replace(i,"")
    for i in c2:
        if not i.isalpha():
            c2 = c2.replace(i,"")
    
    for c in c1:
        if(c1.count(c) != c2.count(c)):
            return False
        c1 = c1.replace(c,"")
        c2 = c2.replace(c,"")
    return c1==c2

print(anagramaPerfecto('Life on mars','alien forms'))

print(anagramaPerfecto('sadasda','fdgh fdg'))
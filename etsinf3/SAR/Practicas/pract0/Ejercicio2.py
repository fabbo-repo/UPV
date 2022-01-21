import string

def pangramaPerfecto(cadena):
    c = cadena.lower()
    c = c.replace(" ","")
    for s in string.ascii_lowercase:
        if(c.count(s)!=1):
            return False
        c = c.replace(s,"")
    return not c

print(pangramaPerfecto('The quick brown fox jumps over the lazy dog'))

print(pangramaPerfecto(string.ascii_lowercase))
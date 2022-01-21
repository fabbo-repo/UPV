import collections

def char_freq(cadena):
    lista = list(cadena)
    cuenta = collections.Counter(lista)
    return cuenta

print(char_freq("abbabcbdbabdbdbabababcbcbab"))
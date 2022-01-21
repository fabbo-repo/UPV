import string

def pangrama(cadena):
    return not set(string.ascii_lowercase)-set(cadena.lower())

print(pangrama('The quick brown fox jumps over the lazy dog'))

print(pangrama('fdgdsg'))
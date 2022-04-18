"""
    Leer fichero por consola:
    python3 ejer2.py <ruta>
"""
import sys

def main():
    file = sys.argv[1]
    print("Leyendo fichero: "+file)
    print()
    with open(file, 'r+') as in_file:
        for line in in_file.readlines():
            print(line, end='')

if __name__ == "__main__":
    if(len(sys.argv) < 2): print("Faltan argumentos")
    else: main()
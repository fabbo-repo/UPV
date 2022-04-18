"""
    Codificar en base64 el fichero /etc/passwd, salida en
    fichero output.txt
    python3 ejer5-1.py
    cat /etc/passwd | base64 > output.txt
"""

import base64

with open("/etc/passwd", 'r') as in_file:
    text = in_file.read()
    
cod = base64.b64encode(text.encode())


with open("output.txt", 'w+') as out_file:
    out_file.write(cod.decode('utf-8'))
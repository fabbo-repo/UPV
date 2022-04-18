"""un fichero de entrada el fichero /etc/passwd
    python3 ejer5-2.py output.txt
"""
import base64

with open("output.txt", 'r') as in_file:
    text = in_file.read()
    text = base64.b64decode(text)
    print(text.decode('utf-8'))
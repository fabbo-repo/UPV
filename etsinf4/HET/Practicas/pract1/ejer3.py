"""
    Hacer una solicitud http de get a la upv:
    python3 ejer3.py
"""

import socket

# Web de la upv
host = 'www.upv.es'
port = 80

# Se envia peticion HTTP de tipo GET
request = str(""\
    + "GET /es/ HTTP/1.1\r\n"\
    + "Host: %s\r\n\r\n") % host

# Creación de un objeto socket (lado cliente)
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    # Conexión con la upv
    s.connect((host, port))
    s.sendall(request.encode())
    response = s.recv(512)
    while True:
        aux = s.recv(512)
        if (len(aux) < 1):
            break
        response += aux

print('Received', repr(response))

"""
    Ejecutar server que sea capaz de retornar User-Aegnt de HTTP:
    python3 ejer4.py 8080
"""
import sys
import socket

host = 'localhost'
port = int(sys.argv[1])

def obtainId(x):
    list1 = str(x).split("\\r\\n")
    res="None"
    for line in list1:
        if("User-Agent:") in line:
            res=line.replace("User-Agent: ","")
            break
    return res

def obtainURL(x):
    list1 = str(x).split("\\r\\n")
    res="None"
    for line in list1:
        if("GET") in line:
            res=line.split(" ")[1]
            break
    return res

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((host, port))
    s.listen()
    conn, addr = s.accept()
    with conn:
        print('Connected -> ', addr)
        request = conn.recv(512)
        """
        while True:
            aux = conn.recv(512)
            if (len(aux) < 1):
                break
            request += aux
        """
        print('\n'+str(request)+'\n')
        respons =  ""\
            +"HTTP/1.1 200 OK\r\n"\
            +"Connection: close\r\n"\
            +"Content-Type: text/html; charset=iso-8859-1\r\n\r\n"\
            +"<!DOCTYPE HTML PUBLIC \"-//IETF//DTD HTML 2.0//EN\">\n"\
            +"<html><head>\n"\
            +"<title>Surprise!</title>\n"\
            +"</head><body>\n"\
            +"<h1>Holaaaa!</h1>La URL es: " + obtainURL(repr(request)) +  "\n"\
            +"<br>Tu Navegador es: " + obtainId(repr(request)) +  "\n"\
            +"<p></p>\n"\
            +"</body></html>\n"
        print(respons)
        conn.sendall(respons.encode())
        conn.close()
    s.close()
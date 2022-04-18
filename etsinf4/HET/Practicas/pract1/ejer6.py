"""
    Empaqutar en bytes un numero
"""
# echo -n ")" | hd
import sys
import struct

def main():
    num = int(sys.argv[1])

    if num < 0: 
        res1 = struct.pack(">b", int(num%128)).hex()
        res2 = struct.pack(">h", int(num%32768)).hex()
        res3 = struct.pack(">i", int(num%2147483648)).hex()
    else: 
        res1 = struct.pack(">b", int(num%127)).hex()
        res2 = struct.pack(">h", int(num%32767)).hex()
        res3 = struct.pack(">i", int(num%2147483647)).hex()
    
    print("1 byte: "+res1)
    
    print("2 byte: "+res2)
    
    print("4 byte: "+res3)
    
if __name__ == "__main__":
    if(len(sys.argv) < 2): print("Faltan argumentos")
    else: main()
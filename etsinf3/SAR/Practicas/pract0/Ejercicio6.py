import collections

def procesarCorhetes(cadena):
    count = 0
    for i in cadena:
        if i=='[': count+=1
        elif i==']': count-=1
        if count<0: return False
    if count==0: return True
    return False

print(procesarCorhetes("[]"))
print(procesarCorhetes("[][]"))
print(procesarCorhetes("[[][]]"))
print(procesarCorhetes("]["))
print(procesarCorhetes("][]["))
print(procesarCorhetes("[]][[]"))
print(procesarCorhetes("[hola]"))
var1 = 1
print("var1: "+str(var1))

lista1 = list(range(10))
print("lista1: "+str(lista1))

var1 = "string"
print("var1: "+str(var1))

tupla1 = tuple(range(10,20))
print("tupla1: "+str(tupla1))

dict1 = {}
for x in lista1:
    dict1[x] = tupla1[x]
print("dict1: "+str(dict1))

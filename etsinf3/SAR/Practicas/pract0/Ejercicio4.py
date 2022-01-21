def funcion_grep(path, cadena):
    f = open(path,"r",encoding="utf-8")
    lineas = list(f.read().split("\n"))
    res = []
    for i in range(len(lineas)) : # range devuelve una lista desde 0 hasta el parámetro que se le pasa, range(3) -> [0,1,2]
        if lineas[i].find(cadena)!=-1 :
            res.append(lineas[i])
    f.close()
    return res

print(funcion_grep('D:/UPV/Tercer Año/Computacion/SAR/Practicas/pract0/prueba.txt','la'))
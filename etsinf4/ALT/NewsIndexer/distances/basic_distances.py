#############################################################################################
#    Levenstein Distance
#############################################################################################
def dp_levenshtein_backwards(x, y) :
    lengthX = len(x)
    lengthY = len(y)  # m

    # Initialize 1st column of the array to [0,1,2,...,m]
    prev = [i for i in range(lengthY+1)]
    current = [1]

    for i in range(lengthX):
        for j in range(lengthY):
            if x[i]==y[j]: current.append(min(prev[j], prev[j+1]+1, current[j]+1))
            else: current.append(min(prev[j]+1, prev[j+1]+1, current[j]+1))

        # Empty list for next iteration
        if i!=lengthX-1:
            prev = current      # list is copied by reference
            current = [i+2]     # no longer copied by reference

    return current[-1]

#############################################################################################
#    Restricted Damerau-Levenstein Distance
#############################################################################################
def dp_restricted_damerau_backwards(x, y) :
    lenx = len(x); leny = len(y) # x and y string length
    
    # current, prev1 y prev2 prev2 will efficiently store the distances 
    # of each character 
    prev1 = []; current = []
    for i in range(0, lenx+1) : 
        prev2 = prev1; prev1 = current; current = []
        for j in range(0, leny+1) :
            D=[]
            if i==0 and j == 0 : D.append(0)
            if i > 0 : D.append(prev1[j] + 1)  # Initialize first column
            if j > 0 : D.append(current[j-1] + 1)  # Initialize first row
            if i > 0 and j > 0 :
                D.append(prev1[j-1] + (x[i-1] != y[j-1]))
            if i > 1 and j > 1 and x[i-2] == y[j-1] and x[i-1] == y[j-2] :
                D.append(prev2[j-2] + 1)
            # The minimum of the distances is added to current
            current.append(min(D))
    return current[-1]

#############################################################################################
#    Intermediate Damerau-Levenstein Distance
#############################################################################################
def dp_intermediate_damerau_backwards(x, y) :
    lenx = len(x); leny = len(y)
    cte = 1 # constant preset to 1 considering cost(acb, ba)=2 and cost(ab, bca)=2

    # In this case prev3 is needed to store extra distances
    prev2 = []; prev1 = []; current = []
    for i in range(0, lenx+1) : 
        prev3 = prev2; prev2 = prev1; prev1 = current; current = []
        for j in range(0, leny+1) :
            D=[]
            if i==0 and j == 0 : D.append(0)
            if i > 0 : D.append(prev1[j] + 1)
            if j > 0 : D.append(current[j-1] + 1)
            if i > 0 and j > 0 :
                D.append(prev1[j-1] + (x[i-1] != y[j-1]))
            if i > 1 and j > 1 and x[i-2] == y[j-1] and x[i-1] == y[j-2] :
                D.append(prev2[j-2] + 1)
            # Adittional conditions:
            # Having the example of x=ab and y=bca:
            elif i > 1 and j > 1+cte and x[i-2] == y[j-1] and x[i-1] == y[j-2-cte] : 
                D.append(prev2[j-3] + 2)
            # And the opposite, x=bca and y=ab:
            elif i > 1+cte and j > 1 and x[i-2-cte] == y[j-1] and x[i-1] == y[j-2] : 
                D.append(prev3[j-2] + 2)
            # The minimum of the distances is added to current
            current.append(min(D))
    return current[-1]


#############################################################################################
#    Tests:
#############################################################################################
if __name__ == "__main__":
    test = [("algoritmo","algortimo"),
            ("algoritmo","algortximo"),
            ("algoritmo","lagortimo"),
            ("algoritmo","agaloritom"),
            ("algoritmo","algormio"),
            ("acb","ba")]

    for x,y in test:
        print(f"{x:12} {y:12}",end="")
        for dist,name in ((dp_levenshtein_backwards,"levenshtein"),
                        (dp_restricted_damerau_backwards,"restricted"),
                        (dp_intermediate_damerau_backwards,"intermediate")):
            print(f" {name} {dist(x,y):2}",end="")
        print()
                 
"""
Salida del programa:

algoritmo    algortimo    levenshtein  2 restricted  1 intermediate  1
algoritmo    algortximo   levenshtein  3 restricted  3 intermediate  2
algoritmo    lagortimo    levenshtein  4 restricted  2 intermediate  2
algoritmo    agaloritom   levenshtein  5 restricted  4 intermediate  3
algoritmo    algormio     levenshtein  3 restricted  3 intermediate  2
acb          ba           levenshtein  3 restricted  3 intermediate  2
"""         

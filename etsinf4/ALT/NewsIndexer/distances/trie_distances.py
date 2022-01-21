try : from utils.trie import Trie
except : from distances.utils.trie import Trie
#############################################################################################
#    Levenstein Trie Distance
#############################################################################################
def dp_levenshtein_trie(x, trie, th) :
    len_trie = trie.get_num_states()
    res = {}

    # current and prev are created as lists with len_trie size
    current = [None] * len_trie
    prev = [None] * len_trie 
    
    # first column is filled
    current[0] = 0
    for st in range(1,len_trie):
        current[st] = current[trie.get_parent(st)] + 1
    
    for ch in x :
        current , prev = prev, current
        current[0] = prev[0]+1
        for st in range(1,len_trie):
            father = trie.get_parent(st)
            current[st] = min(
                prev[st]+1,
                current[father]+1,
                prev[father] + (ch != trie.get_label(st)) 
            )
        if(min(current) > th) : return res
    
    for st in range(1,len_trie):
        if trie.is_final(st) and current[st] <= th:
            res[trie.get_output(st)] = current[st]
    
    return res

#############################################################################################
#    Restricted Damerau-Levenstein Trie Distance
#############################################################################################
def dp_restricted_damerau_trie(x, trie, th) :
    len_trie = trie.get_num_states()
    res = {}

    # current and prev are created as lists with len_trie size
    current = [None] * len_trie
    prev = [None] * len_trie 
    
    # first column is filled
    current[0] = 0
    for st in range(1,len_trie):
        current[st] = current[trie.get_parent(st)] + 1
    
    for ch in x :
        prev2 , prev , current = prev, current, prev
        current[0] = prev[0]+1
        for st in range(1,len_trie):
            father = trie.get_parent(st)
            current[st] = min(
                prev2[st-1]+1,
                prev[st]+1,
                current[father]+1,
                prev[father] + (ch != trie.get_label(st)) 
            )
        if(min(current) > th) : return res
    
    for st in range(1,len_trie):
        if trie.is_final(st) and current[st] <= th:
            res[trie.get_output(st)] = current[st]
    
    return res


#############################################################################################
#    Intermediate Damerau-Levenstein Trie Distance
#############################################################################################
def dp_intermediate_damerau_trie(x, trie, th) :
    return {}


#############################################################################################
#    Tests:
#############################################################################################
if __name__ == "__main__":
    words = ["algortimo", "algortximo","lagortimo", "agaloritom", "algormio", "ba"]
    words.sort()
    trie = Trie(words)

    test = ["algoritmo", "acb"]
    thrs = range(1, 4)

    for threshold in thrs:
        print(f"threshols: {threshold:3}")
        for x in test:
            for dist,name in (
                        (dp_levenshtein_trie,"levenshtein"),
                        (dp_restricted_damerau_trie,"restricted"),
                        (dp_intermediate_damerau_trie,"intermediate"),
                        ):
                print(f"\t{x:12} \t{name}\t", end="")
                print(dist(x, trie, threshold))
                 
"""
Salida del programa:

threshols:   1
	algoritmo    	levenshtein	[]
	algoritmo    	restricted	[('algortimo', 1)]
	algoritmo    	intermediate	[('algortimo', 1)]
	acb          	levenshtein	[]
	acb          	restricted	[]
	acb          	intermediate	[]
threshols:   2
	algoritmo    	levenshtein	[('algortimo', 2)]
	algoritmo    	restricted	[('algortimo', 1), ('lagortimo', 2)]
	algoritmo    	intermediate	[('algormio', 2), ('algortimo', 1), ('lagortimo', 2), ('algortximo', 2)]
	acb          	levenshtein	[]
	acb          	restricted	[]
	acb          	intermediate	[('ba', 2)]
threshols:   3
	algoritmo    	levenshtein	[('algormio', 3), ('algortimo', 2), ('algortximo', 3)]
	algoritmo    	restricted	[('algormio', 3), ('algortimo', 1), ('lagortimo', 2), ('algortximo', 3)]
	algoritmo    	intermediate	[('algormio', 2), ('algortimo', 1), ('lagortimo', 2), ('agaloritom', 3), ('algortximo', 2)]
	acb          	levenshtein	[('ba', 3)]
	acb          	restricted	[('ba', 3)]
	acb          	intermediate	[('ba', 2)]

"""         

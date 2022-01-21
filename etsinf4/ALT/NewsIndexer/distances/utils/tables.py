import numpy as np
import csv

def create_csv(s, thresholds, t_lev, t_res, t_int, t_trie) :
    # sizes = ['100', '500', '1000', '1500', '2000']
    time_leven = []; time_int = []
    time_rest = []; time_trie = []
        
    for thres in thresholds :
        time_leven.append(t_lev[s][thres])
        time_rest.append(t_res[s][thres])
        time_int.append(t_int[s][thres])
        time_trie.append(t_trie[s][thres])
    
    with open('data/table'+str(s)+'.csv', 'w', newline='') as csvfile:
        writer = csv.writer(csvfile, delimiter=';',
                                quotechar='|', quoting=csv.QUOTE_MINIMAL)
        writer.writerow(['Thresholds'] + thresholds)
        writer.writerow(['levenshtein'] + time_leven)
        writer.writerow(['intermediate'] + time_int)
        writer.writerow(['restricted'] + time_rest)
        writer.writerow(['trielevenshtein'] + time_trie)


if __name__=='__main__' :
    create_csv('100', ['1','2'], 
        {'100':{'1':0.2,'2':0.3},'150':{'1':0.2,'2':0.3}}, 
        {'100':{'1':0.2,'2':0.3},'150':{'1':0.2,'2':0.3}}, 
        {'100':{'1':0.2,'2':0.3},'150':{'1':0.2,'2':0.3}}, 
        {'100':{'1':0.2,'2':0.3},'150':{'1':0.2,'2':0.3}})

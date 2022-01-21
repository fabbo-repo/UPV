import numpy as np
import matplotlib.pyplot as plt

def show_bar_graphing(s, thresholds, t_lev, t_res, t_int, t_trie) :
    # sizes = ['100', '500', '1000', '1500', '2000']
    time_leven = []; time_int = []
    time_rest = []; time_trie = []

    # Obtenemos la posicion de cada etiqueta en el eje de X
    x = np.arange(len(thresholds))
    # tamaño de cada barra
    width = 0.1
    fig, ax = plt.subplots()
        
    for thres in thresholds :
        time_leven.append(t_lev[s][thres])
        time_rest.append(t_res[s][thres])
        time_int.append(t_int[s][thres])
        time_trie.append(t_trie[s][thres])
    
    rects_lev = ax.bar(x - 3*width/2, time_leven, width, label='levenshtein')
    rects_res = ax.bar(x - width/2, time_rest, width, label='restricted')
    rects_int = ax.bar(x + width/2, time_int, width, label='intermediate')
    rects_trie = ax.bar(x + 3*width/2, time_trie, width, label='trielevenshtein')

    # Añadimos las etiquetas de identificacion de valores en el grafico
    ax.set_ylabel('Time (s)')
    ax.set_title('Size '+str(s))
    ax.set_xticks(x)
    ax.set_xticklabels(thresholds)
    
    # Añadimos un legen() esto permite mmostrar con colores a que pertence cada valor.
    ax.legend()

    def autolabel(rects):
        """Funcion para agregar una etiqueta con el valor en cada barra"""
        for rect in rects:
            height = rect.get_height()
            ax.annotate('{}'.format(height),
                        xy=(rect.get_x() + rect.get_width() / 2, height),
                        xytext=(0, 3),  # 3 points vertical offset
                        textcoords="offset points",
                        ha='center', va='bottom')

    # Añadimos las etiquetas para cada barra
    autolabel(rects_lev)
    autolabel(rects_res)
    autolabel(rects_int)
    autolabel(rects_trie)
    fig.tight_layout()
    
    plt.savefig('data/plot'+str(s)+'.png')
    # Mostramos la grafica con el metodo show()
    # plt.show()
    

"""
if __name__=='__main__' :
    show_bar_graphing('100', ['1','2'], 
        {'100':{'1':0.2,'2':0.3},'150':{'1':0.2,'2':0.3}}, 
        {'100':{'1':0.2,'2':0.3},'150':{'1':0.2,'2':0.3}}, 
        {'100':{'1':0.2,'2':0.3},'150':{'1':0.2,'2':0.3}}, 
        {'100':{'1':0.2,'2':0.3},'150':{'1':0.2,'2':0.3}})
"""
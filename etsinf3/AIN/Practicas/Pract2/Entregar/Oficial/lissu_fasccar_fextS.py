import json
from math import sqrt
import random
import agentspeak
from loguru import logger
from spade.behaviour import OneShotBehaviour
from spade.template import Template
from spade.message import Message
from pygomas.bditroop import BDITroop
from pygomas.bdifieldop import BDIFieldOp
from pygomas.bdisoldier import BDISoldier
from agentspeak import Actions
from agentspeak import grounded
from agentspeak.stdlib import actions as asp_action
from pygomas.ontology import DESTINATION

from pygomas.agent import LONG_RECEIVE_WAIT

class LissuFasccarSoldier(BDISoldier):

    def add_custom_actions(self, actions):
        super().add_custom_actions(actions)
        
        @actions.add_function(".randomPos", (int, ))
        def _randomPos(max):
            return random.randint(0,max) # Se incluye max

        @actions.add_function(".mejorPos", (tuple, tuple, tuple, ))
        def _mejorPos(p1, p2, bandera):
            p1X = p1[0]; p1Z = p1[2]
            p2X = p2[0]; p2Z = p2[2]
            banderaX = bandera[0]; banderaZ = bandera[2]
            dist1 = sqrt(pow(banderaX-p1X,2) + pow(banderaZ-p1Z,2))
            dist2 = sqrt(pow(banderaX-p2X,2) + pow(banderaZ-p2Z,2))
            if(dist1 < dist2): return 1
            else: return 2
        
        @actions.add_function(".giveRing", (tuple, tuple, ))
        def _giveRing(name, lider):
            myName = str(name[0]).split('@')[0] 
            lName = str(lider[0]).split('@')[0]
            myNumber = int(myName[len(myName)-1])
            lNumber = int(lName[len(lName)-1])
            ring = 1; cont = 0
            for i in range(6): # 6 soldiers excluyendo al coronel
                if i!=lNumber: cont += 1
                if cont == 1: ring = 1
                elif cont == 2 or cont == 3: ring = 2
                else: ring = 3
                if i == myNumber: break
            return ring
        
        @actions.add_function(".givePositionSoldier", (int, tuple, ))
        def _givePositionSoldier(anillo, pBandera):
            cX = pBandera[0]; cZ = pBandera[2]; dist = anillo*15
            pX = []; aux1 = []; aux2 = []
            pX.append(cX-dist)
            pX.append(cX-(2*dist/3)); pX.append(cX-(dist/3))
            pX.append(cX)
            pX.append(cX+(dist/3)); pX.append(cX+(2*dist/3))
            pX.append(cX+dist)
            for px in pX:
                pZ1 = cZ + sqrt(pow(dist,2) - pow(cX - px,2))
                pZ2 = cZ - sqrt(pow(dist,2) - pow(cX - px,2))
                if anillo == 2: # A favor de las manecillas del reloj
                    if(self.map.can_walk(int(px), int(pZ1))): 
                        aux1.append((px,0,pZ1))
                    if(self.map.can_walk(int(px), int(pZ2))): 
                        aux2 = [(px,0,pZ2)] + aux2
                else: # Contra las manecillas del reloj
                    if(self.map.can_walk(int(px), int(pZ1))): 
                        aux1 = [(px,0,pZ1)] + aux1
                    if(self.map.can_walk(int(px), int(pZ2))): 
                        aux2.append((px,0,pZ2))
            if anillo == 2: res = aux1+aux2
            else: res = aux2+aux1
            return tuple(res)
            
# .givePosition(1, Lista, ListaSalida)
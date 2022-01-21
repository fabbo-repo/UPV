- Si tengo poca vida (health(X)):
     evitar ejes (.turn(angle+90º en radianes)) y me dirijo a por kits de sanación (packs_in_fov(...1001...))
     si no hay healing, seguir evitando ejes cerca del centro, donde se crean los healings
     nueva creencia: need_healing ------ entonces evito ejes hasta que consiga healing -> pack_taken(medic, N) -> health(X+N)

- Eje con vida baja (friends_in_fov(...Health, xyz)), 
     si no tenemos otros ejes cerca, nos centramos en este, nos giramos (.look_at(xyz)) y disparamos mientras nos dirigimos hacia su posición (.goto(xyz))
     si hay más, escogemos el de menor distancia (calculamos las distancias con cada eje cercano, a partir de sus posiciones, que estarán guardadas, una a una, en nuestra nueva creencia)

- Normalmente, me muevo aleatoriamente creando puntos de control en cada paso que doy

- Nueva creencia: need_ammo ------ entonces evito ejes hasta que consiga munición -> pack_taken(fieldops, N) -> ammo(X+N)

- EXTRA: Si ya no hay ejes activos, bailar
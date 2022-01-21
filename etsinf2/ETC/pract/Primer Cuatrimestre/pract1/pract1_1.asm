.globl __start
.text 0x00400000
__start:
li $t0,75369  #Antes era 25
li $t1,12976  #Antes era 30
add $s0,$t1,$t0
add $s0,$s0,$s0
.end

# 1- Tiene 4 instrucciones
# 2- En instrucciones ori
# 3- En la 0x0040000c
# 4- La add $s0,$t1,$t0
# 5- 0x0000006e
# 6- Ya esta modificado y se traduce en 2 instrucciones la primera: lui y ori y la segunda en una: ori

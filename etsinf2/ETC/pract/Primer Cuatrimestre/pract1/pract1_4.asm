1- and $t0, $t1, $zero
2- addi $t0, $zero, 100
   ori $t0, $zero, 100
   xori $t0, $zero, 100
3- Porque la primera instruccion deberia ser: la $t0, 0x10003000
4- lui se carga en la parte alta de 16 a 32
   lw carga una palabra
5- 1- la $t0,N  /  sw $zero,0($t0)
   2- la $t0,N  /  li $s2, -1 / sw $s2,0($t0)
   3- la $t0,N  /  li $s2, 1048576 / sw $s2,0($t0)
   4- la $t0,N  /  li $s2, 1048640 / sw $s2,0($t0)
   5- la $t0,N  /  li $s2, 200000 / sw $s2,0($t0)
6- Como: lui $1, -1 / ori $8, $1, -1
7- +0x00000000
   +0x00000000
   +0x00000000
   +0x00010000
   +0xffffffff
   +0x00000000
   +(4 espacios)
   +0x00000032
   +0x00000050
   +0xffffffff
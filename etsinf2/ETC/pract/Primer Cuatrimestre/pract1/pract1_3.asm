.globl __start
.data 0x10000000
A: .word 25
B: .word 30
P: .space 4
 .text 0x00400000
__start: 
la $t0,A
la $t1,B
la $t2,P
lw $s0,0($t0)
lw $s1,0($t1)
add $s2,$s1,$s0
add $s2,$s2,$s2
sw $s2,2($t2)    #antes: sw $s2,0($t2)
move $a0,$s2 # copia el perímetro en $a0
li $v0,1 # código de print_int
syscall # llamada al sistema
.end

# 1- 0x0000000c
# 2- addu $4, $0, $18
# 3- Salta una excepción porque se trata de acceder a una memoria que no contiene una word (0x1000000a)
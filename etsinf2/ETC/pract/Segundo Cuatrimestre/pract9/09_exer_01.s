          .globl __start
          .data 0x10000000
M:        .space 4
Q:        .space 4
R:        .space 4
          
          .text 0x00400000
__start:  li $a0,'M'
          la $a1, M
          jal InputV
		  li $a0,'Q'
          la $a1, Q
          jal InputV
		  la $a0, M
		  la $a1, Q
		  la $a2, R
		  jal MultV
		  li $a0,'R'
          la $a1, R
          jal PromptV
		  li $v0,10
          syscall

InputV:   li $v0, 11
          syscall
          li $v0, 11
          li $a0, '='
          syscall
          li $v0, 5
          syscall
          sw $v0, 0($a1)  #Guarda en M el entero que lee por pantalla
          jr $ra

MultV:    lw $t0,0($a0)
          lw $t1,0($a1)
          bgez $t1,Salta
		  sub $t0,$zero,$t0
		  sub $t1,$zero,$t1
Salta:    li $t2, 0
Iterar:   add $t2,$t2,$t0
		  addi $t1, $t1, -1
          bne $t1, $zero, Iterar
		  sw $t2,0($a2)
		  jr $ra
PromptV:  li $v0,11
          syscall       #Imprime lo que se encuentra $a0		  
		  li $a0, '='
		  li $v0,11
          syscall       #Imprime =		
		  lw $a0,0($a1) 
		  li $v0,1
          syscall       #Imprime =				  
		  jr $ra

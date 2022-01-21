         .globl __start
		 .data 0x10000000
		  M: .word 0
          Q: .word 0
          R: .word 0
          .text 0x00400000

		  __start:  
		  jal Input
		  jal Prompt
		  move $a0,$v0
          li $v0,1
          syscall        #Imprime el entero que se halle en el registro $a0
          li $v0,10
          syscall        #Ejecuta el exit
Mult:     lh $a0,M
          lh $a1,Q
          li $v0, 0
          beqz $a1, MultRet
MultFor:  add $v0, $v0, $a0
          addi $a1, $a1, -1
          bne $a1, $zero, MultFor
MultRet:  jr $ra
Input:    li $a0, 'M'
		  li $v0,11
          syscall       #Imprime M        
		  li $a0, '='
		  li $v0,11
          syscall       #Imprime =        
		  li $v0,5
          syscall       #Solicita que escribas un entero y lo guarda en el registro $v0
          sw $v0,M
          li $a0, 'Q'
		  li $v0,11
          syscall       #Imprime Q		  
		  li $a0, '='
		  li $v0,11
          syscall       #Imprime =        
		  li $v0,5
          syscall       #Solicita que escribas un entero y lo guarda en el registro $v0
          sw $v0,Q
		  jr $ra
Prompt:   li $a0, 'R'
		  li $v0,11
          syscall       #Imprime R		  
		  li $a0, '='
		  li $v0,11
          syscall       #Imprime =		  
		  j Mult
          
          

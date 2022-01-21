          .globl __start
          .data 0x10000000
demana1:  .asciiz "Escriba alguna cosa: "  #parámetro t1
demana2:  .asciiz "Ha escrito: "		   #parámetro t2
cadena:   .space 80                        #parámetro cadena

          .text 0x00400000
__start:  la $a0, demana1        
          la $a1, cadena        
          li $a2, 80            
          jal InputS            
          la $a0, demana2        
          la $a1, cadena        
          jal PromptS    
          #----------------- Aqui se comprueba si funciona StrLength        
          la $a0, cadena  
          jal StrLength
          move $a0,$v0 
          li $v0,1
          syscall
          #----------------- Se imprime al final el tamaño de la cadena
          li $v0,10
          syscall

InputS:   li $v0, 4  
          syscall      #Se imprime demana1
          li $v0, 8
          move $a0, $a1  #Se lee cadena
          move $a1, $a2  #Se lee 80, (la llamada8 hará que ã1=81, siendo ese 1 el retorno de carro, sirve para, por ejemplo, se escriba en la siguiente línea)
          syscall
          jr $ra
		  
PromptS:  li $v0, 4    # Se imprime demana2
          syscall
          move $a0, $a1
          li $v0, 4    # Se imprime cadena
          syscall
          jr $ra

#ejercicio3. Comprobar cómo funciona al añadir esto:
StrLength:move $t0,$a0
		  li $v0,0
StrLdo:   lbu $t1, 0($t0)
          beqz $t1,StrLEnd
		  addiu $t0,$t0,1
		  addi $v0,$v0,1
          li $t2,10  #Byte de retorno en decimal es 10 y en hexadecimal es 0x0a
          beq $t1,$t2,SubRC
		  j StrLdo
SubRC:    addi $v0,$v0,-1 #Se resta el byte de retorno de carro agregado por el syscall read_string
StrLEnd:  jr $ra   

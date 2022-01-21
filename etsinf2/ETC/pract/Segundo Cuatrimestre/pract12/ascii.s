#------- Segmento de datos ---------#
	.data		
T1:	.asciiz "Esperando...\n"
T2:	.asciiz "\nFin\n"

#------- Segmento de c�digo ---------#
	.text
    	.globl __start	

__start:
	# Escribe en consola mensaje T1
	li $v0, 4
	la $a0, T1
	syscall	
	
	# Carga dir base teclado
	la $t0, 0xffff0000

espera: # Espera bit R == 1
	lw $t1,0($t0)
	andi $t1,$t1,1
	beqz $t1,espera

### A COMPLETAR: lee el registro de datos del teclado
####	
    li $v0, 1
	lw $a0, 4($t0)
    syscall
    li $t2, 10  #10 corresponde en acsii al simbolo LF que es el salto de linea
    bne $a0,$t2,espera

	# Escribe en consola mensaje T2
	li $v0, 4
	la $a0, T2
	syscall

	# exit
	li $v0, 10
	syscall			

	.end
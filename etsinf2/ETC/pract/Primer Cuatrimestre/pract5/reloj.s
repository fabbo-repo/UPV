                ##########################################################
                # Segmento de datos
                ##########################################################

                .data 0x10000000
reloj:          .word 0                # HH:MM:SS (3 bytes de menor peso)

cad_asteriscos: .asciiz "\n  **************************************"
cad_horas:      .asciiz "\n   Horas: "
cad_minutos:    .asciiz " Minutos: "
cad_segundos:   .asciiz " Segundos: "
cad_reloj_en_s: .asciiz "\n   Reloj en segundos: "

                ##########################################################
                # Segmento de c�digo
                ##########################################################

                .globl __start
                .text 0x00400000

__start:        la $a0, reloj
                li $a1, 66765
                jal inicializa_reloj_en_s
                la $a0, reloj
                jal imprime_reloj
		#li $a1, 0x02
		#li $a2, 0x03
		#li $a3, 0x0C
		#jal inicializa_reloj_alt
		#jal inicializa_reloj_hh
		#jal inicializa_reloj_mm
		#jal inicializa_reloj_ss
		#la $a0, reloj
		#jal imprime_reloj
             
salir:          li $v0, 10              # C�digo de exit (10)
                syscall                 # �ltima instrucci�n ejecutada
                .end


                ########################################################## 
                # Subrutina que imprime el valor del reloj
                # Entrada: $a0 con la direcci�n de la variable reloj
                ########################################################## 

imprime_reloj:  move $t0, $a0
                la $a0, cad_asteriscos  # Direcci�n de la cadena
                li $v0, 4               # C�digo de print_string
                syscall

                la $a0, cad_horas       # Direcci�n de la cadena
                li $v0, 4               # C�digo de print_string
                syscall

                lbu $a0, 2($t0)         # Lee el campo HH
                li $v0, 1               # C�digo de print_int
                syscall

                la $a0, cad_minutos     # Direcci�n de la cadena
                li $v0, 4               # C�digo de print_string
                syscall

                lbu $a0, 1($t0)         # Lee el campo MM
                li $v0, 1               # C�digo de print_int
                syscall

                la $a0, cad_segundos    # Direcci�n de la cadena
                li $v0, 4               # C�digo de print_string
                syscall

                lbu $a0, 0($t0)         # Lee el campo SS
                li $v0, 1               # C�digo de print_int
                syscall

                la $a0, cad_asteriscos  # Direcci�n de la cadena
                li $v0, 4               # C�digo de print_string
                syscall
                jr $ra

                ########################################################## 
                # Subrutina que imprime los segundos calculados
                # Entrada: $a0 con los segundos a imprimir
                ########################################################## 

imprime_s:      move $t0, $a0
                la $a0, cad_asteriscos  # Direcci�n de la cadena
                li $v0, 4               # C�digo de print_string
                syscall


                la $a0, cad_reloj_en_s  # Direcci�n de la cadena
                li $v0, 4               # C�digo de print_string
                syscall

                move $a0, $t0           # Valor entero a imprimir
                li $v0, 1               # C�digo de print_int
                syscall

                la $a0, cad_asteriscos  # Direcci�n de la cadena
                li $v0, 4               # C�digo de print_string
                syscall
                jr $ra
                
                ########################################################## 
                # Subrutina que incrementa el reloj en una hora
                # Entrada: $a0 con la direcci�n del reloj
                # Salida: reloj incrementado en memoria
                # Nota: 23:MM:SS -> 00:MM:SS
                ########################################################## 
                
pasa_hora:      lbu $t0, 2($a0)         # $t0 = HH
                addiu $t0, $t0, 1       # $t0 = HH++
                li $t1, 24
                beq $t0, $t1, H24       # Si HH==24 se pone HH a cero
                sb $t0, 2($a0)          # Escribe HH++
                j fin_pasa_hora
H24:            sb $zero, 2($a0)        # Escribe HH a 0
fin_pasa_hora:  jr $ra

                #############################################################

inicializa_reloj: 
                sw $a1,0($a0)
                jr $ra

inicializa_reloj_alt:
		sb $a1,2($a0)
		sb $a2,1($a0)
		sb $a3,0($a0)
                jr $ra

inicializa_reloj_hh: 
                sb $a1,2($a0)
                jr $ra
inicializa_reloj_mm:
                sb $a2,1($a0)
		jr $ra
inicializa_reloj_ss:
                sb $a3,0($a0)
                jr $ra

inicializa_reloj2: 
                ori $t1, $a1, 0x0000 #Tambien el move es una opcion
                li $t0, 0x00183B3B
                bgt $t1, $t0, salir
                li $t0, 0x00003B3B
                andi $t1, $t1, 0xFFFF
                bgt $t1, $t0, salir
                li $t0, 0x0000003B
                andi $t1, $t1, 0x00FF
                bgt $t1, $t0, salir
                sw $a1,0($a0)
                jr $ra
        
devuelve_reloj_en_s:
                li $t0, 3600
                li $t1, 60
                lbu $t2, 2($a0)
                mult $t0, $t2
                mflo $t0        #$t0 contiene las horas en segundos
                lbu $t2, 1($a0)
                mult $t1, $t2
                mflo $t1        #$t1 contiene los minutos en segundos
                lbu $t2, 0($a0) #$t0 contiene los segundos
                addu $v0, $t0, $t1
                addu $v0, $v0, $t2
                jr $ra

inicializa_reloj_en_s: 
                li $t0, 60
                #beq $zero, $t0, salir
                div $a1, $t0
                mfhi $t1  #En $t1 se guarda el resto y este resto son los segundos
                mflo $t2
                div $t2, $t0
                mfhi $t2  #En $t2 se guarda el resto y este resto son los minutos
                mflo $t0  #En $t0 se guarda el valor de div que son las horas
                sb $t1, 0($a0)
                sb $t2, 1($a0)
                sb $t0, 2($a0)
                jr $ra

devuelve_reloj_en_s_srd: 
                lbu $t0, 2($a0)
                sll $v0, $t0, 12
                sll $t1, $t0, 9
                subu $v0, $v0, $t1
                sll $t1, $t0, 5
                addu $v0, $v0, $t1
                sll $t1, $t0, 4
                subu $v0, $v0, $t1

                lbu $t0, 1($a0)
                sll $t1, $t0, 6
                addu $v0, $v0, $t1 
                sll $t1, $t0, 2
                subu $v0, $v0, $t1 
                                         
                lbu $t0, 0($a0)
                addu $v0, $v0, $t0
                jra $ra

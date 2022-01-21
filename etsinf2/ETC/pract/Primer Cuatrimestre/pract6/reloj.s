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
                li $a1, 0x00150F2D
                jal inicializa_reloj
                la $a0, reloj
                jal imprime_reloj
                la $a0, reloj
                
                li $t6, 40
        do1:    jal pasa_segundos
                addi $t6, $t6, -1
        while1: bne $zero, $t6, do1
                li $t6, 3
        do2:    jal pasa_hora
                addi $t6, $t6, -1
        while2: bne $zero, $t6, do2
        
                la $a0, reloj
                jal imprime_reloj
                
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

devuelve_reloj_en_s_sd:
                lbu $t0, 2($a0)
                sll $v0, $t0, 11
                sll $t1, $t0, 10
                addu $v0, $v0, $t1
                sll $t1, $t0, 9
                addu $v0, $v0, $t1
                sll $t1, $t0, 4
                addu $v0, $v0, $t1
                #$v0 contiene el valor de las horas en segundos
                lbu $t0, 1($a0)
                sll $t1, $t0, 5
                addu $v0, $v0, $t1
                sll $t1, $t0, 4
                addu $v0, $v0, $t1
                sll $t1, $t0, 3
                addu $v0, $v0, $t1 
                sll $t1, $t0, 2
                addu $v0, $v0, $t1 
                #$v0 contiene el valor de las horas y los minutos en segundos
                lbu $t0, 0($a0)
                addu $v0, $v0, $t0
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
                jr $ra

pasa_segundos: 
                lbu $t0, 0($a0) # $t0 = SS
                addiu $t0, $t0, 1 # $t0 = SS++ 
                li $t1, 60
                beq $t0, $t1, S60 # Si SS==60 se pone SS a cero y añade 1 minuto
                sb $t0, 0($a0) # Escribe SS++
                j fin_pasa_segundos
        S60:    sb $zero, 0($a0) # Escribe SS a 0
                j pasa_minutos
        fin_pasa_segundos:  
                jr $ra
                
pasa_minutos:  
                lbu $t0, 1($a0) # $t0 = MM
                addiu $t0, $t0, 1 # $t0 = MM++ 
                beq $t0, $t1, M60 # Si MM==60 se pone MM a cero y añade 1 hora
                sb $t0, 1($a0) # Escribe SS++
                j fin_pasa_minutos
        M60:    sb $zero, 1($a0) # Escribe SS a 0
                j pasa_hora
        fin_pasa_minutos:  
                jr $ra
                
          .globl __start
          .data 0x10000000
demana1:  .asciiz "Escriba alguna cosa: "  #parámetro t1
demana2:  .asciiz "Ha escrito: "		   #parámetro t2
cadena:   .space 80                        #parámetro cadena

          .text 0x00400000
__start:    lw $t0, 0x101000
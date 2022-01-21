	.data
a: 	.dword 9, 8, 0, 1, 0, 5, 3, 1, 2, 0
tam:  .dword 10
cont0:  .dword 0
	.text
start:
	dadd r1,r0,tam
	ld r1,0(r1) 			
	dadd r6,r0,cont0		; r6 contiene la direccion de cont0 
	dsll r1, r1, #3 		; r1 contiene el tamano del vector
	ld r2,0(r6)				; r2 contiene el valor de cont0 
	dadd r3,r0,a			; r3 contiene la direccion de a 
	
loop:
	ld r10,0(r3)			; r10 contiene un elemento de a 
	dadd r3,r3,#8
	seq r5,r1,r3
	seq r4,r10,r0			; r4 sera 1 si r10 = 0 
	dadd r2,r2,r4
	beqz r5,loop
	
	sd r2,0(r6)
	trap #0         ; Fin de programa

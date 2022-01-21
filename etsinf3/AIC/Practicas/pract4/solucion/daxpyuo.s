        ; z = a*x + y
        ; Tama�o de los vectores: 64 palabras
        ; Vector x
	.data
x:      .double 0,1,2,3,4,5,6,7,8,9
        .double 10,11,12,13,14,15,16,17,18,19
        .double 20,21,22,23,24,25,26,27,28,29
        .double 30,31,32,33,34,35,36,37,38,39
        .double 40,41,42,43,44,45,46,47,48,49
        .double 50,51,52,53,54,55,56,57,58,59

	; Vector y
y:      .double 100,100,100,100,100,100,100,100,100,100
	.double 100,100,100,100,100,100,100,100,100,100
	.double 100,100,100,100,100,100,100,100,100,100
	.double 100,100,100,100,100,100,100,100,100,100
	.double 100,100,100,100,100,100,100,100,100,100
	.double 100,100,100,100,100,100,100,100,100,100

        ; Vector z
	; 60 elementos son 480 bytes
z:      .space 480

        ; Escalar a
a:      .double 1

        ; El c�digo
	.text

start:

        dadd r1,r0,x     ; r1 contiene la direccion de x
        dadd r2,r0,y     ; r1 contiene la direccion de y
        dadd r3,r0,z     ; r2 contiene la direccion de z
        l.d f0,a(r0)     ; f0 contiene a
        dadd r4,r1,#480  ; 60 elementos son 480 bytes, 6B cada uno
loop:
        l.d f2,0(r1)
        l.d f4,0(r2)
        l.d f8,8(r1)
        l.d f10,8(r2)
        l.d f14,16(r1)
        l.d f16,16(r2)
        l.d f20,24(r1)
        l.d f22,24(r2)
        mul.d f6,f0,f2
        mul.d f12,f0,f8
        mul.d f18,f0,f14
        mul.d f24,f0,f20
        add.d f4,f6,f4
        add.d f10,f12,f10
        add.d f16,f18,f16
        add.d f22,f24,f22
        s.d f4, 0(r3)
        s.d f10, 8(r3)
        s.d f16, 16(r3)
        s.d f22, 24(r3)
        dadd r1,r1,#32
        dadd r2,r2,#32
        dsub r5,r4,r1
        dadd r3,r3,#32
        bnez r5,loop

        trap #0         ; Fin de programa


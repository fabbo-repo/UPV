	.text

start:
	ori $8, $0, 10
    lw  $4, 0x100($2)
	lw    $7, 0($4)
	sll   $7, $7, 2
	addi  $8,  $8, -1
	sw    $7,0($4)
	bgtz  $8, do
	li    $v0, 0
	trap #0



        



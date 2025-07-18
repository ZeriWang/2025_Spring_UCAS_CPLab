	.file   "05.cact"
	.option nopic
	.attribute arch, "rv64i2p0_m2p0_a2p0_f2p0_d2p0_c2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	
	.globl   a
	.section .srodata, "a"
	.align   2
	.type    a, @object
	.size    a, 4
a:
	.word    10
	
	.globl   b
	.section .srodata, "a"
	.align   2
	.type    b, @object
	.size    b, 4
b:
	.word    5
	
	.text
	.align   1
	.globl   main
	.type    main, @function
main:
#frame size: 16
	addi  sp, sp, -16
	sd    ra, 8(sp)
	sd    s0, 0(sp)
	addi  s0, sp, 16
	lui   t5, %hi(b)
	lw    a0, %lo(b)(t5)
	j     func_end0
func_end0:
	ld    ra, 8(sp)
	ld    s0, 0(sp)
	addi  sp, sp, 16
	jr    ra
	.size    main,  .-main

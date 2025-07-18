	.file   "01.cact"
	.option nopic
	.attribute arch, "rv64i2p0_m2p0_a2p0_f2p0_d2p0_c2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	
	.globl   a
	.section .sdata, "aw"
	.align   2
	.type    a, @object
	.size    a, 4
a:
	.word    2
	
	.globl   b
	.section .sdata, "aw"
	.align   2
	.type    b, @object
	.size    b, 4
b:
	.word    3
	
	.text
	.align   1
	.globl   main
	.type    main, @function
main:
#frame size: 32
	addi  sp, sp, -32
	sd    ra, 24(sp)
	sd    s0, 16(sp)
	addi  s0, sp, 32
	li    t2, 4
	sw    t2, -20(s0)
	lw    t0, -20(s0)
	lui   t5, %hi(b)
	lw    t1, %lo(b)(t5)
	addw  t2, t0, t1
	sw    t2, -24(s0)
	lw    a0, -24(s0)
	j     func_end0
func_end0:
	ld    ra, 24(sp)
	ld    s0, 16(sp)
	addi  sp, sp, 32
	jr    ra
	.size    main,  .-main

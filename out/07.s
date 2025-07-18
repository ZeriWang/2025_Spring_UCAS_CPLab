	.file   "07.cact"
	.option nopic
	.attribute arch, "rv64i2p0_m2p0_a2p0_f2p0_d2p0_c2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	
	.globl   a
	.section .srodata, "a"
	.align   3
	.type    a, @object
	.size    a, 20
a:
	.word    0
	.word    1
	.word    2
	.word    3
	.word    4
	
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
	lw    t1, -20(s0)
	mv    t5,t1
	slliw t5, t5, 2
	lui   s2, %hi(a)
	addi  s2, s2, %lo(a)
	add   s3, s2, t5
	lw    t2, 0(s3)
	sw    t2, -24(s0)
	lw    a0, -24(s0)
	j     func_end0
func_end0:
	ld    ra, 24(sp)
	ld    s0, 16(sp)
	addi  sp, sp, 32
	jr    ra
	.size    main,  .-main

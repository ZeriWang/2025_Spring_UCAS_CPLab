	.file   "22.cact"
	.option nopic
	.attribute arch, "rv64i2p0_m2p0_a2p0_f2p0_d2p0_c2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	
	.globl   arr
	.data
	.align   3
	.type    arr, @object
	.size    arr, 24
arr:
	.word    1
	.word    2
	.word    33
	.word    4
	.word    5
	.word    6
	
	.text
	.align   1
	.globl   main
	.type    main, @function
main:
#frame size: 48
	addi  sp, sp, -48
	sd    ra, 40(sp)
	sd    s0, 32(sp)
	addi  s0, sp, 48
	li    t2, 0
	sw    t2, -20(s0)
	li    t2, 0
	sw    t2, -24(s0)
label1:
	li    t2, 6
	sw    t2, -28(s0)
	lw    t0, -20(s0)
	lw    t1, -28(s0)
	slt   t2, t0, t1
	sw    t2, -32(s0)
	lw    t2, -32(s0)
	beqz  t2, label2
	lw    t1, -20(s0)
	mv    t5,t1
	slliw t5, t5, 2
	lui   s2, %hi(arr)
	addi  s2, s2, %lo(arr)
	add   s3, s2, t5
	lw    t2, 0(s3)
	sw    t2, -36(s0)
	lw    t0, -24(s0)
	lw    t1, -36(s0)
	addw  t2, t0, t1
	sw    t2, -40(s0)
	lw    t2, -40(s0)
	sw    t2, -24(s0)
	li    t2, 1
	sw    t2, -44(s0)
	lw    t0, -20(s0)
	lw    t1, -44(s0)
	addw  t2, t0, t1
	sw    t2, -48(s0)
	lw    t2, -48(s0)
	sw    t2, -20(s0)
	j     label1
label2:
	lw    a0, -24(s0)
	j     func_end0
func_end0:
	ld    ra, 40(sp)
	ld    s0, 32(sp)
	addi  sp, sp, 48
	jr    ra
	.size    main,  .-main

	.file   "20.cact"
	.option nopic
	.attribute arch, "rv64i2p0_m2p0_a2p0_f2p0_d2p0_c2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	
	.text
	.align   1
	.globl   main
	.type    main, @function
main:
#frame size: 80
	addi  sp, sp, -80
	sd    ra, 72(sp)
	sd    s0, 64(sp)
	addi  s0, sp, 80
	li    t2, 0
	sw    t2, -24(s0)
	lw    t2, -24(s0)
	sw    t2, -20(s0)
	li    t2, 0
	sw    t2, -32(s0)
	lw    t2, -32(s0)
	sw    t2, -28(s0)
label1:
	li    t2, 100
	sw    t2, -36(s0)
	lw    t0, -20(s0)
	lw    t1, -36(s0)
	slt   t2, t0, t1
	sw    t2, -40(s0)
	lw    t2, -40(s0)
	beqz  t2, label2
	li    t2, 50
	sw    t2, -44(s0)
	lw    t0, -20(s0)
	lw    t1, -44(s0)
	subw  t2, t0, t1
	sltu  t2, zero, t2
	not   t2, t2
	andi  t2, t2, 1
	sw    t2, -48(s0)
	lw    t2, -48(s0)
	beqz  t2, label3
	li    t2, 1
	sw    t2, -52(s0)
	lw    t0, -20(s0)
	lw    t1, -52(s0)
	addw  t2, t0, t1
	sw    t2, -56(s0)
	lw    t2, -56(s0)
	sw    t2, -20(s0)
	j     label1
label3:
	lw    t0, -28(s0)
	lw    t1, -20(s0)
	addw  t2, t0, t1
	sw    t2, -60(s0)
	lw    t2, -60(s0)
	sw    t2, -28(s0)
	li    t2, 1
	sw    t2, -64(s0)
	lw    t0, -20(s0)
	lw    t1, -64(s0)
	addw  t2, t0, t1
	sw    t2, -68(s0)
	lw    t2, -68(s0)
	sw    t2, -20(s0)
	j     label1
label2:
	li    t2, 256
	sw    t2, -72(s0)
	lw    t0, -28(s0)
	lw    t1, -72(s0)
	rem   t2, t0, t1
	sw    t2, -76(s0)
	lw    a0, -76(s0)
	j     func_end0
func_end0:
	ld    ra, 72(sp)
	ld    s0, 64(sp)
	addi  sp, sp, 80
	jr    ra
	.size    main,  .-main

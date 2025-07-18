	.file   "03.cact"
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
	li    t2, 8
	sw    t2, -24(s0)
	li    t2, 12
	sw    t2, -28(s0)
	lw    t0, -24(s0)
	lw    t1, -28(s0)
	addw  t2, t0, t1
	sw    t2, -32(s0)
	lw    t2, -32(s0)
	sw    t2, -20(s0)
	lw    a0, -20(s0)
	sw    a0, -36(s0)
	lw    a0, -36(s0)
	call  print_int
	nop
	lw    a0, -20(s0)
	j     func_end0
	li    t2, 9
	sw    t2, -40(s0)
	lw    t0, -20(s0)
	lw    t1, -40(s0)
	mul   t2, t0, t1
	sw    t2, -44(s0)
	lw    t2, -44(s0)
	sw    t2, -20(s0)
	lw    a0, -20(s0)
	sw    a0, -48(s0)
	lw    a0, -48(s0)
	call  print_int
	nop
	lw    a0, -20(s0)
	j     func_end0
	li    t2, 4
	sw    t2, -52(s0)
	lw    t0, -52(s0)
	lw    t1, -24(s0)
	subw  t2, t0, t1
	sw    t2, -56(s0)
	lw    t0, -56(s0)
	lw    t1, -28(s0)
	mul   t2, t0, t1
	sw    t2, -60(s0)
	lw    t2, -60(s0)
	sw    t2, -20(s0)
	lw    a0, -20(s0)
	sw    a0, -64(s0)
	lw    a0, -64(s0)
	call  print_int
	nop
	lw    a0, -20(s0)
	j     func_end0
	lw    a0, -20(s0)
	sw    a0, -68(s0)
	lw    a0, -68(s0)
	call  print_int
	nop
	lw    a0, -20(s0)
	j     func_end0
func_end0:
	ld    ra, 72(sp)
	ld    s0, 64(sp)
	addi  sp, sp, 80
	jr    ra
	.size    main,  .-main

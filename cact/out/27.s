	.file   "27.cact"
	.option nopic
	.attribute arch, "rv64i2p0_m2p0_a2p0_f2p0_d2p0_c2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	
	.text
	.align   1
	.globl   main
	.type    main, @function
main:
#frame size: 224
	addi  sp, sp, -224
	sd    ra, 216(sp)
	sd    s0, 208(sp)
	addi  s0, sp, 224
	li    t2, 5
	sw    t2, -40(s0)
	lw    t2, -40(s0)
	sw    t2, -20(s0)
	li    t2, 5
	sw    t2, -44(s0)
	lw    t2, -44(s0)
	sw    t2, -24(s0)
	li    t2, 1
	sw    t2, -48(s0)
	lw    t2, -48(s0)
	sw    t2, -28(s0)
	li    t2, 2
	sw    t2, -52(s0)
	li    t0, 0
	lw    t1, -52(s0)
	subw  t2, t0, t1
	sw    t2, -56(s0)
	lw    t2, -56(s0)
	sw    t2, -32(s0)
	li    t2, 2
	sw    t2, -60(s0)
	lw    t2, -60(s0)
	sw    t2, -36(s0)
	li    t2, 1
	sw    t2, -64(s0)
	lw    t0, -32(s0)
	lw    t1, -64(s0)
	mul   t2, t0, t1
	sw    t2, -68(s0)
	li    t2, 2
	sw    t2, -72(s0)
	lw    t0, -68(s0)
	lw    t1, -72(s0)
	div   t2, t0, t1
	sw    t2, -76(s0)
	li    t2, 0
	sw    t2, -80(s0)
	lw    t0, -76(s0)
	lw    t1, -80(s0)
	slt   t2, t0, t1
	sw    t2, -84(s0)
	lw    t0, -20(s0)
	lw    t1, -24(s0)
	subw  t2, t0, t1
	sw    t2, -88(s0)
	li    t2, 0
	sw    t2, -92(s0)
	lw    t0, -88(s0)
	lw    t1, -92(s0)
	subw  t2, t0, t1
	sltu  t2, zero, t2
	sw    t2, -96(s0)
	li    t2, 3
	sw    t2, -100(s0)
	lw    t0, -28(s0)
	lw    t1, -100(s0)
	addw  t2, t0, t1
	sw    t2, -104(s0)
	li    t2, 2
	sw    t2, -108(s0)
	lw    t0, -104(s0)
	lw    t1, -108(s0)
	rem   t2, t0, t1
	sw    t2, -112(s0)
	li    t2, 0
	sw    t2, -116(s0)
	lw    t0, -112(s0)
	lw    t1, -116(s0)
	subw  t2, t0, t1
	sltu  t2, zero, t2
	sw    t2, -120(s0)
	lw    t0, -96(s0)
	beqz  t0, and_false_0
	lw    t1, -120(s0)
	sw    t1, -124(s0)
	j     and_end_0
and_false_0:
	li    t2, 0
	sw    t2, -124(s0)
and_end_0:
	lw    t0, -84(s0)
	beqz  t0, or_eval_second_0
	li    t2, 1
	sw    t2, -128(s0)
	j     or_end_0
or_eval_second_0:
	lw    t1, -124(s0)
	sw    t1, -128(s0)
or_end_0:
	lw    t2, -128(s0)
	beqz  t2, label1
	lw    a0, -36(s0)
	call  print_int
	nop
label1:
	li    t2, 2
	sw    t2, -132(s0)
	lw    t0, -32(s0)
	lw    t1, -132(s0)
	rem   t2, t0, t1
	sw    t2, -136(s0)
	li    t2, 67
	sw    t2, -140(s0)
	lw    t0, -136(s0)
	lw    t1, -140(s0)
	addw  t2, t0, t1
	sw    t2, -144(s0)
	li    t2, 0
	sw    t2, -148(s0)
	lw    t0, -144(s0)
	lw    t1, -148(s0)
	slt   t2, t0, t1
	sw    t2, -152(s0)
	lw    t0, -20(s0)
	lw    t1, -24(s0)
	subw  t2, t0, t1
	sw    t2, -156(s0)
	li    t2, 0
	sw    t2, -160(s0)
	lw    t0, -156(s0)
	lw    t1, -160(s0)
	subw  t2, t0, t1
	sltu  t2, zero, t2
	sw    t2, -164(s0)
	li    t2, 2
	sw    t2, -168(s0)
	lw    t0, -28(s0)
	lw    t1, -168(s0)
	addw  t2, t0, t1
	sw    t2, -172(s0)
	li    t2, 2
	sw    t2, -176(s0)
	lw    t0, -172(s0)
	lw    t1, -176(s0)
	rem   t2, t0, t1
	sw    t2, -180(s0)
	li    t2, 0
	sw    t2, -184(s0)
	lw    t0, -180(s0)
	lw    t1, -184(s0)
	subw  t2, t0, t1
	sltu  t2, zero, t2
	sw    t2, -188(s0)
	lw    t0, -164(s0)
	beqz  t0, and_false_1
	lw    t1, -188(s0)
	sw    t1, -192(s0)
	j     and_end_1
and_false_1:
	li    t2, 0
	sw    t2, -192(s0)
and_end_1:
	lw    t0, -152(s0)
	beqz  t0, or_eval_second_1
	li    t2, 1
	sw    t2, -196(s0)
	j     or_end_1
or_eval_second_1:
	lw    t1, -192(s0)
	sw    t1, -196(s0)
or_end_1:
	lw    t2, -196(s0)
	beqz  t2, label2
	li    t2, 4
	sw    t2, -200(s0)
	lw    t2, -200(s0)
	sw    t2, -36(s0)
	lw    a0, -36(s0)
	call  print_int
	nop
label2:
	li    t2, 10
	sw    t2, -204(s0)
	lw    a0, -204(s0)
	call  print_char
	nop
	li    t2, 0
	sw    t2, -208(s0)
	lw    a0, -208(s0)
	sw    a0, -212(s0)
	lw    a0, -212(s0)
	call  print_int
	nop
	lw    a0, -208(s0)
	j     func_end0
func_end0:
	ld    ra, 216(sp)
	ld    s0, 208(sp)
	addi  sp, sp, 224
	jr    ra
	.size    main,  .-main

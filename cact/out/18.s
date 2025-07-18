	.file   "18.cact"
	.option nopic
	.attribute arch, "rv64i2p0_m2p0_a2p0_f2p0_d2p0_c2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	
	.text
	.align   1
	.globl   ifElseIf
	.type    ifElseIf, @function
ifElseIf:
#frame size: 112
	addi  sp, sp, -112
	sd    ra, 104(sp)
	sd    s0, 96(sp)
	addi  s0, sp, 112
	li    t2, 5
	sw    t2, -24(s0)
	lw    t2, -24(s0)
	sw    t2, -20(s0)
	li    t2, 10
	sw    t2, -32(s0)
	lw    t2, -32(s0)
	sw    t2, -28(s0)
	li    t2, 6
	sw    t2, -36(s0)
	lw    t0, -20(s0)
	lw    t1, -36(s0)
	subw  t2, t0, t1
	sltu  t2, zero, t2
	not   t2, t2
	andi  t2, t2, 1
	sw    t2, -40(s0)
	li    t2, 11
	sw    t2, -44(s0)
	lw    t0, -28(s0)
	lw    t1, -44(s0)
	subw  t2, t0, t1
	sltu  t2, zero, t2
	not   t2, t2
	andi  t2, t2, 1
	sw    t2, -48(s0)
	lw    t0, -40(s0)
	beqz  t0, or_eval_second_0
	li    t2, 1
	sw    t2, -52(s0)
	j     or_end_0
or_eval_second_0:
	lw    t1, -48(s0)
	sw    t1, -52(s0)
or_end_0:
	lw    t2, -52(s0)
	beqz  t2, label1
	lw    a0, -20(s0)
	j     func_end0
	j     label2
label1:
	li    t2, 10
	sw    t2, -56(s0)
	lw    t0, -28(s0)
	lw    t1, -56(s0)
	subw  t2, t0, t1
	sltu  t2, zero, t2
	not   t2, t2
	andi  t2, t2, 1
	sw    t2, -60(s0)
	li    t2, 1
	sw    t2, -64(s0)
	lw    t0, -20(s0)
	lw    t1, -64(s0)
	subw  t2, t0, t1
	sltu  t2, zero, t2
	not   t2, t2
	andi  t2, t2, 1
	sw    t2, -68(s0)
	lw    t0, -60(s0)
	beqz  t0, and_false_0
	lw    t1, -68(s0)
	sw    t1, -72(s0)
	j     and_end_0
and_false_0:
	li    t2, 0
	sw    t2, -72(s0)
and_end_0:
	lw    t2, -72(s0)
	beqz  t2, label3
	li    t2, 25
	sw    t2, -76(s0)
	lw    t2, -76(s0)
	sw    t2, -20(s0)
	j     label4
label3:
	li    t2, 10
	sw    t2, -80(s0)
	lw    t0, -28(s0)
	lw    t1, -80(s0)
	subw  t2, t0, t1
	sltu  t2, zero, t2
	not   t2, t2
	andi  t2, t2, 1
	sw    t2, -84(s0)
	li    t2, 5
	sw    t2, -88(s0)
	li    t0, 0
	lw    t1, -88(s0)
	subw  t2, t0, t1
	sw    t2, -92(s0)
	lw    t0, -20(s0)
	lw    t1, -92(s0)
	subw  t2, t0, t1
	sltu  t2, zero, t2
	not   t2, t2
	andi  t2, t2, 1
	sw    t2, -96(s0)
	lw    t0, -84(s0)
	beqz  t0, and_false_1
	lw    t1, -96(s0)
	sw    t1, -100(s0)
	j     and_end_1
and_false_1:
	li    t2, 0
	sw    t2, -100(s0)
and_end_1:
	lw    t2, -100(s0)
	beqz  t2, label5
	li    t2, 15
	sw    t2, -104(s0)
	lw    t0, -20(s0)
	lw    t1, -104(s0)
	addw  t2, t0, t1
	sw    t2, -108(s0)
	lw    t2, -108(s0)
	sw    t2, -20(s0)
	j     label6
label5:
	li    t0, 0
	lw    t1, -20(s0)
	subw  t2, t0, t1
	sw    t2, -112(s0)
	lw    t2, -112(s0)
	sw    t2, -20(s0)
label6:
label4:
label2:
	lw    a0, -20(s0)
	j     func_end0
func_end0:
	ld    ra, 104(sp)
	ld    s0, 96(sp)
	addi  sp, sp, 112
	jr    ra
	.size    ifElseIf,  .-ifElseIf
	
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
	call  ifElseIf
	nop
	sw    a0, -20(s0)
	lw    a0, -20(s0)
	call  print_int
	nop
	li    t2, 10
	sw    t2, -24(s0)
	lw    a0, -24(s0)
	call  print_char
	nop
	li    t2, 0
	sw    t2, -28(s0)
	lw    a0, -28(s0)
	sw    a0, -32(s0)
	lw    a0, -32(s0)
	call  print_int
	nop
	lw    a0, -28(s0)
	j     func_end1
func_end1:
	ld    ra, 24(sp)
	ld    s0, 16(sp)
	addi  sp, sp, 32
	jr    ra
	.size    main,  .-main

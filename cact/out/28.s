	.file   "28.cact"
	.option nopic
	.attribute arch, "rv64i2p0_m2p0_a2p0_f2p0_d2p0_c2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	
	.globl   g
	.section .sdata, "aw"
	.align   2
	.type    g, @object
	.size    g, 4
g:
	.word    0
	
	.text
	.align   1
	.globl   func
	.type    func, @function
func:
#frame size: 32
	addi  sp, sp, -32
	sd    ra, 24(sp)
	sd    s0, 16(sp)
	addi  s0, sp, 32
	mv    t2, a0
	sw    t2, -20(s0)
	lui   t5, %hi(g)
	lw    t0, %lo(g)(t5)
	lw    t1, -20(s0)
	addw  t2, t0, t1
	sw    t2, -24(s0)
	lw    t2, -24(s0)
	lui   t5, %hi(g)
	sw    t2, %lo(g)(t5)
	lui   t5, %hi(g)
	lw    a0, %lo(g)(t5)
	call  print_int
	nop
	lui   t5, %hi(g)
	lw    a0, %lo(g)(t5)
	j     func_end0
func_end0:
	ld    ra, 24(sp)
	ld    s0, 16(sp)
	addi  sp, sp, 32
	jr    ra
	.size    func,  .-func
	
	.text
	.align   1
	.globl   main
	.type    main, @function
main:
#frame size: 176
	addi  sp, sp, -176
	sd    ra, 168(sp)
	sd    s0, 160(sp)
	addi  s0, sp, 176
	call  get_int
	nop
	sw    a0, -24(s0)
	lw    t2, -24(s0)
	sw    t2, -20(s0)
	li    t2, 10
	sw    t2, -28(s0)
	lw    t0, -20(s0)
	lw    t1, -28(s0)
	slt   t2, t1, t0
	sw    t2, -32(s0)
	lw    a0, -20(s0)
	call  func
	nop
	sw    a0, -36(s0)
	lw    t0, -32(s0)
	beqz  t0, and_false_0
	lw    t1, -36(s0)
	sw    t1, -40(s0)
	j     and_end_0
and_false_0:
	li    t2, 0
	sw    t2, -40(s0)
and_end_0:
	lw    t2, -40(s0)
	beqz  t2, label1
	li    t2, 1
	sw    t2, -44(s0)
	lw    t2, -44(s0)
	sw    t2, -20(s0)
	j     label2
label1:
	li    t2, 0
	sw    t2, -48(s0)
	lw    t2, -48(s0)
	sw    t2, -20(s0)
label2:
	call  get_int
	nop
	sw    a0, -52(s0)
	lw    t2, -52(s0)
	sw    t2, -20(s0)
	li    t2, 11
	sw    t2, -56(s0)
	lw    t0, -20(s0)
	lw    t1, -56(s0)
	slt   t2, t1, t0
	sw    t2, -60(s0)
	lw    a0, -20(s0)
	call  func
	nop
	sw    a0, -64(s0)
	lw    t0, -60(s0)
	beqz  t0, and_false_1
	lw    t1, -64(s0)
	sw    t1, -68(s0)
	j     and_end_1
and_false_1:
	li    t2, 0
	sw    t2, -68(s0)
and_end_1:
	lw    t2, -68(s0)
	beqz  t2, label3
	li    t2, 1
	sw    t2, -72(s0)
	lw    t2, -72(s0)
	sw    t2, -20(s0)
	j     label4
label3:
	li    t2, 0
	sw    t2, -76(s0)
	lw    t2, -76(s0)
	sw    t2, -20(s0)
label4:
	call  get_int
	nop
	sw    a0, -80(s0)
	lw    t2, -80(s0)
	sw    t2, -20(s0)
	li    t2, 99
	sw    t2, -84(s0)
	lw    t0, -20(s0)
	lw    t1, -84(s0)
	slt   t2, t1, t0
	not   t2, t2
	andi  t2, t2, 1
	sw    t2, -88(s0)
	lw    a0, -20(s0)
	call  func
	nop
	sw    a0, -92(s0)
	lw    t0, -88(s0)
	beqz  t0, or_eval_second_0
	li    t2, 1
	sw    t2, -96(s0)
	j     or_end_0
or_eval_second_0:
	lw    t1, -92(s0)
	sw    t1, -96(s0)
or_end_0:
	lw    t2, -96(s0)
	beqz  t2, label5
	li    t2, 1
	sw    t2, -100(s0)
	lw    t2, -100(s0)
	sw    t2, -20(s0)
	j     label6
label5:
	li    t2, 0
	sw    t2, -104(s0)
	lw    t2, -104(s0)
	sw    t2, -20(s0)
label6:
	call  get_int
	nop
	sw    a0, -108(s0)
	lw    t2, -108(s0)
	sw    t2, -20(s0)
	li    t2, 100
	sw    t2, -112(s0)
	lw    t0, -20(s0)
	lw    t1, -112(s0)
	slt   t2, t1, t0
	not   t2, t2
	andi  t2, t2, 1
	sw    t2, -116(s0)
	lw    a0, -20(s0)
	call  func
	nop
	sw    a0, -120(s0)
	lw    t0, -116(s0)
	beqz  t0, or_eval_second_1
	li    t2, 1
	sw    t2, -124(s0)
	j     or_end_1
or_eval_second_1:
	lw    t1, -120(s0)
	sw    t1, -124(s0)
or_end_1:
	lw    t2, -124(s0)
	beqz  t2, label7
	li    t2, 1
	sw    t2, -128(s0)
	lw    t2, -128(s0)
	sw    t2, -20(s0)
	j     label8
label7:
	li    t2, 0
	sw    t2, -132(s0)
	lw    t2, -132(s0)
	sw    t2, -20(s0)
label8:
	li    t2, 99
	sw    t2, -136(s0)
	lw    a0, -136(s0)
	call  func
	nop
	sw    a0, -140(s0)
	lw    t2, -140(s0)
	sltu  t2, zero, t2
	not   t2, t2
	andi  t2, t2, 1
	sw    t2, -144(s0)
	li    t2, 100
	sw    t2, -148(s0)
	lw    a0, -148(s0)
	call  func
	nop
	sw    a0, -152(s0)
	lw    t0, -144(s0)
	beqz  t0, and_false_2
	lw    t1, -152(s0)
	sw    t1, -156(s0)
	j     and_end_2
and_false_2:
	li    t2, 0
	sw    t2, -156(s0)
and_end_2:
	lw    t2, -156(s0)
	beqz  t2, label9
	li    t2, 1
	sw    t2, -160(s0)
	lw    t2, -160(s0)
	sw    t2, -20(s0)
	j     label10
label9:
	li    t2, 0
	sw    t2, -164(s0)
	lw    t2, -164(s0)
	sw    t2, -20(s0)
label10:
	li    t2, 10
	sw    t2, -168(s0)
	lw    a0, -168(s0)
	call  print_char
	nop
	li    t2, 0
	sw    t2, -172(s0)
	lw    a0, -172(s0)
	sw    a0, -176(s0)
	lw    a0, -176(s0)
	call  print_int
	nop
	lw    a0, -172(s0)
	j     func_end1
func_end1:
	ld    ra, 168(sp)
	ld    s0, 160(sp)
	addi  sp, sp, 176
	jr    ra
	.size    main,  .-main

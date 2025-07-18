	.file   "31.cact"
	.option nopic
	.attribute arch, "rv64i2p0_m2p0_a2p0_f2p0_d2p0_c2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	
	.globl   k
	.bss
	.align   2
	.type    k, @object
	.size    k, 4
k:
	.zero    4
	
	.text
	.align   1
	.globl   main
	.type    main, @function
main:
#frame size: 112
	addi  sp, sp, -112
	sd    ra, 104(sp)
	sd    s0, 96(sp)
	addi  s0, sp, 112
	li    t2, 3389
	sw    t2, -20(s0)
	lw    t2, -20(s0)
	lui   t5, %hi(k)
	sw    t2, %lo(k)(t5)
	li    t2, 10000
	sw    t2, -24(s0)
	lui   t5, %hi(k)
	lw    t0, %lo(k)(t5)
	lw    t1, -24(s0)
	slt   t2, t0, t1
	sw    t2, -28(s0)
	lw    t2, -28(s0)
	beqz  t2, label1
	li    t2, 1
	sw    t2, -32(s0)
	lui   t5, %hi(k)
	lw    t0, %lo(k)(t5)
	lw    t1, -32(s0)
	addw  t2, t0, t1
	sw    t2, -36(s0)
	lw    t2, -36(s0)
	lui   t5, %hi(k)
	sw    t2, %lo(k)(t5)
	li    t2, 112
	sw    t2, -40(s0)
label2:
	li    t2, 10
	sw    t2, -44(s0)
	lw    t0, -40(s0)
	lw    t1, -44(s0)
	slt   t2, t1, t0
	sw    t2, -48(s0)
	lw    t2, -48(s0)
	beqz  t2, label3
	li    t2, 88
	sw    t2, -52(s0)
	lw    t0, -40(s0)
	lw    t1, -52(s0)
	subw  t2, t0, t1
	sw    t2, -56(s0)
	lw    t2, -56(s0)
	sw    t2, -40(s0)
	li    t2, 1000
	sw    t2, -60(s0)
	lw    t0, -40(s0)
	lw    t1, -60(s0)
	slt   t2, t0, t1
	sw    t2, -64(s0)
	lw    t2, -64(s0)
	beqz  t2, label4
	li    t2, 9
	sw    t2, -68(s0)
	li    t2, 11
	sw    t2, -72(s0)
	li    t2, 10
	sw    t2, -76(s0)
	lw    t2, -76(s0)
	sw    t2, -68(s0)
	lw    t0, -40(s0)
	lw    t1, -68(s0)
	subw  t2, t0, t1
	sw    t2, -80(s0)
	lw    t2, -80(s0)
	sw    t2, -40(s0)
	li    t2, 11
	sw    t2, -84(s0)
	lw    t0, -40(s0)
	lw    t1, -84(s0)
	addw  t2, t0, t1
	sw    t2, -88(s0)
	lw    t0, -88(s0)
	lw    t1, -72(s0)
	addw  t2, t0, t1
	sw    t2, -92(s0)
	lw    t2, -92(s0)
	sw    t2, -40(s0)
label4:
	j     label2
label3:
	lw    a0, -40(s0)
	call  print_int
	nop
label1:
	li    t2, 10
	sw    t2, -96(s0)
	lw    a0, -96(s0)
	call  print_char
	nop
	lui   t5, %hi(k)
	lw    a0, %lo(k)(t5)
	sw    a0, -100(s0)
	lw    a0, -100(s0)
	call  print_int
	nop
	lui   t5, %hi(k)
	lw    a0, %lo(k)(t5)
	j     func_end0
func_end0:
	ld    ra, 104(sp)
	ld    s0, 96(sp)
	addi  sp, sp, 112
	jr    ra
	.size    main,  .-main

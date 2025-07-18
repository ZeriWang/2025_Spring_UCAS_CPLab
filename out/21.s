	.file   "21.cact"
	.option nopic
	.attribute arch, "rv64i2p0_m2p0_a2p0_f2p0_d2p0_c2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	
	.text
	.align   1
	.globl   whileIf
	.type    whileIf, @function
whileIf:
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
	li    t2, 5
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
	li    t2, 25
	sw    t2, -52(s0)
	lw    t2, -52(s0)
	sw    t2, -28(s0)
	j     label4
label3:
	li    t2, 10
	sw    t2, -56(s0)
	lw    t0, -20(s0)
	lw    t1, -56(s0)
	subw  t2, t0, t1
	sltu  t2, zero, t2
	not   t2, t2
	andi  t2, t2, 1
	sw    t2, -60(s0)
	lw    t2, -60(s0)
	beqz  t2, label5
	li    t2, 42
	sw    t2, -64(s0)
	lw    t2, -64(s0)
	sw    t2, -28(s0)
	j     label6
label5:
	li    t2, 2
	sw    t2, -68(s0)
	lw    t0, -20(s0)
	lw    t1, -68(s0)
	mul   t2, t0, t1
	sw    t2, -72(s0)
	lw    t2, -72(s0)
	sw    t2, -28(s0)
label6:
label4:
	li    t2, 1
	sw    t2, -76(s0)
	lw    t0, -20(s0)
	lw    t1, -76(s0)
	addw  t2, t0, t1
	sw    t2, -80(s0)
	lw    t2, -80(s0)
	sw    t2, -20(s0)
	j     label1
label2:
	lw    a0, -28(s0)
	j     func_end0
func_end0:
	ld    ra, 72(sp)
	ld    s0, 64(sp)
	addi  sp, sp, 80
	jr    ra
	.size    whileIf,  .-whileIf
	
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
	call  whileIf
	nop
	sw    a0, -20(s0)
	lw    a0, -20(s0)
	sw    a0, -24(s0)
	lw    a0, -24(s0)
	call  print_int
	nop
	lw    a0, -20(s0)
	j     func_end1
func_end1:
	ld    ra, 24(sp)
	ld    s0, 16(sp)
	addi  sp, sp, 32
	jr    ra
	.size    main,  .-main

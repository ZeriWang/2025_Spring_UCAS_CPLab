	.file   "25.cact"
	.option nopic
	.attribute arch, "rv64i2p0_m2p0_a2p0_f2p0_d2p0_c2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	
	.globl   a
	.bss
	.align   2
	.type    a, @object
	.size    a, 4
a:
	.zero    4
	
	.globl   b
	.bss
	.align   2
	.type    b, @object
	.size    b, 4
b:
	.zero    4
	
	.text
	.align   1
	.globl   main
	.type    main, @function
main:
#frame size: 64
	addi  sp, sp, -64
	sd    ra, 56(sp)
	sd    s0, 48(sp)
	addi  s0, sp, 64
	call  get_int
	nop
	sw    a0, -20(s0)
	lw    t2, -20(s0)
	lui   t5, %hi(a)
	sw    t2, %lo(a)(t5)
	call  get_int
	nop
	sw    a0, -24(s0)
	lw    t2, -24(s0)
	lui   t5, %hi(b)
	sw    t2, %lo(b)(t5)
	lui   t5, %hi(a)
	lw    t0, %lo(a)(t5)
	lui   t5, %hi(b)
	lw    t1, %lo(b)(t5)
	subw  t2, t0, t1
	sltu  t2, zero, t2
	not   t2, t2
	andi  t2, t2, 1
	sw    t2, -32(s0)
	li    t2, 3
	sw    t2, -36(s0)
	lui   t5, %hi(a)
	lw    t0, %lo(a)(t5)
	lw    t1, -36(s0)
	subw  t2, t0, t1
	sltu  t2, zero, t2
	sw    t2, -40(s0)
	lw    t0, -32(s0)
	lw    t1, -40(s0)
	and   t2, t0, t1
	sw    t2, -44(s0)
	lw    t2, -44(s0)
	beqz  t2, label1
	li    t2, 1
	sw    t2, -48(s0)
	lw    t2, -48(s0)
	sw    t2, -28(s0)
	j     label2
label1:
	li    t2, 0
	sw    t2, -52(s0)
	lw    t2, -52(s0)
	sw    t2, -28(s0)
label2:
	lw    a0, -28(s0)
	sw    a0, -56(s0)
	lw    a0, -56(s0)
	call  print_int
	nop
	lw    a0, -28(s0)
	j     func_end0
func_end0:
	ld    ra, 56(sp)
	ld    s0, 48(sp)
	addi  sp, sp, 64
	jr    ra
	.size    main,  .-main

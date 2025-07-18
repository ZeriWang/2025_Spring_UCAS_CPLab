	.file   "23.cact"
	.option nopic
	.attribute arch, "rv64i2p0_m2p0_a2p0_f2p0_d2p0_c2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	
	.globl   a
	.section .sdata, "aw"
	.align   2
	.type    a, @object
	.size    a, 4
a:
	.word    1
	
	.globl   b
	.section .sdata, "aw"
	.align   2
	.type    b, @object
	.size    b, 4
b:
	.word    0
	
	.globl   c
	.section .sdata, "aw"
	.align   2
	.type    c, @object
	.size    c, 4
c:
	.word    1
	
	.globl   d
	.section .sdata, "aw"
	.align   2
	.type    d, @object
	.size    d, 4
d:
	.word    2
	
	.globl   e
	.section .sdata, "aw"
	.align   2
	.type    e, @object
	.size    e, 4
e:
	.word    4
	
	.text
	.align   1
	.globl   main
	.type    main, @function
main:
#frame size: 96
	addi  sp, sp, -96
	sd    ra, 88(sp)
	sd    s0, 80(sp)
	addi  s0, sp, 96
	li    t2, 0
	sw    t2, -20(s0)
	lui   t5, %hi(a)
	lw    t0, %lo(a)(t5)
	lui   t5, %hi(b)
	lw    t1, %lo(b)(t5)
	mul   t2, t0, t1
	sw    t2, -24(s0)
	lw    t0, -24(s0)
	lui   t5, %hi(c)
	lw    t1, %lo(c)(t5)
	div   t2, t0, t1
	sw    t2, -28(s0)
	lui   t5, %hi(e)
	lw    t0, %lo(e)(t5)
	lui   t5, %hi(d)
	lw    t1, %lo(d)(t5)
	addw  t2, t0, t1
	sw    t2, -32(s0)
	lw    t0, -28(s0)
	lw    t1, -32(s0)
	subw  t2, t0, t1
	sltu  t2, zero, t2
	not   t2, t2
	andi  t2, t2, 1
	sw    t2, -36(s0)
	lui   t5, %hi(a)
	lw    t0, %lo(a)(t5)
	lui   t5, %hi(b)
	lw    t1, %lo(b)(t5)
	addw  t2, t0, t1
	sw    t2, -40(s0)
	lui   t5, %hi(a)
	lw    t0, %lo(a)(t5)
	lw    t1, -40(s0)
	mul   t2, t0, t1
	sw    t2, -44(s0)
	lw    t0, -44(s0)
	lui   t5, %hi(c)
	lw    t1, %lo(c)(t5)
	addw  t2, t0, t1
	sw    t2, -48(s0)
	lui   t5, %hi(d)
	lw    t0, %lo(d)(t5)
	lui   t5, %hi(e)
	lw    t1, %lo(e)(t5)
	addw  t2, t0, t1
	sw    t2, -52(s0)
	lw    t0, -48(s0)
	lw    t1, -52(s0)
	slt   t2, t1, t0
	not   t2, t2
	andi  t2, t2, 1
	sw    t2, -56(s0)
	lw    t0, -36(s0)
	lw    t1, -56(s0)
	and   t2, t0, t1
	sw    t2, -60(s0)
	lui   t5, %hi(b)
	lw    t0, %lo(b)(t5)
	lui   t5, %hi(c)
	lw    t1, %lo(c)(t5)
	mul   t2, t0, t1
	sw    t2, -64(s0)
	lui   t5, %hi(a)
	lw    t0, %lo(a)(t5)
	lw    t1, -64(s0)
	subw  t2, t0, t1
	sw    t2, -68(s0)
	lui   t5, %hi(a)
	lw    t0, %lo(a)(t5)
	lui   t5, %hi(c)
	lw    t1, %lo(c)(t5)
	div   t2, t0, t1
	sw    t2, -72(s0)
	lui   t5, %hi(d)
	lw    t0, %lo(d)(t5)
	lw    t1, -72(s0)
	subw  t2, t0, t1
	sw    t2, -76(s0)
	lw    t0, -68(s0)
	lw    t1, -76(s0)
	subw  t2, t0, t1
	sltu  t2, zero, t2
	not   t2, t2
	andi  t2, t2, 1
	sw    t2, -80(s0)
	lw    t0, -60(s0)
	lw    t1, -80(s0)
	or    t2, t0, t1
	sw    t2, -84(s0)
	lw    t2, -84(s0)
	beqz  t2, label1
	li    t2, 1
	sw    t2, -88(s0)
	lw    t2, -88(s0)
	sw    t2, -20(s0)
label1:
	lw    a0, -20(s0)
	call  print_int
	nop
	li    t2, 10
	sw    t2, -92(s0)
	lw    a0, -92(s0)
	call  print_char
	nop
	lw    a0, -20(s0)
	sw    a0, -96(s0)
	lw    a0, -96(s0)
	call  print_int
	nop
	lw    a0, -20(s0)
	j     func_end0
func_end0:
	ld    ra, 88(sp)
	ld    s0, 80(sp)
	addi  sp, sp, 96
	jr    ra
	.size    main,  .-main

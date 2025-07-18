	.file   "08.cact"
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
	li    t2, 1
	sw    t2, -24(s0)
	lw    t0, -20(s0)
	lw    t1, -24(s0)
	subw  t2, t0, t1
	sw    t2, -28(s0)
	lw    t2, -28(s0)
	sw    t2, -20(s0)
	lw    a0, -20(s0)
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
#frame size: 32
	addi  sp, sp, -32
	sd    ra, 24(sp)
	sd    s0, 16(sp)
	addi  s0, sp, 32
	li    t2, 10
	sw    t2, -24(s0)
	lw    t2, -24(s0)
	lui   t5, %hi(a)
	sw    t2, %lo(a)(t5)
	lui   t5, %hi(a)
	lw    a0, %lo(a)(t5)
	call  func
	nop
	sw    a0, -28(s0)
	lw    t2, -28(s0)
	sw    t2, -20(s0)
	lw    a0, -20(s0)
	sw    a0, -32(s0)
	lw    a0, -32(s0)
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

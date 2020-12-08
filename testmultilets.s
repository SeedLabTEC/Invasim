	.file	"testmultilets.c"
	.option nopic
	.attribute arch, "rv64i2p0_m2p0_a2p0_f2p0_d2p0_c2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.align	1
	.globl	foo
	.type	foo, @function
foo:
	addi	sp,sp,-64
	sd	s0,56(sp)
	addi	s0,sp,64
	li	a5,27
	sw	a5,-20(s0)
	li	a5,28
	sw	a5,-24(s0)
	li	a5,29
	sw	a5,-28(s0)
	li	a5,30
	sw	a5,-32(s0)
	li	a5,31
	sw	a5,-36(s0)
	li	a5,32
	sw	a5,-40(s0)
	lw	a4,-20(s0)
	lw	a5,-24(s0)
	mulw	a5,a4,a5
	sw	a5,-44(s0)
	lw	a4,-28(s0)
	lw	a5,-32(s0)
	mulw	a5,a4,a5
	sw	a5,-48(s0)
	lw	a4,-36(s0)
	lw	a5,-40(s0)
	mulw	a5,a4,a5
	sw	a5,-52(s0)
	nop
	mv	a0,a5
	ld	s0,56(sp)
	addi	sp,sp,64
	jr	ra
	.size	foo, .-foo
	.align	1
	.globl	main
	.type	main, @function
main:
	addi	sp,sp,-16
	sd	ra,8(sp)
	sd	s0,0(sp)
	addi	s0,sp,16
	call	foo
	li	a5,0
	mv	a0,a5
	ld	ra,8(sp)
	ld	s0,0(sp)
	addi	sp,sp,16
	jr	ra
	.size	main, .-main
	.ident	"GCC: (GNU) 10.2.0"

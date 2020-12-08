	.file	"main.c"
	.option nopic
	.attribute arch, "rv64i2p0_m2p0_a2p0_f2p0_d2p0_c2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.align	1
	.globl	mult
	.type	mult, @function
mult:
	addi	sp,sp,-32
	sd	s0,24(sp)
	addi	s0,sp,32
	li	a5,1000
	sw	a5,-20(s0)
	li	a5,3
	sw	a5,-24(s0)
	li	a5,500
	sw	a5,-28(s0)
	li	a5,2
	sw	a5,-32(s0)
	lw	a4,-20(s0)
	lw	a5,-24(s0)
	mulw	a5,a4,a5
	sext.w	a5,a5
	lw	a4,-28(s0)
	mulw	a5,a4,a5
	sext.w	a5,a5
	lw	a4,-32(s0)
	mulw	a5,a4,a5
	sext.w	a5,a5
	mv	a0,a5
	ld	s0,24(sp)
	addi	sp,sp,32
	jr	ra
	.size	mult, .-mult
	.align	1
	.globl	main
	.type	main, @function
main:
	addi	sp,sp,-32
	sd	ra,24(sp)
	sd	s0,16(sp)
	addi	s0,sp,32
	call	mult
	mv	a5,a0
	sw	a5,-20(s0)
	sw	zero,-20(s0)
	lw	a5,-20(s0)
	sext.w	a5,a5
	beq	a5,zero,.L4
	li	a5,2
	sw	a5,-24(s0)
.L4:
	li	a5,32
	sw	a5,-28(s0)
	li	a5,0
	mv	a0,a5
	ld	ra,24(sp)
	ld	s0,16(sp)
	addi	sp,sp,32
	jr	ra
	.size	main, .-main
	.ident	"GCC: (GNU) 10.2.0"

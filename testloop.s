	.file	"testloop.c"
	.option nopic
	.attribute arch, "rv64i2p0_m2p0_a2p0_f2p0_d2p0_c2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.align	1
	.globl	loop
	.type	loop, @function
loop:
	addi	sp,sp,-32
	sd	s0,24(sp)
	addi	s0,sp,32
	sw	zero,-20(s0)
.L2:
	flw	fa5,-20(s0)
	fcvt.d.s	fa4,fa5
	lui	a5,%hi(.LC0)
	fld	fa5,%lo(.LC0)(a5)
	fadd.d	fa5,fa4,fa5
	fcvt.s.d	fa5,fa5
	fsw	fa5,-20(s0)
	j	.L2
	.size	loop, .-loop
	.align	1
	.globl	main
	.type	main, @function
main:
	addi	sp,sp,-16
	sd	ra,8(sp)
	sd	s0,0(sp)
	addi	s0,sp,16
	call	loop
	li	a5,0
	mv	a0,a5
	ld	ra,8(sp)
	ld	s0,0(sp)
	addi	sp,sp,16
	jr	ra
	.size	main, .-main
	.section	.rodata
	.align	3
.LC0:
	.word	-350469331
	.word	1058682594
	.ident	"GCC: (GNU) 10.2.0"

	.file	"main2.c"
	.option nopic
	.attribute arch, "rv64i2p0_m2p0_a2p0_f2p0_d2p0_c2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.align	1
	.globl	main
	.type	main, @function
main:
	addi	sp,sp,-32
	sd	s0,24(sp)
	addi	s0,sp,32
	sw	zero,-20(s0)
	sw	zero,-24(s0)
	j	.L2
.L3:
	lw	a5,-20(s0)
	addiw	a5,a5,7
	sext.w	a5,a5
	mv	a4,a5
	mv	a5,a4
	slliw	a5,a5,2
	addw	a5,a5,a4
	sw	a5,-20(s0)
	lw	a5,-20(s0)
	addiw	a5,a5,11
	sext.w	a5,a5
	mv	a4,a5
	mv	a5,a4
	slliw	a5,a5,3
	addw	a5,a5,a4
	sw	a5,-20(s0)
	lw	a5,-20(s0)
	addiw	a5,a5,13
	sext.w	a5,a5
	mv	a4,a5
	mv	a5,a4
	slliw	a5,a5,1
	addw	a5,a5,a4
	slliw	a5,a5,2
	sw	a5,-20(s0)
	lw	a5,-20(s0)
	addiw	a5,a5,17
	sext.w	a5,a5
	mv	a4,a5
	mv	a5,a4
	slliw	a5,a5,4
	subw	a5,a5,a4
	sw	a5,-20(s0)
	lw	a5,-20(s0)
	addiw	a5,a5,19
	sext.w	a5,a5
	mv	a4,a5
	mv	a5,a4
	slliw	a5,a5,3
	addw	a5,a5,a4
	slliw	a5,a5,1
	sw	a5,-20(s0)
	lw	a5,-20(s0)
	addiw	a5,a5,23
	sext.w	a5,a5
	mv	a4,a5
	mv	a5,a4
	slliw	a5,a5,2
	addw	a5,a5,a4
	slliw	a5,a5,2
	sw	a5,-20(s0)
	lw	a5,-20(s0)
	addiw	a5,a5,29
	sext.w	a5,a5
	mv	a4,a5
	mv	a5,a4
	slliw	a5,a5,1
	addw	a5,a5,a4
	slliw	a5,a5,3
	addw	a5,a5,a4
	sw	a5,-20(s0)
	lw	a5,-20(s0)
	addiw	a5,a5,31
	sext.w	a5,a5
	mv	a4,a5
	mv	a5,a4
	slliw	a5,a5,3
	subw	a5,a5,a4
	slliw	a5,a5,2
	subw	a5,a5,a4
	sw	a5,-20(s0)
	lw	a5,-24(s0)
	addiw	a5,a5,1
	sw	a5,-24(s0)
.L2:
	lw	a5,-24(s0)
	sext.w	a4,a5
	li	a5,1000001536
	addi	a5,a5,-1537
	ble	a4,a5,.L3
	lw	a5,-20(s0)
	mv	a0,a5
	ld	s0,24(sp)
	addi	sp,sp,32
	jr	ra
	.size	main, .-main
	.ident	"GCC: (GNU) 10.2.0"

mult:
	addi	sp,sp,-32
	sw	s0,28(sp)
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
	mul	a4,a4,a5
	lw	a5,-28(s0)
	mul	a4,a4,a5
	lw	a5,-32(s0)
	mul	a5,a4,a5
	mv	a0,a5
	lw	s0,28(sp)
	addi	sp,sp,32
	jr	ra
main:
	addi	sp,sp,-32
	sw	ra,28(sp)
	sw	s0,24(sp)
	addi	s0,sp,32
	call	mult
	sw	a0,-20(s0)
	sw	zero,-20(s0)
	lw	a5,-20(s0)
	beq	a5,zero,.L4
	li	a5,2
	sw	a5,-24(s0)
.L4:
	li	a5,32
	sw	a5,-28(s0)
	li	a5,0
	mv	a0,a5
	lw	ra,28(sp)
	lw	s0,24(sp)
	addi	sp,sp,32
	jr	ra
	.size	main, .-main
	.ident	"GCC: (GNU) 9.2.0"

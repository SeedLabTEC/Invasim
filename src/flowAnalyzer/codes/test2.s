	.file	"test2.c"
	.option nopic
	.attribute arch, "rv32i2p0_m2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.align	2
	.globl	main
	.type	main, @function
main:
	li	a4,1000001536
	addi	a4,a4,-1536
	li	a0,0
.L2:
	addi	a0,a0,7
	slli	a5,a0,2
	add	a0,a5,a0
	addi	a0,a0,11
	slli	a5,a0,3
	add	a5,a5,a0
	addi	a0,a5,13
	slli	a5,a0,1
	add	a5,a5,a0
	slli	a5,a5,2
	addi	a5,a5,17
	slli	a0,a5,4
	sub	a5,a0,a5
	addi	a5,a5,19
	slli	a0,a5,3
	add	a0,a0,a5
	slli	a0,a0,1
	addi	a5,a0,23
	slli	a0,a5,2
	add	a0,a0,a5
	slli	a0,a0,2
	addi	a5,a0,29
	slli	a0,a5,1
	add	a0,a0,a5
	slli	a0,a0,3
	add	a0,a0,a5
	addi	a0,a0,31
	slli	a5,a0,3
	sub	a5,a5,a0
	slli	a5,a5,2
	sub	a0,a5,a0
	addi	a4,a4,-1
	bne	a4,zero,.L2
	ret
	.size	main, .-main
	.ident	"GCC: (GNU) 9.2.0"

	.file	"string.h"
	.text
	
# char *byLine(FILE *f, char *buf, int n)
	
	.globl	byLineF
	.type	byLineF,	@function

byLineF:
	pushq	%rbx
	movq	%rdx,	%rcx
#	movl	112(%rdi),	%eax
#	cltq
#	mov	%rax,	%rdi
	movsxdl	112(%rdi),	%rdi
	xorq	%rbx,	%rbx
.L6:
	xorq	%rax,	%rax
	movq	$1,	%rdx
	push	%rdi
	push	%rcx
	syscall
	pop	%rcx
	pop	%rdi
	cmpb	$0,	%al
	je	.L8
	incq	%rbx
	cmpb	$0,	(%rsi)
	je	.L8
	cmpb	$10,	(%rsi)
	je	.L7
	incq	%rsi
	loop	.L6
.L7:
	movq	$0,	(%rsi)
.L8:
	movq	%rbx,	%rax
	popq	%rbx
	ret

# char *byPerimeterF(FILE *f, char *buf, int n, char perimeter)
	.globl	byPerimeterF
	.type	byPerimeterF,	@function

byPerimeterF:
	pushq	%rbx
	pushq	%r12
	movb	%cl,	%bl
	movq	%rdx,	%rcx
	movsxdl	112(%rdi),	%rdi
	xorq	%r12,	%r12
.L14:
	xorq	%rax,	%rax
	movq	$1,	%rdx
	push	%rdi
	push	%rcx
	syscall
	pop	%rcx
	pop	%rdi
	cmpb	$0,	%al
	je	.L16
	incq	%r12
	cmpb	$0,	(%rsi)
	je	.L16
	cmpb	%bl,	(%rsi)
	je	.L15
	incq	%rsi
	loop	.L14
.L15:
	movq	$0,	(%rsi)
.L16:
	movq	%r12,	%rax
	popq	%r12
	popq	%rbx
	ret
	
# char *byPerimeterS(char *str, char *buf, int n, char perimeter)

	.globl	byPerimeterS
	.type	byPerimeterS,	@function

byPerimeterS:
	pushq	%rbx
	xorq	%rbx,	%rbx
	movb	%cl,	%bl
	movq	%rdx,	%rcx
	xchgq	%rdi,	%rsi
.L9:
	lodsb
	stosb
	cmpb	$0,	%al
	je	.L11
	cmpb	%bl,	%al
	je	.L10
	loop	.L9
.L10:
	movb	$0,	-1(%rdi)
	jmp	.L13
.L11:
	decq	%rsi
.L13:
	popq	%rbx
	movq	%rsi,	%rax
	ret
	
# char *byLineS(char *str, char *buf, int n)
	
	.globl	byLineS
	.type	byLineS,	@function

byLineS:
	movq	%rdx,	%rcx
	xchgq	%rdi,	%rsi
.L3:
	lodsb
	stosb
	cmpb	$0,	%al
	je	.L5
	cmpb	$10,	%al
	je	.L4
	loop	.L3
.L4:
	movb	$0,	-1(%rdi)
	jmp	.L12
.L5:
	decq	%rsi
.L12:
	movq	%rsi,	%rax
	ret

	.globl	getFD
	.type	getFD,	@function

# int getFD(FILE *f)
	
getFD:
	xor	%rax,	%rax
	movl	112(%rdi),	%eax
	ret
		.global negate
		.global absolute
		
		.global	add
		.global	sub
		.global	mul
		.global	divide
		.global	remain
		
		.global	power
		.global	factorial
		
		.text
		
@@@@@@@@@@@@@	NEGATE	@@@@@@@@@@@@@			
negate:
		push {lr}
		rsb r0, r0, #0		@reverse sub from 0 to negate 
		pop	{lr}
		bx	lr

@@@@@@@@@@@@@	ABSOLUTE	@@@@@@@@@@@@@	
absolute:
		push {r4, r5, lr}
		
		asr	r4, r0, #31		@signextended shift to isolate sign
		eor	r5, r0, r4		@XOR has effect of NOT on negative nums
		sub r0, r5, r4		@has effect of adding 1 to negative nums
							@combined ops "undo" twos compliment on negs
		pop	{r4, r5, lr}
		bx	lr

@@@@@@@@@@@@@	ADD	@@@@@@@@@@@@@	
add:
		push {lr}
		adds r0, r0, r1
		bvc	vld_add
		ldr r0, =ERR
		ldr r0, [r0]
		
vld_add:
		pop	{lr}
		bx	lr

@@@@@@@@@@@@@	SUBTRACT	@@@@@@@@@@@@@	
sub:
		push {lr}
		subs r0, r0, r1
		bvc	vld_sub
		ldr r0, =ERR
		ldr r0, [r0]
		
vld_sub:
		pop	{lr}
		bx	lr

@@@@@@@@@@@@@	MULTIPLY	@@@@@@@@@@@@@	
mul:
		push {r4, r5, lr}
		smull r4, r5, r0, r1
		mov r0, r4
		cmp r4, #0
		bge pos
	
neg:	
		cmp r5, #-1		@test for negative overflow
		beq mul_ret
		ldr r0, =ERR
		ldr r0, [r0]		
		
pos:		
		cmp r5, #0		@test for positive overflow
		beq mul_ret
		ldr r0, =ERR
		ldr r0, [r0]

mul_ret:
		pop	{r4, r5, lr}
		bx	lr

@@@@@@@@@@@@@	DIVIDE	@@@@@@@@@@@@@	
divide:
		push {lr}
		cmp r1, #0
		bne	vld_div
		ldr r0, =ERR
		ldr r0, [r0]
		bl	div_ret
		
vld_div:
		sdiv r0, r0, r1

div_ret:
		pop	{lr}
		bx	lr

@@@@@@@@@@@@@	REMAIN	@@@@@@@@@@@@@	
remain:
		push {r4, r5, lr}
		mov r4, r0		@save copy of dividend
		mov r5, r1		@save copy of divisor
		bl	divide		@quotient in r0
		mov r1, r5
		bl mul			@quotient*divisor
		mov r1, r0
		mov r0, r4
		bl sub			@dividend - (quotient*divisor)
		pop	{r4, r5, lr}
		bx	lr

@@@@@@@@@@@@@	POWER	@@@@@@@@@@@@@	
power:					@canonical recursive power function
		push {r4, lr}
		cmp r1, #0		
		bge	vld_pwr
		ldr r0, =ERR	@return error code if negative exponent
		ldr r0, [r0]
		bl	pwr_ret

vld_pwr:
		mov	r4, r0		@make copy of our N to put in stack
		cmp r1, #0		@if equal to 0, break recursion/return 1
		moveq r0, #1
		beq	pwr_ret
		
		sub	r1, r1, #1	@decrement exponent
		bl	power		@recurse
		mov	r1, r4
		bl	mul
				
pwr_ret:
		pop	{r4, lr}
		bx	lr

@@@@@@@@@@@@@	FACTORIAL	@@@@@@@@@@@@@	
factorial:				@canonical recursive factorial function
		push {r4, lr}
		cmp r0, #0		
		bge	vld_fact
		ldr r0, =ERR	@return error if negative factorial
		ldr r0, [r0]
		bl	fact_ret

vld_fact:
		mov	r4, r0			@make copy of our n to be put in stack
		cmp r0, #0
		moveq r0, #1		@if equal to 0, break recursion
		beq	fact_ret
		
		sub	r0, r0, #1		@store n-1
		bl	factorial		@recurse
		mov	r1, r4
		bl	mul
		
fact_ret:		
		pop	{r4, lr}
		bx	lr

		.data
ERR:	.word	0x80000000

		.global	search
		.global	delete
		.global	insert
		
		.text
		.balign	4

@@@@@@@@@@@@@	search	@@@@@@@@@@@@@
search:
		push 	{r4, r5, r6, r7, r8, r9, r10, r11, lr}

		mov 	r4, r2			@store copy of player**
		mov		r5, r1			@store copy of jersey number in r5
		ldr		r6, [r0, #4]	@store copy of array pointer in r6
		
		ldrh	r11, [r0, #2]	@load number of players in table to r7
		str		r6, [r4]		@store first player* in player**
			
		sub		r11, #1			@set R boundary			
		mov		r7, #0			@set L boundary	
		
binarysearch:
		cmp		r7, r11			@if L > R
		movgt	r0, #0			@then return 0
		bgt		srch_return		@value was not in table
		
		add		r8, r7, r11		@set m, gives current player	
		lsr		r8, #1
		
		mov		r9, #44			@move size of player to r9
		mul		r9, r8, r9		@player offset
		add		r10, r6, r9		@player*	
		ldrh	r1,	[r10]		@get jersey number of current player
		
		cmp		r1, r5			@compare current jersey to query
		streq	r10, [r4]		@store current player* in player**
		moveq	r0, #1			@if equal return 1
		beq		srch_return
		
left:							@if less than
		addlt	r7, r8, #1		@increment L
		addlt	r10, r10, #44	@get address of next player
		strlt	r10, [r4]		@store next player* in player**
		sublt	r10, r10, #44	@restore address to current player	
		blt		binarysearch
		
right:							@if greater than
		subgt	r11, r8, #1		@decrement R
		strgt	r10, [r4]		@store current player* in player**
		bgt		binarysearch
		
srch_return:
		pop		{r4, r5, r6, r7, r8, r9, r10, r11, lr}
		bx		lr

@@@@@@@@@@@@@	delete	@@@@@@@@@@@@@
delete:
		push 	{r4, r5, r6, r7, r8, r9, r10, lr}
		
		mov 	r4, r0			@store copy of table* in r4
		mov		r5, r1			@store copy of query in r5
		ldr		r6, [r0, #4]	@store copy of player array ptr in r6
		
		ldr		r2, =player_ptr	@load player** to register 2
		bl		search
		
		mov		r7, r2			@store copy of player** in r7
	
		cmp		r0, #0			@if search unsuccessful, return 0
		moveq	r0, #0
		beq		del_return
		
		ldr		r7, [r7]		@dereference player** to r7
		
		sub 	r8, r7, r6		@num of bytes from first player to query

		mov		r9, #44			@num of bytes per player
		sdiv	r8, r8, r9		@index of query in array
		
		ldrh	r10, [r4, #2]	@number of players in array

		sub		r10, r10, #1	@decrement number players in array
		sub		r8, r10, r8		@number players after query
		
		mov		r0, r7			@query address/address to move to
		add		r1, r7, r9		@start address of block to move
		mul		r2, r8, r9		@number of bytes to move
		
		bl		memmove			@move the block of memory
		
		strh	r10, [r4, #2]	@update number of players in table
			
		mov		r0, #1			@return 1 for success
		
del_return:		
		pop		{r4, r5, r6, r7, r8, r9, r10, lr}
		bx		lr
		
@@@@@@@@@@@@@	insert	@@@@@@@@@@@@@
insert:
		push 	{r4, r5, r6, r7, r8, r9, r10, r11, lr}
		
		ldrh	r4, [r0]		@get capacity
		ldrh 	r5, [r0, #2]	@get table count	
		cmp		r4, r5
		moveq	r0, #0
		beq		ins_return		@if capacity = count, then table is full
		
		mov 	r4, r0			@store copy of table* in r4
		mov		r5, r1			@store copy of query in r5
		mov		r6, r2			@store name pointer
		mov		r7, r3			@store games played

		ldr		r2, =player_ptr	@load player** to register 2
		bl		search
			
		cmp		r0, #1			@if search successful, return 0
		moveq	r0, #0
		beq		ins_return
		
		ldr		r0, [r4, #4]	@get address of player array
		ldr		r2, [r2]		@dereference player** to r2
		
		sub 	r8, r2, r0		@num of bytes from first player to query

		mov		r9, #44			@num of bytes per player
		sdiv	r8, r8, r9		@index of query in array
		
		ldrh	r10, [r4, #2]	@number of players in array

		sub		r8, r10, r8		@number players after query
		
		add		r0, r2, r9		@query address/address to move to
		mov		r1, r2			@start address of block to move
		mul		r2, r8, r9		@number of bytes to move
		
		mov		r9, r1			@store copy of address of inserted data 

		bl		memmove			@move the block of memory
		
		add		r10, r10, #1	@increment number of players in array
		strh	r10, [r4, #2]	@update number of players in table
		
		strh	r5, [r9]		@store jersey number

		mov		r1, #0			@initial offset for loading char
		mov		r2,	#2			@initial offset for storing char

char_loop:
		ldrb	r0, [r6, r1]	@load char
		cmp		r0, #0			@check if char is NULL and end loop
		strb	r0, [r9, r2]	@store NULL byte
		beq		end_char_loop	
		
		cmp		r1, #24			@end loop if max char number reached
		moveq	r0, #0			@move NULL to r0
		streq	r0, [r9, r2]	@store NULL terminator
		beq		end_char_loop
		
		strb	r0, [r9, r2]	@store char
		
		add		r1, r1, #1		@increment char load index
		add		r2, r2, #1		@increment char store index
		
		b	char_loop
		
end_char_loop:		
		strh	r7, [r9, #28]	@store gp
		
		ldr		r8, [sp, #36]	@load b2 from stack	
		strh	r8, [r9, #30] 	@store b2
		
		ldr		r10, [sp, #40]	@load b3 from stack	
		strh	r10, [r9, #32]	@store b3 
		
		ldr		r11, [sp, #44]	@load ft from stack	
		strh	r11, [r9, #34]	@store ft
		
		mov		r6, #3			@scale factor for b3
		lsl		r8, #1			@multiply b2 by 2
		mul		r10, r10, r6	@multiply b3 by 3
		add		r8, r8, r10		@add b2 and b3
		add		r8, r8, r11		@add ft to running sum to get pts
		strh	r8, [r9, #36]	@store pts	
		
		cmp		r7, #0			@check if played any games
		bne		non_zero_gp
		fmsr	s0, r7			@move 0 to FPU
		fsitos 	s0, s0			@convert 0 to float
		fsts	s0, [r9, #40]	@set ppg to 0.0
		mov		r0, #1			
		b		ins_return

non_zero_gp:		
		fmsr	s0, r8			@load pts into FPU
		fmsr	s1, r7			@load gp into FPU
		fsitos	s0, s0			@convert to float
		fsitos	s1, s1			@convert to float
		
		fdivs	s2, s0, s1		
		fsts	s2, [r9, #40]	@store ppg

		mov		r0, #1
		
ins_return:		
		pop		{r4, r5, r6, r7, r8, r9, r10, r11, lr}
		bx		lr

@@@@@@@@@@@@@	variables	@@@@@@@@@@@@@
		.data
		.balign	4
player_ptr:		.word	0

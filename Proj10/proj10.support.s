		.global search
		.global view
		
		.text
		.balign 4
@@@@@@@@@@@@@	Search	@@@@@@@@@@@@@
search:
		push 	{r4, r5, r6, r7, r8, r9, r10, r11, lr}

		mov 	r4, r2			@store copy of player**
		mov		r5, r1			@store copy of jersey number in r5
		ldr		r6, [r0, #4]	@store copy of array pointer in r6
		
		ldrh	r11, [r0, #2]	@load number of players in table to r7
			
		sub		r11, #1			@set R boundary			
		mov		r7, #0			@set L boundary	
		
binarysearch:
		cmp		r7, r11			@if L > R
		movgt	r0, #0			@then return 0
		bgt		endloop			@value was not in table
		
		add		r8, r7, r11		@set m, gives current player	
		lsr		r8, #1
		
		mov		r9, #44			@move size of player to r9
		mul		r9, r8, r9		@player offset
		add		r10, r6, r9		@player*	
		ldrh	r1,	[r10]		@get jersey number of current player
		
		cmp		r1, r5			@compare current jersey to query
		streq	r10, [r4]		@store player* in player**
		moveq	r0, #1			@if equal return 1
		beq		endloop
		
right:							@if less than
		addlt	r7, r8, #1		@increment L
		blt		binarysearch
		
left:							@if greater than
		subgt	r11, r8, #1		@decrement R
		bgt		binarysearch		
		
endloop:
		pop		{r4, r5, r6, r7, r8, r9, r10, r11, lr}
		bx		lr
		
@@@@@@@@@@@@@	View	@@@@@@@@@@@@@
view:
		push 	{r4, r5, r6, lr}
		mov 	r4, r0			@store copy of table address in r4
		mov		r5, r1			@store copy of query
		
		ldr		r2, =player_ptr	@load player** to register 2
		bl		search
		
		mov		r6, r2			@store copy of player**
		
		cmp		r0, #0			@if search unsuccessful, return 0
		moveq	r0, #0
		beq		return
		
		ldr		r0, =fmt		@print column headings
		bl		printf
		
		ldr		r0, =fmt1		@print column headings
		bl		printf
		
		ldr		r6, [r6]		@dereference player** to get player*
		
		ldr		r0, =fmt2
		ldrh	r1, [r6]		@get jersey number
		add		r2, r6, #2		@get player name
		ldrh	r3, [r6, #28]	@get gp
		bl		printf			
		
		ldr		r0, =fmt3
		ldrh	r1, [r6, #30]	@get b2
		ldrh	r2, [r6, #32]	@get b3
		ldrh	r3, [r6, #34]	@get ft
		bl		printf
		
		ldr		r0, =fmt4
		ldrh	r1, [r6, #36]	@get pts
		bl		printf
		
		mov		r0, #1
		
return:
		pop		{r4, r5, r6, lr}
pop:	bx		lr
		


@@@@@@@@@@@@@	strings	@@@@@@@@@@@@@
fmt:	.ascii	"Player	number and name         "
		.asciz	"GP   B2   B3   FT  PTS   PPG\n"
fmt1:
		.ascii	"-----------------------------  "
		.asciz	"---  ---  ---  ---  ---  ----\n"
		
fmt2:	.asciz	"%2d  %-25s  %3d"

fmt3:	.asciz	"  %3d  %3d  %3d"
		
fmt4:	.asciz	"  %3d   N/A\n"


		
@@@@@@@@@@@@@	vars	@@@@@@@@@@@@@		
		.data
		.balign 4		
player_ptr:	.word		0		
			



		.global main
		.global	incrmnt_var
		
		.text
main:
		push	{lr}

readin:	bl		getchar			@ main loop to read input
		mov		r5, r0			@ move to non parameter register
		cmp		r5, #-1			@ check if EOF 
		beq		end				@ branch to end
		bl		putchar
		
total:		
		ldr		r0, =tot		@ load address of total to r0
		bl		incrmnt_var		@ increment total

upper:		
		cmp		r5, #'A'
		blt		decimal			@ if less than, it can't be lowercase
		cmp		r5, #'Z'
		bgt		lower			@ check for lowercase
			
		ldr		r0, =up
		bl		incrmnt_var
		
lower:
		cmp		r5, #'a'
		blt		decimal			
		cmp		r5, #'z'
		bgt		control			@ if greater than, may be DEL
		
		ldr		r0, =low
		bl		incrmnt_var
		
decimal:
		cmp		r5, #'0'
		blt		newline		
		cmp		r5, #'9'
		bgt		hexidecimal		@ if greater than, may be hex

		ldr		r0, =dec
		bl		incrmnt_var
		
		ldr		r0, =hex		@ if dec then is hex	
		bl		incrmnt_var		
		
hexidecimal:
		cmp		r5, #'A'
		blt		newline		
		cmp		r5, #'f'
		bgt		control		@ if greater than, may be DEL
		cmp		r5, #'F'		
		ble		ishex
		cmp		r5, #'a'
		blt		newline
		
ishex:		
		ldr		r0, =hex
		bl		incrmnt_var
		
newline:
		cmp		r5, #'\n'
		bne		whitespace			
		
		ldr		r0, =new
		bl		incrmnt_var
		
		ldr		r0, =wht		@ if is newline, is whitespace
		bl		incrmnt_var
		
		
whitespace:
		
		cmp		r5, #' '		@ space check
		beq		iswhite
		cmp		r5, #'	'		@ tab check
		bne		control
		
iswhite:
		ldr		r0, =wht
		bl		incrmnt_var
		
control:
		cmp		r5, #0x7F
		beq		iscntrl
		cmp		r5, #0x1F
		bgt		toreadin

iscntrl:
		ldr		r0, =ctrl
		bl		incrmnt_var
		
toreadin:
		bl		readin			@ loop back and read another char

end:	ldr		r0, =fmt1		@ end of program. print counts
		ldr		r1, =tot		@ load and print total
		ldr		r1, [r1]
		bl		printf
		
		ldr		r0, =fmt2		@ load and print upper
		ldr		r1, =up		
		ldr		r1, [r1]
		bl		printf
		
		ldr		r0, =fmt3		@ load and print lower
		ldr		r1, =low	
		ldr		r1, [r1]
		bl		printf
		
		ldr		r0, =fmt4		@ load and print decimals
		ldr		r1, =dec		
		ldr		r1, [r1]
		bl		printf
		
		ldr		r0, =fmt5		@ load and print hexidecimals
		ldr		r1, =hex		
		ldr		r1, [r1]
		bl		printf
		
		ldr		r0, =fmt6		@ load and print newlines
		ldr		r1, =new		
		ldr		r1, [r1]
		bl		printf
		
		ldr		r0, =fmt7		@ load and print whitespace
		ldr		r1, =wht		
		ldr		r1, [r1]
		bl		printf
		
		ldr		r0, =fmt8		@ load and print control
		ldr		r1, =ctrl		
		ldr		r1, [r1]
		bl		printf
		
		pop		{lr}
		bx		lr

incrmnt_var:					@ helper function to incriment var
								@ takes a pointer to var in r0
		push	{r0, r1, lr}
		
		mov		r1, r0
		ldr		r0, [r1]
		add		r0, r0, #1
		str		r0, [r1]
		
		pop		{r0, r1, lr}
		bx		lr


		.data
tot:	.word	0
up:		.word	0
low:	.word	0
dec:	.word	0
hex:	.word	0
new:	.word	0
wht:	.word	0
ctrl:	.word	0

fmt1:
		.asciz	"\nTotal number of characters: %d\n"
		
fmt2:		
		.ascii	"\nNumber of upper case letters (in the set {A-Z}): "
		.asciz	"%d\n"
		
fmt3:		
		.ascii	"\nNumber of lower case letters (in the set {a-z}): "
		.asciz	"%d\n"
				
fmt4:		
		.asciz	"\nNumber of decimal digits (in the set {0-9}): %d\n"
		
fmt5:		
		.ascii	"\nNumber of hexadecimal digits (in the set {0-9, A-F," 
		.asciz	"a-f}): %d\n"
		
fmt6:		
		.asciz	"\nNumber of newline characters: %d\n"
		
fmt7:		
		.ascii	"\nNumber of whitespace characters (blanks, tabs and "
		.asciz	"newlines): %d\n"
		
fmt8:		
		.ascii	"\nNumber of control characters (0x00 to 0x1F, 0x7F): "
		.asciz	"%d\n"


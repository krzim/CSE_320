label:
		beq		label
		bne		label
		bcs		label
		bcc		label
		bmi		label
		bpl		label
		bvs		label
		bvc		label
		bhi		label
		bls		label
		bge		label
		blt		label
		bgt		label
		ble		label
		b		label
		b		ahead
		b		far
		add		r0, r1
ahead:
		ldr		r0, [r1]
		mov		r0, r1
		moveq	r0, r1
far:
		ldreq	r0, [r1]

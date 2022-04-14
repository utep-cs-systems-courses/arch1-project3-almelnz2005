	.balign 2
	.text
	.global switch_interrupt_handler
	.extern switch_update_interrupt_sense
	.extern switches
	
	;.data not needed since we are not using any new variabl
switch_interrupt_handler:
	call #switch_update_interrupt_sense
	xor.b #255, r12 		;#255 = 0xff, r12 is p2val
	and.b #15, r12			;p2val & SWITCHES. SWITCHES -> 0000 1111, since we are only
	;using ther first four switches
	mov.b r12, &switches
	pop r0

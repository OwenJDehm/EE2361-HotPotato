.include "xc.inc"

.text                       ;BP (put the following data in ROM(program memory))

; This is a library, thus it can *not* contain a _main function: the C file will
; define main().  However, we will need a .global statement to make available ASM
; functions to C code.
; All functions utilized outside of this file will need to have a leading 
; underscore (_) and be included in a comment delimited list below.
.global _write_0, _write_1, _delay_100micro, _delay_1milli

    _delay_100micro:
	repeat #1593
	nop
	return

    _delay_1milli:
	repeat #15993
	nop
	return

    _write_0:
	inc LATA
	repeat #3
	nop
	clr LATA
	repeat #4
	nop
	return
	
    _write_1:
	inc LATA
	repeat #6
	nop
	clr LATA
	repeat #3
	nop
	return
	
    
    bset LATA, #0
    
	
    





;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 4.0.0 #11528 (Linux)
;--------------------------------------------------------
	.module ai_program
	.optsdcc -mz80
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _main
	.globl _puts
	.globl _printf
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _DATA
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _INITIALIZED
;--------------------------------------------------------
; absolute external ram data
;--------------------------------------------------------
	.area _DABS (ABS)
;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
	.area _HOME
	.area _GSINIT
	.area _GSFINAL
	.area _GSINIT
;--------------------------------------------------------
; Home
;--------------------------------------------------------
	.area _HOME
	.area _HOME
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area _CODE
;ai-program.c:3: int main(void) {
;	---------------------------------
; Function main
; ---------------------------------
_main::
	push	ix
	ld	ix,#0
	add	ix,sp
	push	af
;ai-program.c:4: int n1 = 0, n2 = 1, next;
	ld	bc, #0x0000
	ld	de, #0x0001
;ai-program.c:7: printf("Fibonacci sequence:\n");
	push	bc
	push	de
	ld	hl, #___str_1
	push	hl
	call	_puts
	pop	af
	pop	de
	pop	bc
;ai-program.c:9: for (int i = 0; i < count; i++) {
	ld	hl, #0x0000
00103$:
	ld	a, l
	sub	a, #0x0a
	ld	a, h
	rla
	ccf
	rra
	sbc	a, #0x80
	jr	NC,00101$
;ai-program.c:10: printf("%d ", n1);
	push	hl
	push	bc
	push	de
	push	bc
	ld	hl, #___str_2
	push	hl
	call	_printf
	pop	af
	pop	af
	pop	de
	pop	bc
	pop	hl
;ai-program.c:11: next = n1 + n2;
	ld	a, c
	add	a, e
	ld	c, a
	ld	a, b
	adc	a, d
	ld	b, a
	inc	sp
	inc	sp
	push	bc
;ai-program.c:12: n1 = n2;
	ld	c, e
	ld	b, d
;ai-program.c:13: n2 = next;
	pop	de
	push	de
;ai-program.c:9: for (int i = 0; i < count; i++) {
	inc	hl
	jr	00103$
00101$:
;ai-program.c:16: printf("\n");
	ld	hl, #___str_4
	push	hl
	call	_puts
	pop	af
;ai-program.c:17: return 0;
	ld	hl, #0x0000
;ai-program.c:18: }
	ld	sp, ix
	pop	ix
	ret
___str_1:
	.ascii "Fibonacci sequence:"
	.db 0x00
___str_2:
	.ascii "%d "
	.db 0x00
___str_4:
	.db 0x00
	.area _CODE
	.area _INITIALIZER
	.area _CABS (ABS)

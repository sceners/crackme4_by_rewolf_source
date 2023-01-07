;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�
; push  length
; push  lpString
; call  _dec2int
;
; procedura konwertuje wartosc dec zapisana w string'u na dword'a w eax
; (wielkosc znakow dowolna)
;
; na wejsciu:
; length   - dlugosc lancucha
; lpString - offset stringa z liczba dec
;
; na wyjsciu:
; eax - przekonwertowany DWORD
;
; modyfikowane rejestry:
; eax
;
; Autor : ReWolf^HTB (rewolf@poczta.onet.pl)
;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�

_dec2int proc
	push	ebx
	push	ecx
	push	edi
	push	edx
	add	esp,14h
	pop	edi
	pop	ecx
	xor	eax,eax
	xor	ebx,ebx
	push	10d
_d2i_1:	mul	dword ptr [esp]
	mov	bl,byte ptr [edi]
	sub	bl,30h
	add	al,bl
	inc	edi
	inc	bh
	cmp     bh,cl
	jne	_d2i_1
	sub	esp,18h
	pop	edx
	pop	edi
	pop	ecx
	pop	ebx
	ret	8
_dec2int endp

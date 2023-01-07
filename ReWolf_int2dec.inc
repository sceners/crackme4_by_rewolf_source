;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�
; push dword
; push offset bufor
; call _int2dec
; 
; procdure konwertuje wartosc DWORD na lancuch decymalny
;
; na wejsciu:
; dword - wartosc, ktora ma zostac przekonwertowana
; bufor - bufor, w ktorym zostanie zwrocony przekonwertowany string.
;         bufor musi miec 11 bajtow, zera na poczatku sa obcinane,
;         string jest zakonczony zerem
;
; na wyjsciu:
; brak
;
; modyfikowane rejestry:
; brak
;
; Autor : ReWolf^HTB (rewolf@poczta.onet.pl)
;컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�

_int2dec proc
        push	eax
        push	ebx
        push	ecx
        push	edx
        push	edi
        mov	eax,dword ptr [esp+1Ch]
        mov	edi,dword ptr [esp+18h]
        mov	byte ptr [edi+10d],0
        xor	ecx,ecx
        mov	cl,10d
        xor	ebx,ebx
_i2d_1:	xor	edx,edx
	div	ecx
	add	dl,30h
	mov	byte ptr [edi+9],dl
	dec	edi
	inc	ebx
	cmp	bl,10d
	jne	_i2d_1
	xor	ecx,ecx
	dec	ecx
	mov	al,30h
	mov	edi,dword ptr [esp+18h]
	repz	scasb
_i2d_2:	mov	bl,byte ptr [edi-1]
	mov	byte ptr [edi+ecx+1],bl
	inc	edi
	test	bl,bl
	jne	_i2d_2
	pop	edi
	pop	edx
	pop	ecx
	pop	ebx
	pop	eax
	ret	8
_int2dec endp

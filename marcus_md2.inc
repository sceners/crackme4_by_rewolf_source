comment ~

 ############
 # Hash MD2 #
 ############

 push offset _hash
 push _length_string
 push offset _string
 call _MD2

 _hash                  - wynik hashu w hex - dl. 128 bitow
 _length_string         - dlugosc stringa
 _string                - string do hashowania

 Marcus // HTBTeam (o6.o7.2oo4)
 www.marcushp.prv.pl

~

.486

.data
byte_10001157	db 29h
		dd 0A2C9432Eh, 3D017CD8h, 0ECA15436h, 621306F0h, 0C0F305A7h
		dd 988C73C7h, 0BCD92B93h, 1ECA824Ch, 0FD3C579Bh, 6716E0D4h
		dd 8A186F42h, 0BE12E517h, 0DAD6C44Eh, 0A049DE9Eh, 0BB8EF5FBh
		dd 0A97AEE2Fh, 15917968h, 943F07B2h, 0B8910C2h,	80215F22h
		dd 5A9A5D7Fh, 35273290h, 0BFE7CC3Eh, 0FF0397F7h, 48B33019h
		dd 0D7D1B5A5h, 0AC2A925Eh, 4FC6AA56h, 96D238B8h, 76B67DA4h
		dd 9CE26BFCh, 45F10474h, 6459709Dh, 86208771h, 0E665CF5Bh
		dd 1B02A82Dh, 0AEAD2560h, 1CF6B9B0h, 34696146h,	550F7E40h
		dd 0DD23A347h, 0C33AAF51h, 0BACEF95Ch, 2C26EAC5h, 856E0D53h
		dd 0D3098428h, 41F4CDDFh, 6A524D81h, 6CC837DCh,	24FAABC1h
		dd 0C087BE1h, 784AB1BDh, 0E38B9588h, 0E96DE863h, 3BFED5CBh
		dd 0F2391D00h, 660EB7EFh, 0A6E4D058h, 0EBF87277h, 310A4B75h
		dd 8FB45044h, 0DB1A1FEDh, 9F338D99h
		db 11h,	83h, 14h
dword_10003000	dd 0
dword_10003004	dd 0
dword_10003008	dd 0
dword_1000300C	dd 0
dword_10003010	dd 0
dword_10003014	dd 0
dword_10003018	dd 0
dword_1000301C	dd 0
dword_10003020	dd 0
dword_10003024	dd 0
dword_10003028	dd 0
dword_1000302C	dd 0
byte_10003030	db 0
		dd 3 dup(0)
		db 2 dup(0)
byte_1000303F	db 0
byte_10003040	db 0
		;align 10h
		x db 16 DUP (0)
dword_10003050	dd 0
byte_10003054	db 0
		align 4

.code
mmd2code dd 'MMD2' xor 12345678h
mmd2size dd mmd2end-mmd2size-4
_MD2 proc
comment ~
arg_8		= dword	ptr  8
arg_4		= dword	ptr  0Ch
arg_0		= dword	ptr  10h



		push	ebp
		mov	ebp, esp
		pusha
		xor	eax, eax
		mov	ds:dword_10003000, eax
		mov	ds:dword_10003004, eax
		mov	ds:dword_10003008, eax
		mov	ds:dword_1000300C, eax
		mov	ds:byte_10003054, 2
		mov	ecx, [ebp+arg_4]
		mov	esi, [ebp+arg_8]
		shr	ecx, 4
		jz	loc_100010F5
		mov	ds:dword_10003050, ecx
		xor	eax, eax
		mov	esi, [ebp+arg_8]

loc_1000104B:
		mov	eax, [esi]
		mov	edx, [esi+4]
		mov	ds:dword_10003010, eax
		mov	ds:dword_10003014, edx
		xor	eax, ds:dword_10003000
		xor	edx, ds:dword_10003004
		mov	ds:dword_10003020, eax
		mov	ds:dword_10003024, edx
		mov	eax, [esi+8]
		mov	edx, [esi+0Ch]
		mov	ds:dword_10003018, eax
		mov	ds:dword_1000301C, edx
		xor	eax, ds:dword_10003008
		xor	edx, ds:dword_1000300C
		mov	ds:dword_10003028, eax
		mov	ds:dword_1000302C, edx
		xor	ebx, ebx
		xor	edx, edx

loc_1000109E:
		mov	ecx, 0FFFFFFD0h

loc_100010A3:
		mov	bl, ds:byte_10001157[ebx]
		xor	bl, ds:byte_10003030[ecx]
		mov	ds:byte_10003030[ecx], bl
		inc	ecx
		jnz	short loc_100010A3
		add	bl, dl
		inc	dl
		cmp	dl, 12h
		jnz	short loc_1000109E
		mov	ecx, 0FFFFFFF0h
		movzx	eax, ds:byte_1000303F

loc_100010CD:
		xor	al, [ecx+esi+10h]
		mov	al, ds:byte_10001157[eax]
		xor	al, ds:byte_10003040[ecx]
		mov	ds:byte_10003040[ecx], al
		inc	ecx
		jnz	short loc_100010CD
		add	esi, 10h
		dec	ds:dword_10003050
		jnz	loc_1000104B

loc_100010F5:
		inc	ds:dword_10003050
		dec	ds:byte_10003054
		jz	short loc_1000112E
		js	short loc_10001138
		mov	ecx, [ebp+arg_4]
		mov	edx, 10h
		and	ecx, 0Fh
		sub	edx, ecx
		test	ecx, ecx
		mov	al, dl
		cld
		mov	edi, offset byte_10003040
		jz	short loc_10001120
		rep movsb

loc_10001120:
		mov	ecx, edx
		rep stosb
		mov	esi, offset byte_10003040
		jmp	loc_1000104B

loc_1000112E:
		mov	esi, offset byte_10003030
		jmp	loc_1000104B

loc_10001138:
		mov	edi, [ebp+arg_0]
		mov	esi, offset dword_10003000
		push	esi
		mov	ecx, 4
		rep movsd
		pop	edi
		mov	ecx, 16h
		xor	eax, eax
		rep stosd
		popa
		leave
		retn	0Ch
		~
		;comment ~
db 31,153,149,63,121,210,218,95,59,82,121,252,78,99,57,95
db 233,26,8,31,74,177,117,46,10,18,191,90,31,99,57,95
db 72,153,52,83,193,103,113,158,163,22,118,219,255,18,121,95
db 195,31,40,46,10,18,74,159,193,103,113,212,76,153,47,91
db 233,2,8,31,74,155,108,75,59,82,121,108,79,18,8,31
db 74,33,108,91,59,82,121,252,106,99,57,95,195,7,93,46
db 10,18,242,25,66,153,47,83,233,10,8,31,74,155,108,67
db 59,82,121,108,79,26,8,31,74,33,108,83,59,82,121,252
db 98,99,57,95,195,7,85,46,10,18,74,132,121,192,192,143
db 181,237,134,213,209,18,9,31,74,32,224,111,59,82,121,215
db 211,34,8,31,74,83,12,180,72,200,135,157,202,232,107,42
db 151,171,137,160,181,237,118,233,79,45,8,31,74,32,61,81
db 90,152,249,95,58,82,121,109,203,82,8,31,74,154,248,31
db 59,82,121,30,63,245,250,153,90,237,116,14,59,82,121,80
db 207,68,134,160,181,237,124,14,59,82,121,161,71,71,8,31
db 74,102,82,39,121,153,52,83,240,2,121,95,74,145,152,80
db 97,195,252,150,192,208,133,224,10,99,57,95,62,16,138,251
db 193,216,138,245,244,82,8,31,74,251,100,160,181,237,199,111
db 59,82,121,182,89,237,134,160,193,111,105,225,74,99,57,95
db 28,171,125,95,74,18,138,250,21,171,111,95,74,18,74,159
db 185,185,24,150,136,30,121
;~
_MD2 endp
mmd2end equ $

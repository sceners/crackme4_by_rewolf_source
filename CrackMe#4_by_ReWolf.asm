.386
.model flat, stdcall
option casemap:none

include \masm32\include\windows.inc
include \masm32\include\kernel32.inc
include \masm32\include\user32.inc
include \masm32\include\gdi32.inc
includelib \masm32\lib\kernel32
includelib \masm32\lib\user32
includelib \masm32\lib\gdi32


include \masm32\include\mfmPlayer.inc
includelib \masm32\lib\mfmPlayer.lib


include marcus_md2.inc
include marcus_md5.inc

include about_dlg.inc

ID_ABOUT = 1004
ID_EXIT = 1005
ID_CHECK = 1006

ID_EDIT_SERIAL = 1003
ID_EDIT_NAME = 1002


WM_RW_GETTEXT = WM_USER+85

;.const

.data
	music_start dd offset music_end - music_start -4
	include music_xm.inc
	music_end equ $

	;strName db 'ReWolf^HTB',0

	strScrollText db '..::..Hard.To.Beat.Cracking.Team.presents.CrackMe.#4.by.ReWolf..::..cOde:.ReWolf..gFx:.ReWolf..sFx:.ghidorah..::..',0
	strWindowText db 'CrackMe #4 by ReWolf^HTB',0

	;strWinText  db 'CRACKME#4_BY_REWOLF spowodowa³ b³¹d: nieprawid³owa strona w',0Dh,0Ah
                   ;db 'module CRACKME#4_BY_REWOLF.EXE przy 017f:0040129A.',0Dh,0Ah,0Dh,0Ah
                   ;db 'No wreszcie poprawny serial, teraz machnij keygen i wyœlij go do mnie:',0Dh,0Ah
                   ;db ' - rewolf@poczta.onet.pl',0Dh,0Ah
                   ;db 'a jeszcze jak by ci siê chcia³o to tutorial równie¿ mile widziany',0
	strWinText	db 67,83,67,64,79,72,67,36,60,86,72,82,83,95,75,88
		db 79,77,68,35,119,117,105,112,103,109,101,124,109,190,46,109
		db 179,184,102,57,36,107,111,98,120,123,107,124,101,105,189,96
		db 119,96,34,112,112,119,105,105,105,41,125,6,6,96,97,107
		db 117,109,103,35,71,87,71,68,67,68,79,40,56,82,76,86
		db 95,83,71,84,75,73,64,41,77,81,79,43,124,127,116,118
		db 32,49,51,52,98,63,54,55,60,57,59,57,53,76,32,2
		db 10,12,8,77,107,37,113,117,109,122,112,104,101,104,46,127
		db 111,113,112,98,115,107,127,39,123,108,120,98,109,97,34,47
		db 116,100,112,98,126,37,107,102,107,97,100,98,102,45,101,106
		db 121,102,103,109,36,108,38,112,113,149,102,98,102,45,105,96
		db 32,101,109,35,105,107,111,98,50,4,2Ah,43,33,45,124,106
		db 119,110,110,101,68,117,105,100,114,125,107,37,99,99,107,123
		db 46,113,110,14,14,100,38,109,109,122,112,104,118,104,46,101
		db 97,106,34,97,125,37,101,110,40,122,99,225,44,110,102,108
		db 105,96,177,108,36,113,105,39,124,124,126,100,126,100,111,99
		db 32,115,241,116,106,108,99,184,40,100,99,103,105,45,121,102
		db 100,123,107,98,106,124,0

	nmRect RECT <21,148,280,161>
	srRect RECT <21,184,280,202>

	id_bitmap db 'BG',0

	vert_sum db 28,92,156,220
	horz_sum db 48,52,56,60,64,68,72,76

.data?
	hashMD2 db 16 DUP (?)
	hashMD5 db 16 DUP (?)
	longHashMD5 db 32 DUP (?)
	longHashMD2 db 32 DUP (?)
	tmpTab db 32 DUP (?)
	tmpTab2 db 32 DUP (?)
	zlozenieMD5MD2 db 32 DUP (?)
	binarySerial db 32 DUP (?)
        ;---------------------
	hBoldFont dd ?
	sctBoldFnt LOGFONT <?>

	DialogHandle dd ?
	OldEditProc dd ?

	thPaintRun db ?
	dwPaintThID dd ?
	;---------------------
	strNameBuffer db 256 DUP (?)
	strSerialBuffer db 256 DUP (?)
	;-------------------------
	_SendDlgItemMessage dd ?
	_strlen dd ?

	permintFlag db ?


.code
;include \masm32\rewolf\rewolf_strlen.inc
include \masm32\rewolf\rewolf_zeromemory.inc
include \masm32\rewolf\rewolf_dec2int.inc

elimcode dd 'ELIM' xor 12345678h
elimsize dd elimend-elimsize-4
Eliminate proc lpHT:DWORD

	comment ~
	pushad
	push	64
	push	offset tmpTab
	call	_zeromemory

	mov	edx,lpHT

	xor	ebx,ebx
_e1:
	movzx	eax,byte ptr [edx+ebx]
	cmp	byte ptr [tmpTab+eax],1
	je	_e2
	mov	byte ptr [tmpTab+eax],1
	jmp	_e3
_e2:
	mov	byte ptr [tmpTab2+ebx],1
_e3:
	inc	ebx
	cmp	ebx,32
	jne	_e1

	cld
_e4:
	mov	esi,offset tmpTab
	mov	edi,offset tmpTab2
	mov	ecx,32

	mov	al,1
	repne	scasb
	jne	_e5
	dec	edi
	mov	byte ptr [edi],0
	sub	edi,offset tmpTab2
	xchg	edi,esi

	mov	ecx,32
	xor	al,al
	repne	scasb
	dec	edi
	mov	byte ptr [edi],1
	sub	edi,offset tmpTab
	mov	eax,edi

	mov	byte ptr [edx+esi],al
	jmp	_e4
_e5:
	popad
	ret	4
	~
;--------------
;comment ~
db 96,148,148,55,95,95,16,175,148,93,120,191,173,224,135,168
db 190,74,112,100,238,16,206,83,38,159,192,175,148,93,120,86
db 65,22,190,215,205,190,58,87,52,244,127,145,182,7,218,21
db 53,30,59,212,206,63,13,138,201,161,128,246,119,31,199,79
db 151,93,120,238,21,31,120,87,133,30,138,249,64,57,55,145
db 50,31,249,184,45,189,58,87,178,225,193,119,53,31,120,101
db 245,237,214,24,243,24,121,214,218,231,217,21,53,148,191,223
db 49,9,147,146,84,214,186,83,53
;~
;--------------

Eliminate endp
elimend equ $

zlzcode dd 'ZLOZ' xor 0FEDCBA98h
zlzsize dd zlzend-zlzsize-4
Zlozenie proc lpDest,lpSrc1,lpSrc2:DWORD
;Src1*Src2
	comment ~
	pushad

	mov	esi,lpSrc2
	mov	edi,lpDest
	mov	edx,lpSrc1
	xor	ecx,ecx
_nb:
	movzx	eax,byte ptr [esi+ecx]
	mov	bl,byte ptr [edx+eax]
	mov	byte ptr [edi+ecx],bl
	inc	ecx
	cmp	ecx,32
	jne	_nb

	popad
	ret
	~
;comment ~
db 151,126,124,196,73,128,128,47,191,253,27,241,206,198,89,171
db 116,241,161,46,222,229,24,184,251,180,19,93,226,128,96,197
db 11,55,156,164
;~
Zlozenie endp
zlzend equ $

mdhcode dd 'MODH' xor 87654321h
mdhsize dd mdhend-mdhsize-4
ModHash proc lpHT:DWORD

	comment ~
	pushad
        mov	esi,lpHT
	xor	ebx,ebx
	mov	ecx,32
_mh1:
	movzx	eax,byte ptr [esi+ebx]
	cdq
	div	ecx
	mov	byte ptr [esi+ebx],dl
	inc	ebx
	cmp	ebx,32
	jne	_mh1

	popad
	ret	4
	~
;comment ~
        DB 03Ch                                    ;  CHAR '<'
        DB 08Ch
        DB 0C6h
        DB 0AAh
        DB 0E2h
        DB 072h                                    ;  CHAR 'r'
        DB 022h                                    ;  CHAR '"'
        DB 0F9h
        DB 0B2h
        DB 0BEh
        DB 00Ah
        DB 0CAh
        DB 069h                                    ;  CHAR 'i'
        DB 007h
        DB 025h                                    ;  CHAR '%'
        DB 07Ch                                    ;  CHAR '|'
        DB 06Dh                                    ;  CHAR 'm'
        DB 034h                                    ;  CHAR '4'
        DB 0B3h
        DB 03Dh                                    ;  CHAR '='
        DB 098h
        DB 08Fh
        DB 03Eh                                    ;  CHAR '>'
        DB 0F9h
        DB 02Ah                                    ;  CHAR '*'
        DB 084h
        DB 0D1h
        DB 0EAh
        DB 01Ch
        DB 0F7h
        DB 04Bh                                    ;  CHAR 'K'
        DB 003h
        DB 0ABh
        DB 003h
        DB 02Ah                                    ;  CHAR '*'
;~
ModHash endp
mdhend equ $

pricode dd 'PEIN' xor 12345678h
prisize dd priend-prisize-4
PermIntegrity proc lpPMT:DWORD
	comment ~

	pushad

	push	32
	push	offset tmpTab
	call	_zeromemory

	mov	edi,offset tmpTab
	mov	esi,lpPMT
	xor	ecx,ecx
_npi:
	movzx	eax,byte ptr [esi+ecx]
	cmp	eax,31
	ja	_end_not
	mov	byte ptr [edi+eax],1
	inc	ecx
	cmp	ecx,32
	jne	_npi

	xor	eax,eax
	dec	edi
_npi2:
	add	al,byte ptr [edi+ecx]
	loop	_npi2
	cmp	eax,32
	je	_end_true


_end_not:
	mov	permintFlag,0
	jmp	_end
_end_true:
	mov	permintFlag,1
_end:
	popad
	ret
	~
db 99,148,157,34,92,63,25,186,151,93,113,170,246,225,142,189
db 137,231,208,0,54,148,4,74,5,214,126,244,50,46,242,186
db 41,104,102,132,50,39,112,3,181,230,81,55,219,44,177,13
db 52,27,72,160,205,156,137,98,66,22,183,71,251,187,51,66
db 54,244,118,132,51,210,213,0,54,30,16,139,244,27,113
PermIntegrity endp
priend equ $

chsecode dd 'CHSE' xor 0ABCDEF12h
chsesize dd chseend-chsesize-4
CheckSerial proc

	comment ~
	pushad

	push	offset hashMD2

	push	offset strNameBuffer
	call	_strlen

	push	eax
	push	offset strNameBuffer
	;call	_MD2
	push	offset _MD2
	call	DecodeAndCall

	push	offset longHashMD5
	push	8
	push	offset hashMD2
	;call	_MD5
	push	offset _MD5
	call	DecodeAndCall

	push	offset longHashMD5+16
	push	8
	push	offset hashMD2+8
	;call	_MD5
	push	offset _MD5
	call	DecodeAndCall


	push	offset hashMD5

	push	offset strNameBuffer
	call	_strlen

	push	eax
	push	offset strNameBuffer
	;call	_MD5
	push	offset _MD5
	call	DecodeAndCall

	push	offset longHashMD2
	push	8
	push	offset hashMD5
	;call	_MD2
	push	offset _MD2
	call	DecodeAndCall

	push	offset longHashMD2+16
	push	8
	push	offset hashMD5+8
	;call	_MD2
	push	offset _MD2
	call	DecodeAndCall



	push	offset longHashMD5
	;call	ModHash
	push	offset ModHash
	call	DecodeAndCall

	push	offset longHashMD2
	;call	ModHash
	push	offset ModHash
	call	DecodeAndCall

	push	offset longHashMD5
	;call	Eliminate
	push	offset Eliminate
	call	DecodeAndCall

	push	offset longHashMD2
	;call	Eliminate
	push	offset Eliminate
	call	DecodeAndCall


	push	offset longHashMD2
	push	offset longHashMD5
	push	offset zlozenieMD5MD2
	push	offset Zlozenie
	call	DecodeAndCall

	push	offset strSerialBuffer
	call	_strlen

	ror	eax,3
	add	eax,0BADC0DEh
	xor	eax,98765432h
	sub	eax,0DEADBEEFh
	ror	eax,3

	cmp	eax,0B6A5BABCh
	jne	_end

	mov	esi,offset strSerialBuffer
	mov	edi,offset binarySerial
	xor	ecx,ecx
_npb:
        push	2
        push	esi
	call	_dec2int

	mov	byte ptr [edi+ecx],al

	inc	ecx
	add	esi,2
	cmp	ecx,32
	jne	_npb

	push	offset binarySerial
	push	offset PermIntegrity
	call	DecodeAndCall

	cmp	permintFlag,1
	jne	_end

	push	64
	push	offset tmpTab
	call	_zeromemory

	push	offset longHashMD5
	push	offset binarySerial
	push	offset tmpTab
	push	offset Zlozenie
	call	DecodeAndCall


	push	offset zlozenieMD5MD2
	push	offset tmpTab
	push	offset tmpTab2
	push	offset Zlozenie
	call	DecodeAndCall


	mov	edi,offset tmpTab2
	xor	edx,edx

_nsb:
	xor	ecx,ecx
	xor	eax,eax
_ns:
	movzx	ebx,byte ptr [edi+ecx]
	add	eax,ebx
	inc	ecx
	cmp	ecx,8
	jne	_ns
        movzx	ecx,byte ptr [vert_sum+edx]
        cmp	eax,ecx
        jne	_end
        add	edi,8
        inc	edx
        cmp	edx,4
        jne	_nsb


	mov	edi,offset tmpTab2
	xor	edx,edx
_nsh:
	xor	ecx,ecx
	xor	eax,eax
_nh:
	movzx	ebx,byte ptr [edi+8*ecx]
	add	eax,ebx
	inc	ecx
	cmp	ecx,4
	jne	_nh
        movzx	ecx,byte ptr [horz_sum+edx]
        cmp	eax,ecx
        jne	_end
        inc	edi
        inc	edx
        cmp	edx,8
        jne	_nsh

	cmp	byte ptr [tmpTab2],0
	jne	_end
	cmp	byte ptr [tmpTab2+6],6
	jne	_end
	cmp	byte ptr [tmpTab2+9],9
	jne	_end
	cmp	byte ptr [tmpTab2+13],13
	jne	_end
	cmp	byte ptr [tmpTab2+15],15
	jne	_end
	cmp	byte ptr [tmpTab2+18],18
	jne	_end
	cmp	byte ptr [tmpTab2+20],20
	jne	_end
	cmp	byte ptr [tmpTab2+27],27
	jne	_end

	push	offset tmpTab2
	push	offset strWinText
	push	offset encode_msg
	call	DecodeAndCall

	push	MB_ICONERROR
	push	offset strWindowText
	push	offset strWinText
	push	DialogHandle
	call	MessageBox

	push	offset tmpTab2
	push	offset strWinText
	push	offset encode_msg
	call	DecodeAndCall

_end:
	popad
	ret
	~
	;comment ~
db 55,212,29,73,21,188,237,45,245,254,133,23,66,117,33,170
db 87,236,237,45,245,254,133,128,95,172,197,232,191,235,135,232
db 87,212,61,73,21,188,239,224,63,36,36,170,87,212,210,249
db 23,188,109,169,85,188,133,128,159,29,199,232,61,180,237,72
db 246,254,133,128,0,173,197,232,191,151,135,232,87,212,45,73
db 21,188,237,45,245,254,133,23,66,117,33,170,87,236,237,45
db 245,254,133,128,0,173,197,232,191,183,135,232,87,212,93,73
db 21,188,239,224,63,20,36,170,87,212,141,248,23,188,109,29
db 86,188,133,128,191,29,199,232,61,180,237,88,246,254,133,128
db 95,172,197,232,191,99,132,232,87,212,61,73,21,188,237,207
db 73,252,133,0,135,189,133,232,63,100,36,170,87,212,162,246
db 23,188,109,41,86,188,133,128,239,29,199,232,63,198,152,168
db 87,84,55,233,87,188,237,48,246,254,133,128,45,161,197,232
db 191,31,132,232,87,212,93,73,21,188,237,80,246,254,133,128
db 111,30,199,232,63,71,152,168,87,84,15,233,87,188,237,45
db 244,254,133,23,66,117,33,170,87,125,77,235,82,98,69,69
db 92,137,183,188,33,36,168,7,233,17,91,41,159,191,184,84
db 237,25,51,231,210,225,132,232,87,2,64,75,21,188,58,176
db 245,254,133,219,158,214,135,190,191,206,120,23,168,52,129,209
db 22,63,67,234,212,69,165,157,187,212,221,74,21,188,237,186
db 73,252,133,0,103,189,133,232,215,129,72,76,21,188,132,231
db 210,157,132,232,87,214,197,128,175,29,199,232,191,164,120,23
db 168,212,61,73,21,188,237,176,245,254,133,128,175,29,199,232
db 63,71,152,168,87,84,123,232,87,188,237,208,245,254,133,128
db 175,29,199,232,63,164,39,170,87,212,126,245,23,188,109,13
db 87,188,133,87,79,30,199,232,100,110,182,33,100,124,138,94
db 75,133,134,43,22,63,124,224,34,72,138,94,221,230,37,170
db 87,135,68,231,210,1,133,232,87,63,66,224,21,63,127,236
db 34,100,58,240,245,254,133,219,133,143,76,219,151,179,51,244
db 152,191,70,169,212,69,129,157,163,179,51,98,9,28,199,232
db 108,125,138,109,217,188,133,232,16,254,6,18,95,201,95,104
db 106,164,39,170,87,188,240,150,215,129,155,74,21,188,131,157
db 34,60,184,201,245,254,133,225,34,208,5,213,114,30,199,232
db 90,201,230,104,106,155,39,170,87,179,240,178,215,129,175,74
db 21,188,151,157,6,60,184,196,245,254,133,252,34,244,5,213
db 100,30,199,232,76,201,186,128,79,30,199,232,63,156,26,170
db 87,212,56,192,23,188,109,197,87,188,133,130,71,212,130,119
db 21,188,237,200,200,254,133,23,98,4,39,170,87,84,20,224
db 87,188,237,240,245,254,133,128,119,35,199,232,63,1,173,168
db 87,84,135,232,87,188,228,43
;~
CheckSerial endp
chseend equ $

DecodeAndCall proc

	push	dword ptr [esp+4]	;+4*8
	call	Decode

	pop	eax
	pop	edx

	call	edx

	push	edx
	call	Decode

	push	eax
	ret

DecodeAndCall endp

Decode proc
	pushad

	mov	edi,dword ptr [esp+4+8*4]	;adres docelowej procki
	mov	ecx,dword ptr [edi-4]		;rozmiar docelowej procki
	mov	eax,dword ptr [edi-8]		;dword dekodujacy

	xor	ebx,ebx

	push	ecx

	shr	ecx,2
_dac1:
	xor	dword ptr [edi+4*ebx],eax
	inc	ebx
	loop	_dac1

	pop	ecx
	shl	ebx,2
	sub	ecx,ebx
	add	edi,ebx

	test	ecx,ecx
	je	_dac_end
	cmp	ecx,3
	jne	_dac2
	xor	word ptr [edi],ax
	add	edi,2
	rol	eax,16
	xor	byte ptr [edi],al
	jmp	_dac_end
_dac2:
	cmp	ecx,2
	jne	_dac3
	xor	word ptr [edi],ax
	jmp	_dac_end
_dac3:
	xor	byte ptr [edi],al
_dac_end:

	popad

	ret	4
Decode endp

NewEditProc proc hEdit,uMsg,wParam,lParam:DWORD

	cmp	uMsg,WM_RW_GETTEXT
	jne	_cp
	push	EM_GETLINE
	pop	uMsg

_cp:
	push	lParam
	push	wParam
	push	uMsg
	push	hEdit
	push	OldEditProc
	call	CallWindowProc

	cmp	uMsg,WM_KEYDOWN
	je	_chg
	cmp	uMsg,WM_KILLFOCUS
	je	_chg
	cmp	uMsg,WM_MOUSEMOVE
	je	_chg_0
	cmp	uMsg,WM_LBUTTONDOWN
	jne	_end

_chg_0:
	cmp	wParam,MK_LBUTTON
	jne	_end

_chg:	push	hEdit
	mov	eax,EN_CHANGE
	rol	eax,16
	push	eax

	push	hEdit
	call	GetDlgCtrlID

	mov	edx,eax

	pop	eax

	mov	ax,dx	;ID_EDIT_NAME
	push	eax
	push	WM_COMMAND
	push	DialogHandle
	call	SendMessage

_end:	ret
NewEditProc endp

thPaintProc proc hDlg:DWORD
	LOCAL hDlgDC:DWORD
	LOCAL hCompDC:DWORD
	LOCAL hBackDC:DWORD
	LOCAL hTextDC:DWORD
	LOCAL hSuwDC:DWORD
	LOCAL hMainBitmap:DWORD
	LOCAL hTextBitmap:DWORD
	LOCAL hSuwBitmap:DWORD
	LOCAL hCompBitmap:DWORD
	LOCAL _txSize:SIZEL
	LOCAL suwRight:DWORD
	LOCAL suwLeft:DWORD
	LOCAL scrollPos:DWORD
	LOCAL period:DWORD

	pushad

	mov	suwRight,111
	mov	suwLeft,6
	mov	scrollPos,0	;-300
	mov	period,0

	push	hDlg
	call	GetDC
	mov	hDlgDC,eax

	push	eax
	call	CreateCompatibleDC
	mov	hBackDC,eax

	push	offset id_bitmap
	push	400000h
	call	LoadBitmap
	mov	hMainBitmap,eax

	push	eax
	push	hBackDC
	call	SelectObject

	push	hDlgDC
	call	CreateCompatibleDC
	mov	hTextDC,eax

	push	hBoldFont
	push	eax
	call	SelectObject

	lea	edx,_txSize
	push	edx
	push	(sizeof strScrollText -1)
	push	offset strScrollText
	push	hTextDC
	call	GetTextExtentPoint32

	push	_txSize.y
	push	_txSize.x

	add	dword ptr [esp],600

	push	hDlgDC
	call	CreateCompatibleBitmap
	mov	hTextBitmap,eax

	push	eax
	push	hTextDC
	call	SelectObject

	push	WHITE_BRUSH
	call	GetStockObject

	push	eax
	push	hTextDC
	call	SelectObject

	push	WHITE_PEN
	call	GetStockObject

	push	eax
	push	hTextDC
	call	SelectObject

	push	_txSize.y
	push	_txSize.x
	add	dword ptr [esp],600
	push	0
	push	0
	push	hTextDC
	call	Rectangle

	push	BLACK_PEN
	call	GetStockObject

	push	eax
	push	hTextDC
	call	SelectObject

	push	(sizeof strScrollText -1)
	push	offset strScrollText
	push	0
	push	300	;0
	push	hTextDC
	call	TextOut

	push	hDlgDC
	call	CreateCompatibleDC
	mov	hCompDC,eax

	push	250
	push	300
	push	hDlgDC
	call	CreateCompatibleBitmap
	mov	hCompBitmap,eax

	push	eax
	push	hCompDC
	call	SelectObject


_nf:
	cmp	thPaintRun,0
	je	_end

	push	SRCCOPY
	push	0
	push	0
	push	hBackDC
	push	250
	push	300
	push	0
	push	0
	push	hCompDC
	call	BitBlt

	test	period,1
	je	_nextframe
	push	PATINVERT
	push	0
	push	0
	push	0
	push	25
	push	5
	push	9
	push	suwLeft
	push	hCompDC
	call	BitBlt

	push	PATINVERT
	push	0
	push	0
	push	0
	push	25
	push	5
	push	38
	push	suwLeft
	push	hCompDC
	call	BitBlt

	push	PATINVERT
	push	0
	push	0
	push	0
	push	25
	push	5
	push	68
	push	suwLeft
	push	hCompDC
	call	BitBlt

	push	PATINVERT
	push	0
	push	0
	push	0
	push	25
	push	5
	push	9
	push	suwRight
	push	hCompDC
	call	BitBlt

	push	PATINVERT
	push	0
	push	0
	push	0
	push	25
	push	5
	push	38
	push	suwRight
	push	hCompDC
	call	BitBlt

	push	PATINVERT
	push	0
	push	0
	push	0
	push	25
	push	5
	push	68
	push	suwRight
	push	hCompDC
	call	BitBlt

	push	SRCCOPY
	push	9
	push	7
	push	hCompDC
	push	84	;250
	push	109	;300
	push	9
	push	7
	push	hDlgDC
	call	BitBlt

	inc	suwLeft
	cmp	suwLeft,111
	jne	_nf2
	mov	suwLeft,6
_nf2:
	dec	suwRight
	cmp	suwRight,6
	jne	_nextframe
	mov	suwRight,111

_nextframe:
	inc	period


        push	SRCAND

        push	0
        push	scrollPos
        push	hTextDC
        push	13
        push	300
        push	221
        push	0
        push	hCompDC
        call	BitBlt

	push	SRCCOPY
	push	221
	push	0
	push	hCompDC
	push	13
	push	300
	push	221
	push	0
	push	hDlgDC
	call	BitBlt

	inc	scrollPos
	mov	eax,_txSize.x
	add	eax,300
	cmp	scrollPos,eax
	jne	_n
	mov	scrollPos,0

_n:
	push	20
	call	Sleep
	jmp	_nf

_end:
	push	hDlgDC
	push	hDlg
	call	ReleaseDC

	push	hBackDC
	call	DeleteDC

	push	hTextDC
	call	DeleteDC

	push	hCompDC
	call	DeleteDC

	push	hMainBitmap
	call	DeleteObject

	push	hTextBitmap
	call	DeleteObject

	push	hCompBitmap
	call	DeleteObject

	mov	thPaintRun,2

	popad
	ret
thPaintProc endp


MainDlgProc proc hDlg,uMsg,wParam,lParam:DWORD
	pushad

	cmp	uMsg,WM_CLOSE
	je	_close
	cmp	uMsg,WM_MOUSEMOVE
	je	_mousemove
	cmp	uMsg,WM_COMMAND
	je	_command
	cmp	uMsg,WM_INITDIALOG
	je	_init
	cmp	uMsg,WM_CTLCOLOREDIT
	je	_coloredit


_end:
	popad
	xor	eax,eax
	ret

_close:

	mov	thPaintRun,0
_the:	cmp	thPaintRun,2
	jne	_the

	push	hBoldFont
	call	DeleteObject

	push	0
	push	hDlg
	call	EndDialog
	jmp	_end

_init:
	push	hDlg
	pop	DialogHandle

	push	offset strWindowText
	push	hDlg
	call	SetWindowText

	push	0
	push	0
	push	WM_GETFONT
	push	hDlg
	call	SendMessage

	push	offset SendDlgItemMessage
	pop	_SendDlgItemMessage
	xor	_SendDlgItemMessage,0ABCDEF98h

	push	offset _strlen_
	pop	_strlen

	push	offset sctBoldFnt
	push	sizeof LOGFONT
	push	eax
	call	GetObject

	mov	sctBoldFnt.lfWeight,FW_BOLD
	push	offset sctBoldFnt
	call	CreateFontIndirect
	mov	hBoldFont,eax

	push	eax

	push	0
	push	eax
	push	WM_SETFONT
	push	ID_EDIT_NAME
	push	hDlg
	call	SendDlgItemMessage

	pop	eax
	push	0
	push	eax
	push	WM_SETFONT
	push	ID_EDIT_SERIAL
	push	hDlg
	call	SendDlgItemMessage


	push	ID_EDIT_NAME
	push	hDlg
	call	GetDlgItem
	push	eax

	push	GWL_WNDPROC
	push	eax
	call	GetWindowLong
	mov	OldEditProc,eax

	pop	eax
	push	offset NewEditProc
	push	GWL_WNDPROC
	push	eax
	call	SetWindowLong

	push	ID_EDIT_SERIAL
	push	hDlg
	call	GetDlgItem

	push	offset NewEditProc
	push	GWL_WNDPROC
	push	eax
	call	SetWindowLong



	mov	thPaintRun,1

        xor	eax,eax
        push	offset dwPaintThID
        push	eax
        push	hDlg
        push	offset thPaintProc
        push	eax
        push	eax
        call	CreateThread



	jmp	_end

_mousemove:
	cmp	wParam,1
	je	_moveok
	jmp	_end
_moveok:
	call	ReleaseCapture
	push	0
	push	0F012h
	push	WM_SYSCOMMAND
	push	hDlg
	call	SendMessage
	jmp	_end

_coloredit:

	push	TRANSPARENT
	push	wParam
	call	SetBkMode

	;push	0DFDFDFh
	;push	wParam
	;call	SetTextColor

	push	NULL_BRUSH
	call	GetStockObject
	ret

_command:
	mov	eax,wParam
	ror	eax,16
	cmp	ax,STN_CLICKED
	je	_static_clicked
	cmp	ax,EN_CHANGE
	je	_editchange

	jmp	_end

_static_clicked:
	ror	eax,16
	cmp	ax,ID_EXIT
	je	_close
	cmp	ax,ID_ABOUT
	je	_showAbout
	cmp	ax,ID_CHECK
	je	_check_serial

	jmp	_end

_editchange:
        ror	eax,16
        cmp	ax,ID_EDIT_NAME
        jne	_ec1

        push	FALSE
        push	offset nmRect
        push	hDlg
        call	InvalidateRect
        jmp	_end
	_ec1:

	push	FALSE
	push	offset srRect
	push	hDlg
	call	InvalidateRect

	jmp	_end

_showAbout:
	push	0
	push	offset DlgProc2
	push	hDlg
	push	101
	push	400000h
	call	DialogBoxParam

	jmp	_end

_check_serial:
	push	256
	push	offset strNameBuffer
	call	_zeromemory

	mov	eax,offset _strlen_

	mov	dword ptr [eax],0005C790h
	mov	dword ptr [eax+3],offset strNameBuffer
	mov	dword ptr [eax+7],0100h
	mov	word ptr [eax+11],05C7h
	mov	dword ptr [eax+13],offset strSerialBuffer
	mov	dword ptr [eax+17],0100h
	mov	word ptr [eax+21],9090h
	mov	byte ptr [eax+23],90h

;include \masm32\rewolf\rewolf_strlen.inc
_strlen_:
dd 07C8B5157h
dd 0C0330C24h
dd 0F249C933h
dd 049D1F7AEh
dd 05F59C18Bh
dd 0900004C2h


	mov	dword ptr [eax],07C8B5157h
	mov	dword ptr [eax+4],0C0330C24h
	mov	dword ptr [eax+8],0F249C933h
	mov	dword ptr [eax+12],049D1F7AEh
	mov	dword ptr [eax+16],05F59C18Bh
	mov	dword ptr [eax+20],0900004C2h

	;mov	word ptr [strNameBuffer],256
	;mov	word ptr [strSerialBuffer],256

	;push	offset strNameBuffer
	xor	byte ptr [xref2],080h
xref2	db	0E8h
	dd	offset strNameBuffer
	xor	byte ptr [xref2],080h

	;push	0
	xor	byte ptr [xref3],54h
xref3	db	3Eh,00
	xor	byte ptr [xref3],54h


	;push	WM_RW_GETTEXT
	xor 	byte ptr [xref4],58h
xref4	db	30h
	dd	WM_RW_GETTEXT
	xor 	byte ptr [xref4],58h

	;push	ID_EDIT_NAME
	xor 	byte ptr [xref5],0ABh
xref5	db	0C3h
	dd	ID_EDIT_NAME
	xor 	byte ptr [xref5],0ABh

	push	hDlg
	xor	_SendDlgItemMessage,0ABCDEF98h


	;call	_SendDlgItemMessage
	xor	word ptr [sdim1],95CAh
sdim1	dw	8035h
	dd	offset _SendDlgItemMessage
	xor	word ptr [sdim1],95CAh

	xor	_SendDlgItemMessage,0ABCDEF98h

	;push	offset strSerialBuffer
	xor	byte ptr [xref6],080h
xref6	db	0E8h
	dd	offset strSerialBuffer
	xor	byte ptr [xref6],080h

	;push	0
	xor	byte ptr [xref7],54h
xref7	db	3Eh,00
	xor	byte ptr [xref7],54h

	;push	WM_RW_GETTEXT
	xor 	byte ptr [xref8],58h
xref8	db	30h
	dd	WM_RW_GETTEXT
	xor 	byte ptr [xref8],58h

	;push	ID_EDIT_SERIAL
	xor 	byte ptr [xref9],0ABh
xref9	db	0C3h
	dd	ID_EDIT_SERIAL
	xor 	byte ptr [xref9],0ABh

	push	hDlg
	xor	_SendDlgItemMessage,0ABCDEF98h

	;call	_SendDlgItemMessage
	xor	word ptr [sdim2],95CAh
sdim2	dw	8035h
	dd	offset _SendDlgItemMessage
	xor	word ptr [sdim2],95CAh

	xor	_SendDlgItemMessage,0ABCDEF98h


	;push	offset CheckSerial
	xor	byte ptr [xref10],080h
xref10	db	0E8h
	dd	offset CheckSerial
	xor	byte ptr [xref10],080h

	;call	DecodeAndCall
	xor	byte ptr [dac],80h
dac	db	68h
	dd	not ($ - offset DecodeAndCall + 3)
	xor	byte ptr [dac],80h

	jmp	_end
MainDlgProc endp

emsgcode dd 'EMSG' xor 0ABCDEF12h
emsgsize dd emsgend-emsgsize-4
encode_msg proc lpStrMsg,lpKey:DWORD
	comment ~
	pushad
	mov	esi,lpKey
	mov	edi,lpStrMsg

	xor	ecx,ecx
	xor	edx,edx
_em1:
	cmp	byte ptr [edi+ecx],0
	je	_end
	mov	al,byte ptr [esi+edx]
	xor	byte ptr [edi+ecx],al
	inc	ecx
	inc	edx
	cmp	edx,16
	jne	_em1
	xor	edx,edx
	jmp	_em1

_end:
	popad
	ret
	~
db 0,55,108,142,222,201,140,101,40,180,179,39,102,110,0,210
db 108,188,244,255,223,184,178,222,81,133,193,172,214,70,144,155
db 184,143,82,5,188,221,73,44,93,188
encode_msg endp
emsgend equ $

start:
comment ~

	~
;-------------------------------------------

	push	offset music_start
	call	mfmPlay

	push	0
	push	offset MainDlgProc
	push	0
	push	1000
	push	400000h
	call	DialogBoxParam

	push	0
	call	mfmPlay

	push	0
	call	ExitProcess
end start


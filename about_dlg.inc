.386
option casemap:none

include \masm32\include\kernel32.inc
include \masm32\include\user32.inc
include \masm32\include\gdi32.inc
include \masm32\include\shell32.inc
includelib \masm32\lib\kernel32
includelib \masm32\lib\user32
includelib \masm32\lib\gdi32
includelib \masm32\lib\shell32

DLG_0101 = 101
ID_FRAME = 150
ID_PLUS = 151
ID_MINUS = 152
ID_CURRENTSPEED = 153
ID_MAILME = 154
ID_MYWWW = 155
ID_MAILGROUP = 157
ID_WWWGROUP = 156

;.const

.data
	TxFontName db 'Terminal',0
	txFileNFO db 'htbteam.nfo',0
	txerror_nfofile db 'I think that you lose ''HTBTeam.nfo'' file',0
	txCaption db 'ReWolf crack engine',0
	txOpen db 'open',0
	txMailMe db 'mailto:rewolf@poczta.onet.pl',0
	txMyWWW db 'http://www.rewolf.prv.pl/',0
	txMailGroup db 'mailto:htb@go2.pl',0
	txWWWGroup db 'http://htbteam.tk/',0

	cnt_rect RECT <439,37,459,49>

.data?
	hBitmap dd ?	;\
	hDCmem dd ?	;/

	hDCWnd dd ?

	dwThreadID dd ?
	hThread dd ?
	currentSpeed dd ?

	Run db ?

	dec_buffer db 11 DUP (?)


.code
;include \masm32\rewolf\rewolf_strlen.inc
include \masm32\rewolf\rewolf_int2dec.inc

prepare_nfo_file proc
	LOCAL LineCount:DWORD
	LOCAL CurrentStart:DWORD
	LOCAL y_pos:DWORD
	LOCAL hFnt:DWORD
	LOCAL hBrush:DWORD
	LOCAL hFile:DWORD
	LOCAL hMem:DWORD
	LOCAL fSize:DWORD
	LOCAL tmp:DWORD

	mov	LineCount,0
	mov	y_pos,1

	pushad

	push	0
	push	FILE_ATTRIBUTE_NORMAL
	push	OPEN_EXISTING
	push	0
	push	FILE_SHARE_READ
	push	GENERIC_READ
	push	offset txFileNFO
	call	CreateFile
	cmp	eax,INVALID_HANDLE_VALUE
	je	_error_nfofile

	mov	hFile,eax

	push	0
	push	eax
	call	GetFileSize
	mov	fSize,eax
	push	eax

	push	eax
	push	GMEM_FIXED
	call	GlobalAlloc
	mov	hMem,eax

	mov	edx,dword ptr [esp]

	push	0
	lea	ecx,[ebp+9*4]		;ecx:=offset tmp
	push	ecx
	push	edx
	push	eax
	push	hFile
	call	ReadFile

	pop	ecx
	mov	edi,hMem
	mov	eax,0Dh
_sc:	repne	scasb
	jne	_err
	inc	LineCount
	jmp	_sc
_err:
;---------------------------------------------------------------------------
	xor	eax,eax
	push	offset TxFontName ; LPCSTR ; Face
	push	eax               ; DWORD ; PitchAndFamily
	push	eax               ; DWORD ; Quality
	push	eax               ; DWORD ; ClipPrecision
	push	eax               ; DWORD ; OutputPrecision
	push	1                 ; DWORD ; Charset
	push	eax               ; DWORD ; StrikeOut
	push	eax               ; DWORD ; UnderLine
	push	eax               ; DWORD ; Italic
	push	200h              ; int ; Weight
	push	eax               ; int ; Orientation
	push	eax               ; int ; Escapement
	push	6                 ; int ; Width
	push	8                ; int ; Height
	call	CreateFont
	mov	hFnt,eax

	push	0
	push	1
	push	1
	mov	ecx,LineCount
	lea	ecx,[ecx*8+2]
	push	ecx
	push	480
	call	CreateBitmap
	mov	hBitmap,eax

	push	hDCWnd
	call	CreateCompatibleDC
	mov	hDCmem,eax

	push	hBitmap
	push	eax
	call	SelectObject

	push	WHITE_BRUSH
	call	GetStockObject
	mov	hBrush,eax

	push	eax
	push	hDCmem
	call	SelectObject

	push	001h
	push	hDCmem
	call	SetTextColor

	push	hFnt
	push	hDCmem
	call	SelectObject

	push	0
	push	0
	mov	ecx,LineCount
	lea	ecx,[ecx*8+2]
	push	ecx
	push	480
	push	hDCmem
	call	Rectangle
;---------------------------------------------------------------------------

	mov	ecx,fSize
	mov	edi,hMem

_sc2:	mov	CurrentStart,edi
	mov	eax,0Dh
	repne	scasb
	jne	_err2

	push	ecx

	push	edi
	inc	dword ptr [esp]

	dec	edi
	mov	byte ptr [edi],0

	push	CurrentStart
	call	_strlen


	push	0
	push	eax
	push	CurrentStart
	push	0
	push	ETO_OPAQUE
	push	y_pos
	push	4
	push	hDCmem
	call	ExtTextOut

	pop	edi
	pop	ecx
	add	y_pos,8
	jmp	_sc2
_err2:

	push	hFnt
	call	DeleteObject
	push	hBrush
	call	DeleteObject


	push	hMem
	call	GlobalFree
	push	hFile
	call	CloseHandle
	popad
	mov	eax,LineCount
	ret

_error_nfofile:
	push	MB_ICONERROR
	push	offset txCaption
	push	offset txerror_nfofile
	push	0
	call	MessageBox
	popad
	xor	eax,eax
	ret
prepare_nfo_file endp

ThreadFunction proc param:DWORD
	LOCAL currentY:DWORD
	LOCAL maxY:DWORD

	pushad

	mov	currentY,0
	mov	currentSpeed,30
	mov	eax,param
	lea	eax,[eax*8]
	mov	maxY,eax

_stt:	cmp	Run,0
	je	_endt

	mov	eax,maxY
	cmp	currentY,eax
	je	_zeroY

_bt:	push	SRCCOPY
	push	currentY
	push	0
	push	hDCmem
	push	193
	push	480
	push	1
	push	0
	push	hDCWnd
	call	BitBlt

	inc	currentY

	push	currentSpeed
	call	Sleep

	jmp	_stt

_endt:	mov	Run,2
	popad
	ret

_zeroY:
	mov	currentY,-193
	jmp	_bt
ThreadFunction endp

DlgProc2 proc hDlg,uMsg,wParam,lParam:DWORD
	pushad

	cmp	uMsg,WM_CLOSE
	je	_close
	cmp	uMsg,WM_INITDIALOG
	je	_init
	cmp	uMsg,WM_MOUSEMOVE
	je	_mousemove
	cmp	uMsg,WM_COMMAND
	je	_command
	cmp	uMsg,WM_RBUTTONUP
	je	_close
	cmp	uMsg,WM_HOTKEY
	je	_close
	cmp	uMsg,WM_CTLCOLORSTATIC
	je	_ctlcolorstatic
	cmp	uMsg,WM_CTLCOLORDLG
	je	_colordlg

_end:	popad
	xor	eax,eax
	ret

_close:
	mov	Run,0
_inf:	cmp	Run,2
	jne	_inf

	push	0BADh
	push	hDlg
	call	UnregisterHotKey

	push	hBitmap
	call	DeleteObject
	push	hDCmem
	call	DeleteDC
	push	0
	push	hDlg
	call	EndDialog
	jmp	_end

_init:

	mov	ebx,191

_s:     push	0
	push	hBoldFont
	push	WM_SETFONT
	push	ebx
	push	hDlg
	call	SendDlgItemMessage
	inc	ebx
	cmp	ebx,201
	jne	_s

        push	0
	push	hBoldFont
	push	WM_SETFONT
	push	153
	push	hDlg
	call	SendDlgItemMessage


        push	VK_ESCAPE
        push	0
        push	0BADh
        push	hDlg
        call	RegisterHotKey


        push	ID_FRAME
        push	hDlg
        call	GetDlgItem
        push	eax
        call	GetDC
        mov	hDCWnd,eax
	call	prepare_nfo_file
	mov	ecx,eax
	inc	ecx

	mov	Run,1

	xor	eax,eax
        push	offset dwThreadID	;lpThreadID
        push	eax			;dwCreationFlags
        push	ecx			;lpParameter
        push	offset ThreadFunction	;lpStartAddress
	push	eax			;dwStackSize
	push	eax			;lpThreadAttributes
	call	CreateThread
	mov	hThread,eax

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

_command:
	cmp	wParam,ID_PLUS
	je	_plus
	cmp	wParam,ID_MINUS
	je	_minus
	cmp	wParam,ID_MAILME
	je	_mailme
	cmp	wParam,ID_MYWWW
	je	_mywww
	cmp	wParam,ID_MAILGROUP
	je	_mailgroup
	cmp	wParam,ID_WWWGROUP
	je	_wwwgroup
	jmp	_end

_plus:
	cmp	currentSpeed,1
	je	_nxt2
	dec	currentSpeed
	jmp	_nxt2

_minus:
	cmp	currentSpeed,100
	je	_nxt2
	inc	currentSpeed
_nxt2:
	mov	eax,100
	sub	eax,currentSpeed
	inc	eax

	push	eax		;currentSpeed
	push	offset dec_buffer
	call	_int2dec

	push	offset dec_buffer
	push	ID_CURRENTSPEED
	push	hDlg
	call	SetDlgItemText

        ;push	ID_CURRENTSPEED
        ;push	hDlg
        ;call	GetDlgItem
        ;push	eax
        ;call	UpdateWindow

        push	FALSE
        push	offset cnt_rect
        push	hDlg
        call	InvalidateRect


	jmp	_end

_mailme:
	xor	eax,eax
	push	SW_SHOW
	push	eax
	push	eax
	push	offset txMailMe
	push	offset txOpen
	push	hDlg
	call	ShellExecute
	jmp	_end

_mywww:
	xor	eax,eax
	push	SW_SHOW
	push	eax
	push	eax
	push	offset txMyWWW
	push	offset txOpen
	push	hDlg
	call	ShellExecute
	jmp	_end

_mailgroup:
	xor	eax,eax
	push	SW_SHOW
	push	eax
	push	eax
	push	offset txMailGroup
	push	offset txOpen
	push	hDlg
	call	ShellExecute
	jmp	_end

_wwwgroup:
	xor	eax,eax
	push	SW_SHOW
	push	eax
	push	eax
	push	offset txWWWGroup
	push	offset txOpen
	push	hDlg
	call	ShellExecute
	jmp	_end

_ctlcolorstatic:
	push	ID_MAILME
	push	hDlg
	call	GetDlgItem
	cmp	eax,lParam
	je	_chcolor
	push	ID_MYWWW
	push	hDlg
	call	GetDlgItem
	cmp	eax,lParam
	je	_chcolor
	push	ID_MAILGROUP
	push	hDlg
	call	GetDlgItem
	cmp	eax,lParam
	je	_chcolor
	push	ID_WWWGROUP
	push	hDlg
	call	GetDlgItem
	cmp	eax,lParam
	je	_chcolor
	jmp	_other_static

_chcolor:
	push	00FFFFFFh
	push	wParam
	call	SetTextColor
	push	TRANSPARENT
	push	wParam
	call	SetBkMode
	popad
	;push	COLOR_3DFACE
	;call	GetSysColorBrush
	push	NULL_BRUSH;BLACK_BRUSH
	call	GetStockObject
	ret

_other_static:
	push	0;00AFAFAFh
	push	wParam
	call	SetTextColor
	push	TRANSPARENT
	push	wParam
	call	SetBkMode
	popad
	push	NULL_BRUSH;BLACK_BRUSH
	call	GetStockObject
	ret

_colordlg:
	popad
	push	NULL_BRUSH;BLACK_BRUSH
	call	GetStockObject
	ret
DlgProc2 endp

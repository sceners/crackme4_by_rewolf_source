comment ~

 ############
 # Hash MD5 #
 ############

 push offset _hash
 push _length_string
 push offset _string
 call _MD5

 _hash                  - wynik hashu w hex - dl. 128 bitow
 _length_string         - dlugosc stringa
 _string                - string do hashowania

 Marcus // HTBTeam (o5.o7.2oo4)
 www.marcushp.prv.pl

~

.486

_md5  PROTO	:DWORD, :DWORD, :DWORD

.data?
_md5_string   db 128 dup(?)

.code
mmd5code dd 'MMD5' xor 12345678h
mmd5size dd mmd5end-mmd5size-4
_MD5 PROC	ptrString:DWORD, ptrLength:DWORD, ptrHash:DWORD

	comment ~

		pusha
            mov   esi, ptrHash
            mov   edi, ptrString
		push	esi

            mov   ecx,32
           @@:
            mov   dword ptr [_md5_string+ecx-1],0
            loop  @B

            push  esi
            mov   ebx, ptrLength
            mov   ecx, ebx
            mov   esi, edi
            mov   edi, offset _md5_string
            push  edi
            rep   movsb
            pop   edi
            pop   esi
            mov   byte ptr [_md5_string+ebx],80h
            imul  ebx, 8
            mov   word ptr [_md5_string+38h],bx

            mov   dword ptr [esi], 67452301h
            mov   dword ptr [esi+4], 0EFCDAB89h
            mov   dword ptr [esi+8], 98BADCFEh
            mov   dword ptr [esi+0Ch], 10325476h

		mov	eax, [esi]
		mov	ebx, [esi+4]
		mov	ecx, [esi+8]
		mov	edx, [esi+0Ch]
		mov	esi, edi
		mov	edi, edx
		xor	edi, ecx
		and	edi, ebx
		xor	edi, edx
		add	eax, edi
		add	eax, [esi]
		add	eax, 0D76AA478h
		rol	eax, 7
		add	eax, ebx
		mov	edi, ecx
		xor	edi, ebx
		and	edi, eax
		xor	edi, ecx
		add	edx, edi
		add	edx, [esi+4]
		add	edx, 0E8C7B756h
		rol	edx, 0Ch
		add	edx, eax
		mov	edi, ebx
		xor	edi, eax
		and	edi, edx
		xor	edi, ebx
		add	ecx, edi
		add	ecx, [esi+8]
		add	ecx, 242070DBh
		rol	ecx, 11h
		add	ecx, edx
		mov	edi, eax
		xor	edi, edx
		and	edi, ecx
		xor	edi, eax
		add	ebx, edi
		add	ebx, [esi+0Ch]
		add	ebx, 0C1BDCEEEh
		rol	ebx, 16h
		add	ebx, ecx
		mov	edi, edx
		xor	edi, ecx
		and	edi, ebx
		xor	edi, edx
		add	eax, edi
		add	eax, [esi+10h]
		add	eax, 0F57C0FAFh
		rol	eax, 7
		add	eax, ebx
		mov	edi, ecx
		xor	edi, ebx
		and	edi, eax
		xor	edi, ecx
		add	edx, edi
		add	edx, [esi+14h]
		add	edx, 4787C62Ah
		rol	edx, 0Ch
		add	edx, eax
		mov	edi, ebx
		xor	edi, eax
		and	edi, edx
		xor	edi, ebx
		add	ecx, edi
		add	ecx, [esi+18h]
		add	ecx, 0A8304613h
		rol	ecx, 11h
		add	ecx, edx
		mov	edi, eax
		xor	edi, edx
		and	edi, ecx
		xor	edi, eax
		add	ebx, edi
		add	ebx, [esi+1Ch]
		add	ebx, 0FD469501h
		rol	ebx, 16h
		add	ebx, ecx
		mov	edi, edx
		xor	edi, ecx
		and	edi, ebx
		xor	edi, edx
		add	eax, edi
		add	eax, [esi+20h]
		add	eax, 698098D8h
		rol	eax, 7
		add	eax, ebx
		mov	edi, ecx
		xor	edi, ebx
		and	edi, eax
		xor	edi, ecx
		add	edx, edi
		add	edx, [esi+24h]
		add	edx, 8B44F7AFh
		rol	edx, 0Ch
		add	edx, eax
		mov	edi, ebx
		xor	edi, eax
		and	edi, edx
		xor	edi, ebx
		add	ecx, edi
		add	ecx, [esi+28h]
		add	ecx, 0FFFF5BB1h
		rol	ecx, 11h
		add	ecx, edx
		mov	edi, eax
		xor	edi, edx
		and	edi, ecx
		xor	edi, eax
		add	ebx, edi
		add	ebx, [esi+2Ch]
		add	ebx, 895CD7BEh
		rol	ebx, 16h
		add	ebx, ecx
		mov	edi, edx
		xor	edi, ecx
		and	edi, ebx
		xor	edi, edx
		add	eax, edi
		add	eax, [esi+30h]
		add	eax, 6B901122h
		rol	eax, 7
		add	eax, ebx
		mov	edi, ecx
		xor	edi, ebx
		and	edi, eax
		xor	edi, ecx
		add	edx, edi
		add	edx, [esi+34h]
		add	edx, 0FD987193h
		rol	edx, 0Ch
		add	edx, eax
		mov	edi, ebx
		xor	edi, eax
		and	edi, edx
		xor	edi, ebx
		add	ecx, edi
		add	ecx, [esi+38h]
		add	ecx, 0A679438Eh
		rol	ecx, 11h
		add	ecx, edx
		mov	edi, eax
		xor	edi, edx
		and	edi, ecx
		xor	edi, eax
		add	ebx, edi
		add	ebx, [esi+3Ch]
		add	ebx, 49B40821h
		rol	ebx, 16h
		add	ebx, ecx
		mov	edi, ecx
		xor	edi, ebx
		and	edi, edx
		xor	edi, ecx
		add	eax, edi
		add	eax, [esi+4]
		add	eax, 0F61E2562h
		rol	eax, 5
		add	eax, ebx
		mov	edi, ebx
		xor	edi, eax
		and	edi, ecx
		xor	edi, ebx
		add	edx, edi
		add	edx, [esi+18h]
		add	edx, 0C040B340h
		rol	edx, 9
		add	edx, eax
		mov	edi, eax
		xor	edi, edx
		and	edi, ebx
		xor	edi, eax
		add	ecx, edi
		add	ecx, [esi+2Ch]
		add	ecx, 265E5A51h
		rol	ecx, 0Eh
		add	ecx, edx
		mov	edi, edx
		xor	edi, ecx
		and	edi, eax
		xor	edi, edx
		add	ebx, edi
		add	ebx, [esi]
		add	ebx, 0E9B6C7AAh
		rol	ebx, 14h
		add	ebx, ecx
		mov	edi, ecx
		xor	edi, ebx
		and	edi, edx
		xor	edi, ecx
		add	eax, edi
		add	eax, [esi+14h]
		add	eax, 0D62F105Dh
		rol	eax, 5
		add	eax, ebx
		mov	edi, ebx
		xor	edi, eax
		and	edi, ecx
		xor	edi, ebx
		add	edx, edi
		add	edx, [esi+28h]
		add	edx, 2441453h
		rol	edx, 9
		add	edx, eax
		mov	edi, eax
		xor	edi, edx
		and	edi, ebx
		xor	edi, eax
		add	ecx, edi
		add	ecx, [esi+3Ch]
		add	ecx, 0D8A1E681h
		rol	ecx, 0Eh
		add	ecx, edx
		mov	edi, edx
		xor	edi, ecx
		and	edi, eax
		xor	edi, edx
		add	ebx, edi
		add	ebx, [esi+10h]
		add	ebx, 0E7D3FBC8h
		rol	ebx, 14h
		add	ebx, ecx
		mov	edi, ecx
		xor	edi, ebx
		and	edi, edx
		xor	edi, ecx
		add	eax, edi
		add	eax, [esi+24h]
		add	eax, 21E1CDE6h
		rol	eax, 5
		add	eax, ebx
		mov	edi, ebx
		xor	edi, eax
		and	edi, ecx
		xor	edi, ebx
		add	edx, edi
		add	edx, [esi+38h]
		add	edx, 0C33707D6h
		rol	edx, 9
		add	edx, eax
		mov	edi, eax
		xor	edi, edx
		and	edi, ebx
		xor	edi, eax
		add	ecx, edi
		add	ecx, [esi+0Ch]
		add	ecx, 0F4D50D87h
		rol	ecx, 0Eh
		add	ecx, edx
		mov	edi, edx
		xor	edi, ecx
		and	edi, eax
		xor	edi, edx
		add	ebx, edi
		add	ebx, [esi+20h]
		add	ebx, 455A14EDh
		rol	ebx, 14h
		add	ebx, ecx
		mov	edi, ecx
		xor	edi, ebx
		and	edi, edx
		xor	edi, ecx
		add	eax, edi
		add	eax, [esi+34h]
		add	eax, 0A9E3E905h
		rol	eax, 5
		add	eax, ebx
		mov	edi, ebx
		xor	edi, eax
		and	edi, ecx
		xor	edi, ebx
		add	edx, edi
		add	edx, [esi+8]
		add	edx, 0FCEFA3F8h
		rol	edx, 9
		add	edx, eax
		mov	edi, eax
		xor	edi, edx
		and	edi, ebx
		xor	edi, eax
		add	ecx, edi
		add	ecx, [esi+1Ch]
		add	ecx, 676F02D9h
		rol	ecx, 0Eh
		add	ecx, edx
		mov	edi, edx
		xor	edi, ecx
		and	edi, eax
		xor	edi, edx
		add	ebx, edi
		add	ebx, [esi+30h]
		add	ebx, 8D2A4C8Ah
		rol	ebx, 14h
		add	ebx, ecx
		mov	edi, ebx
		xor	edi, ecx
		xor	edi, edx
		add	eax, edi
		add	eax, [esi+14h]
		add	eax, 0FFFA3942h
		rol	eax, 4
		add	eax, ebx
		mov	edi, eax
		xor	edi, ebx
		xor	edi, ecx
		add	edx, edi
		add	edx, [esi+20h]
		add	edx, 8771F681h
		rol	edx, 0Bh
		add	edx, eax
		mov	edi, edx
		xor	edi, eax
		xor	edi, ebx
		add	ecx, edi
		add	ecx, [esi+2Ch]
		add	ecx, 6D9D6122h
		rol	ecx, 10h
		add	ecx, edx
		mov	edi, ecx
		xor	edi, edx
		xor	edi, eax
		add	ebx, edi
		add	ebx, [esi+38h]
		add	ebx, 0FDE5380Ch
		rol	ebx, 17h
		add	ebx, ecx
		mov	edi, ebx
		xor	edi, ecx
		xor	edi, edx
		add	eax, edi
		add	eax, [esi+4]
		add	eax, 0A4BEEA44h
		rol	eax, 4
		add	eax, ebx
		mov	edi, eax
		xor	edi, ebx
		xor	edi, ecx
		add	edx, edi
		add	edx, [esi+10h]
		add	edx, 4BDECFA9h
		rol	edx, 0Bh
		add	edx, eax
		mov	edi, edx
		xor	edi, eax
		xor	edi, ebx
		add	ecx, edi
		add	ecx, [esi+1Ch]
		add	ecx, 0F6BB4B60h
		rol	ecx, 10h
		add	ecx, edx
		mov	edi, ecx
		xor	edi, edx
		xor	edi, eax
		add	ebx, edi
		add	ebx, [esi+28h]
		add	ebx, 0BEBFBC70h
		rol	ebx, 17h
		add	ebx, ecx
		mov	edi, ebx
		xor	edi, ecx
		xor	edi, edx
		add	eax, edi
		add	eax, [esi+34h]
		add	eax, 289B7EC6h
		rol	eax, 4
		add	eax, ebx
		mov	edi, eax
		xor	edi, ebx
		xor	edi, ecx
		add	edx, edi
		add	edx, [esi]
		add	edx, 0EAA127FAh
		rol	edx, 0Bh
		add	edx, eax
		mov	edi, edx
		xor	edi, eax
		xor	edi, ebx
		add	ecx, edi
		add	ecx, [esi+0Ch]
		add	ecx, 0D4EF3085h
		rol	ecx, 10h
		add	ecx, edx
		mov	edi, ecx
		xor	edi, edx
		xor	edi, eax
		add	ebx, edi
		add	ebx, [esi+18h]
		add	ebx, 4881D05h
		rol	ebx, 17h
		add	ebx, ecx
		mov	edi, ebx
		xor	edi, ecx
		xor	edi, edx
		add	eax, edi
		add	eax, [esi+24h]
		add	eax, 0D9D4D039h
		rol	eax, 4
		add	eax, ebx
		mov	edi, eax
		xor	edi, ebx
		xor	edi, ecx
		add	edx, edi
		add	edx, [esi+30h]
		add	edx, 0E6DB99E5h
		rol	edx, 0Bh
		add	edx, eax
		mov	edi, edx
		xor	edi, eax
		xor	edi, ebx
		add	ecx, edi
		add	ecx, [esi+3Ch]
		add	ecx, 1FA27CF8h
		rol	ecx, 10h
		add	ecx, edx
		mov	edi, ecx
		xor	edi, edx
		xor	edi, eax
		add	ebx, edi
		add	ebx, [esi+8]
		add	ebx, 0C4AC5665h
		rol	ebx, 17h
		add	ebx, ecx
		mov	edi, edx
		not	edi
		or	edi, ebx
		xor	edi, ecx
		add	eax, edi
		add	eax, [esi]
		add	eax, 0F4292244h
		rol	eax, 6
		add	eax, ebx
		mov	edi, ecx
		not	edi
		or	edi, eax
		xor	edi, ebx
		add	edx, edi
		add	edx, [esi+1Ch]
		add	edx, 432AFF97h
		rol	edx, 0Ah
		add	edx, eax
		mov	edi, ebx
		not	edi
		or	edi, edx
		xor	edi, eax
		add	ecx, edi
		add	ecx, [esi+38h]
		add	ecx, 0AB9423A7h
		rol	ecx, 0Fh
		add	ecx, edx
		mov	edi, eax
		not	edi
		or	edi, ecx
		xor	edi, edx
		add	ebx, edi
		add	ebx, [esi+14h]
		add	ebx, 0FC93A039h
		rol	ebx, 15h
		add	ebx, ecx
		mov	edi, edx
		not	edi
		or	edi, ebx
		xor	edi, ecx
		add	eax, edi
		add	eax, [esi+30h]
		add	eax, 655B59C3h
		rol	eax, 6
		add	eax, ebx
		mov	edi, ecx
		not	edi
		or	edi, eax
		xor	edi, ebx
		add	edx, edi
		add	edx, [esi+0Ch]
		add	edx, 8F0CCC92h
		rol	edx, 0Ah
		add	edx, eax
		mov	edi, ebx
		not	edi
		or	edi, edx
		xor	edi, eax
		add	ecx, edi
		add	ecx, [esi+28h]
		add	ecx, 0FFEFF47Dh
		rol	ecx, 0Fh
		add	ecx, edx
		mov	edi, eax
		not	edi
		or	edi, ecx
		xor	edi, edx
		add	ebx, edi
		add	ebx, [esi+4]
		add	ebx, 85845DD1h
		rol	ebx, 15h
		add	ebx, ecx
		mov	edi, edx
		not	edi
		or	edi, ebx
		xor	edi, ecx
		add	eax, edi
		add	eax, [esi+20h]
		add	eax, 6FA87E4Fh
		rol	eax, 6
		add	eax, ebx
		mov	edi, ecx
		not	edi
		or	edi, eax
		xor	edi, ebx
		add	edx, edi
		add	edx, [esi+3Ch]
		add	edx, 0FE2CE6E0h
		rol	edx, 0Ah
		add	edx, eax
		mov	edi, ebx
		not	edi
		or	edi, edx
		xor	edi, eax
		add	ecx, edi
		add	ecx, [esi+18h]
		add	ecx, 0A3014314h
		rol	ecx, 0Fh
		add	ecx, edx
		mov	edi, eax
		not	edi
		or	edi, ecx
		xor	edi, edx
		add	ebx, edi
		add	ebx, [esi+34h]
		add	ebx, 4E0811A1h
		rol	ebx, 15h
		add	ebx, ecx
		mov	edi, edx
		not	edi
		or	edi, ebx
		xor	edi, ecx
		add	eax, edi
		add	eax, [esi+10h]
		add	eax, 0F7537E82h
		rol	eax, 6
		add	eax, ebx
		mov	edi, ecx
		not	edi
		or	edi, eax
		xor	edi, ebx
		add	edx, edi
		add	edx, [esi+2Ch]
		add	edx, 0BD3AF235h
		rol	edx, 0Ah
		add	edx, eax
		mov	edi, ebx
		not	edi
		or	edi, edx
		xor	edi, eax
		add	ecx, edi
		add	ecx, [esi+8]
		add	ecx, 2AD7D2BBh
		rol	ecx, 0Fh
		add	ecx, edx
		mov	edi, eax
		not	edi
		or	edi, ecx
		xor	edi, edx
		add	ebx, edi
		add	ebx, [esi+24h]
		add	ebx, 0EB86D391h
		rol	ebx, 15h
		add	ebx, ecx
		pop	esi
		add	[esi], eax
		add	[esi+4], ebx
		add	[esi+8], ecx
		add	[esi+0Ch], edx
		popa
		ret
		~
		;comment ~
db 24,153,149,63,198,103,105,212,48,26,47,230,109,18,121,95
db 138,147,138,255,15,18,121,95,77,18,155,171,27,153,36,83
db 198,217,242,168,242,230,217,29,77,69,138,251,18,76,191,220
db 185,178,59,95,205,121,162,87,43,155,100,115,236,80,121,152
db 75,19,90,26,42,213,63,91,196,185,180,176,138,84,113,161
db 145,168,225,152,11,30,15,11,127,2,242,89,198,76,125,212
db 3,26,242,9,65,153,142,212,183,33,128,124,182,33,131,92
db 138,17,127,90,53,182,19,136,140,210,126,92,142,153,128,108
db 182,49,129,108,180,17,174,92,27,22,248,157,27,165,190,183
db 140,208,117,92,157,153,130,108,181,49,131,108,182,17,182,92
db 3,26,248,158,150,98,89,123,140,211,104,92,135,153,129,108
db 183,49,128,108,181,17,166,92,19,30,248,156,163,220,196,158
db 140,209,111,92,148,153,131,108,180,49,130,108,183,17,190,92
db 11,2,124,240,66,110,140,158,141,21,122,156,198,235,74,164
db 110,234,74,166,78,197,122,9,89,147,187,117,139,149,62,158
db 143,30,122,143,198,233,74,167,110,232,74,164,78,221,122,17
db 85,147,184,76,11,34,209,158,140,3,122,149,198,234,74,165
db 110,235,74,167,78,205,122,1,81,147,186,94,216,84,132,158
db 142,4,122,134,198,232,74,166,110,233,74,165,78,213,122,25
db 109,23,161,199,205,123,184,159,74,17,186,212,180,33,130,124
db 181,33,128,92,154,17,47,123,204,208,214,168,9,153,184,157
db 65,17,169,212,182,33,129,124,183,33,130,92,130,17,55,119
db 204,211,200,4,178,237,184,158,92,17,179,212,181,33,131,124
db 180,33,129,92,146,17,39,115,204,209,199,136,17,155,184,156
db 91,17,160,212,183,33,128,124,182,33,131,92,138,17,63,111
db 72,48,104,207,38,211,185,88,78,209,242,166,126,233,90,167
db 126,235,122,136,78,68,77,222,143,129,8,199,176,211,187,83
db 78,194,242,164,126,234,90,165,126,233,122,144,78,92,65,222
db 140,156,58,38,235,211,184,78,78,216,242,167,126,232,90,166
db 126,234,122,128,78,76,69,222,142,51,113,235,4,211,186,73
db 78,203,242,166,126,233,90,165,126,235,122,152,78,84,125,90
db 47,55,103,169,140,210,124,92,142,153,130,108,181,49,128,108
db 182,17,174,92,27,10,248,157,13,161,57,159,140,208,112,92
db 157,153,129,108,183,49,130,108,181,17,182,92,3,62,248,158
db 28,72,39,121,140,211,119,92,135,153,131,108,180,49,129,108
db 183,17,166,92,83,147,186,245,138,164,144,158,142,6,122,134
db 198,235,74,164,110,232,74,166,78,213,122,25,89,23,36,79
db 98,196,184,159,72,17,186,212,182,33,129,124,180,33,130,92
db 154,17,47,119,204,208,42,75,9,16,184,157,68,17,169,212
db 181,33,131,124,182,33,129,92,130,17,55,99,204,211,248,185
db 236,202,184,158,67,17,179,212,183,33,128,124,181,33,131,92
db 146,17,39,79,204,209,177,164,158,245,184,156,89,17,160,212
db 180,33,130,124,183,33,128,92,138,17,63,123,72,244,180,190
db 108,211,185,90,78,209,242,164,126,234,90,166,126,233,122,136
db 78,68,65,222,143,196,126,104,142,211,187,86,78,194,242,167
db 126,232,90,164,126,234,122,144,78,92,117,222,140,149,116,138
db 185,211,184,81,78,216,242,165,126,235,90,167,126,232,122,128
db 78,76,89,222,142,255,109,5,8,211,186,75,78,203,242,166
db 126,233,90,165,126,235,122,152,78,84,77,90,72,251,154,246
db 140,210,124,92,142,153,130,108,181,49,128,108,182,17,174,92
db 27,26,248,157,181,177,150,163,140,208,112,92,157,153,129,108
db 183,49,130,108,181,17,182,92,3,14,248,158,148,16,22,56
db 140,211,119,92,135,153,131,108,180,49,129,108,183,17,166,92
db 19,34,248,156,199,94,83,210,140,209,109,92,148,153,130,108
db 180,33,131,92,138,17,63,75,72,80,64,165,178,211,185,91
db 78,209,242,167,126,233,74,166,78,197,122,9,109,147,187,222
db 187,99,254,158,143,25,122,143,198,232,74,167,126,233,122,144
db 78,92,85,222,140,48,24,194,32,211,184,79,78,216,242,166
db 126,232,74,167,78,205,122,1,117,147,186,83,117,247,132,158
db 142,5,122,134,198,233,74,166,126,232,122,152,78,84,125,90
db 9,248,199,251,140,210,125,92,142,153,129,108,182,33,128,92
db 154,17,47,79,204,208,208,144,147,89,184,157,70,17,169,212
db 183,33,129,108,182,17,182,92,3,14,248,158,45,89,194,169
db 140,211,105,92,135,153,128,108,183,33,129,92,146,17,39,119
db 204,209,9,227,242,172,184,156,90,17,160,212,182,33,128,108
db 183,17,190,92,11,38,124,153,51,137,81,158,141,22,122,156
db 198,234,74,164,126,235,122,136,78,4,248,157,183,53,216,181
db 140,208,114,92,157,153,131,108,181,33,130,92,130,17,55,83
db 204,211,252,111,162,198,184,158,93,17,179,212,180,33,131,108
db 181,17,166,92,19,10,248,156,72,15,241,91,140,209,110,92
db 148,153,130,108,180,33,131,92,138,17,63,123,72,43,169,139
db 148,211,185,91,78,209,242,167,126,233,74,166,78,197,122,9
db 125,147,187,186,212,201,159,158,143,25,122,143,198,232,74,167
db 126,233,122,144,78,92,69,222,140,234,5,253,82,211,184,79
db 78,216,242,166,126,232,74,167,78,205,122,1,69,147,186,58
db 27,190,189,158,142,5,122,134,198,232,142,136,70,233,74,166
db 78,213,122,89,72,86,91,118,185,211,185,89,78,209,242,166
db 186,197,114,167,126,233,122,136,78,68,101,222,143,133,134,117
db 14,211,187,85,78,194,242,164,186,197,114,165,126,234,122,144
db 78,92,65,222,140,181,90,203,230,211,184,80,78,216,242,167
db 186,197,114,166,126,232,122,128,78,76,109,222,142,43,217,204
db 177,211,186,74,78,203,242,165,186,197,114,164,126,235,122,152
db 78,84,73,90,142,75,34,58,140,210,127,92,142,153,128,168
db 154,25,129,108,182,17,174,92,27,30,248,157,223,222,117,208
db 140,208,115,92,157,153,130,168,154,25,131,108,181,17,182,92
db 3,58,248,158,48,230,150,160,140,211,118,92,135,153,129,168
db 154,25,128,108,183,17,166,92,19,22,248,156,156,79,253,218
db 140,209,108,92,148,153,131,168,154,25,130,108,180,17,190,92
db 11,50,124,16,51,186,22,158,141,20,122,156,198,235,142,136
db 70,234,74,164,78,197,122,9,113,147,187,191,171,62,135,158
db 143,24,122,143,198,233,142,136,70,232,74,167,78,221,122,17
db 85,147,184,75,14,19,218,158,140,29,122,149,198,234,142,136
db 70,235,74,165,78,205,122,1,121,147,186,254,92,26,55,158
db 142,7,122,134,198,232,142,136,70,233,74,166,78,213,122,25
db 93,23,251,33,30,229,184,159,75,17,186,212,180,229,174,84
db 181,33,130,92,154,17,47,115,204,208,76,173,119,175,184,157
db 71,17,169,212,182,229,174,84,183,33,129,92,130,17,55,87
db 204,211,194,141,154,56,184,158,66,17,179,212,181,229,174,84
db 180,33,131,92,146,17,39,123,204,209,232,140,203,249,184,156
db 88,17,160,1,76,20,120,1,73,19,55,87,76,68,117,62
db 132,208,117,95

;~
_MD5 endp
mmd5end equ $

;-------------------------------------------------------------------------
.586
.MODEL FLAT, STDCALL
OPTION CASEMAP:NONE
.XMM

.NOLIST
.NOCREF
;INCLUDE    \masm32\include\windows.inc
.LIST

OPTION CASEMAP:NONE
;INCLUDE C:\masm32\include\windows.inc
.DATA
Temp dword 0

RED_GIMP real4 0.3
GREEN_GIMP real4 0.59
BLUE_GIMP real4 0.11

RED_BT709 real4 0.2126
GREEN_BT709 real4 0.7152
BLUE_BT709 real4 0.0722

RED_BT601 real4 0.299
GREEN_BT601 real4 0.587
BLUE_BT601 real4 0.114

Quotient word 3

.CODE

DllEntry PROC hInstDLL:DWORD, reason:DWORD, reserved1:DWORD

mov	eax, 1 	;TRUE
ret

DllEntry ENDP

;-------------------------------------------------------------------------
; This is an example function. It's here to show
; where to put your own functions in the DLL
;-------------------------------------------------------------------------

Grayscale_GIMP proc arr: PTR DWORD, len: DWORD
mov eax, len
cmp eax, 0
jne not_empty
jmp empty

not_empty:
mov edx, dword ptr ds:[arr]
xor eax, eax
push esi
xor esi, esi
push ebx
xor ebx, ebx

FINIT 
L1:
;Count Red
xor ebx, ebx
mov ebx, [edx + esi * 4]
mov Temp, ebx
fld RED_GIMP
fimul Temp
inc esi

;Count Green
xor ebx, ebx
mov ebx, [edx + esi * 4]
mov Temp, ebx
fld GREEN_GIMP
fimul Temp
inc esi

;Count Blue
xor ebx, ebx
mov ebx, [edx + esi * 4]
mov Temp, ebx
fld BLUE_GIMP
fimul Temp
inc esi

fadd
fadd
fistp Temp
mov ebx, Temp
;mov edx, dword ptr ds:[arr]
sub esi, 3
mov [edx + esi * 4], ebx
inc esi
mov [edx + esi * 4], ebx
inc esi
mov [edx + esi * 4], ebx

inc esi
cmp esi, len
jne L1

empty:
pop ebx
pop esi

ret
Grayscale_GIMP endp

Grayscale_BT709 proc arr: PTR DWORD, len: DWORD
mov eax, len
cmp eax, 0
jne not_empty
jmp empty

not_empty:
mov edx, dword ptr ds:[arr]
xor eax, eax
push esi
xor esi, esi
push ebx
xor ebx, ebx

FINIT 
L1:
;Count Red
xor ebx, ebx
mov ebx, [edx + esi * 4]
mov Temp, ebx
fld RED_BT709
fimul Temp
inc esi

;Count Green
xor ebx, ebx
mov ebx, [edx + esi * 4]
mov Temp, ebx
fld GREEN_BT709
fimul Temp
inc esi

;Count Blue
xor ebx, ebx
mov ebx, [edx + esi * 4]
mov Temp, ebx
fld BLUE_BT709
fimul Temp
inc esi

fadd
fadd
fistp Temp
mov ebx, Temp
;mov edx, dword ptr ds:[arr]
sub esi, 3
mov [edx + esi * 4], ebx
inc esi
mov [edx + esi * 4], ebx
inc esi
mov [edx + esi * 4], ebx

inc esi
cmp esi, len
jne L1

empty:
pop ebx
pop esi

ret
Grayscale_BT709 endp


Grayscale_BT601 proc arr: PTR DWORD, len: DWORD
mov eax, len
cmp eax, 0
jne not_empty
jmp empty

not_empty:
mov edx, dword ptr ds:[arr]
xor eax, eax
push esi
xor esi, esi
push ebx
xor ebx, ebx

FINIT 
L1:
;Count Red
xor ebx, ebx
mov ebx, [edx + esi * 4]
mov Temp, ebx
fld RED_BT601
fimul Temp
inc esi

;Count Green
xor ebx, ebx
mov ebx, [edx + esi * 4]
mov Temp, ebx
fld GREEN_BT601
fimul Temp
inc esi

;Count Blue
xor ebx, ebx
mov ebx, [edx + esi * 4]
mov Temp, ebx
fld BLUE_BT601
fimul Temp
inc esi

fadd
fadd
fistp Temp
mov ebx, Temp
;mov edx, dword ptr ds:[arr]
sub esi, 3
mov [edx + esi * 4], ebx
inc esi
mov [edx + esi * 4], ebx
inc esi
mov [edx + esi * 4], ebx

inc esi
cmp esi, len
jne L1

empty:
pop ebx
pop esi

ret
Grayscale_BT601 endp

Grayscale_arithmetic proc arr: PTR DWORD, len: DWORD
mov eax, len
cmp eax, 0
jne not_empty
jmp empty

not_empty:
mov edx, dword ptr ds:[arr]
xor eax, eax
push esi
xor esi, esi
push ebx
xor ebx, ebx

FINIT 
L1:
;Add Red
xor ebx, ebx
mov ebx, [edx + esi * 4]
add Temp, ebx
inc esi

;Add Green
xor ebx, ebx
mov ebx, [edx + esi * 4]
add Temp, ebx
inc esi

;Add Blue
xor ebx, ebx
mov ebx, [edx + esi * 4]
add Temp, ebx
inc esi

;Push sum of RGB
fild Temp
fidiv Quotient

fistp Temp
mov ebx, Temp
;mov edx, dword ptr ds:[arr]
sub esi, 3
mov [edx + esi * 4], ebx
inc esi
mov [edx + esi * 4], ebx
inc esi
mov [edx + esi * 4], ebx

inc esi
cmp esi, len
jne L1

empty:
pop ebx
pop esi

ret
Grayscale_arithmetic endp

END DllEntry
;-------------------------------------------------------------------------

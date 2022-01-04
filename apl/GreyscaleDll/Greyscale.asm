.MODEL FLAT, STDCALL
OPTION CASEMAP:NONE

.NOLIST
.NOCREF

.LIST

;OPTION CASEMAP:NONE

.DATA
RED_TEMP_ARR_256 real4 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0
GREEN_TEMP_ARR_256 real4 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0
BLUE_TEMP_ARR_256 real4 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0
GRAY_RES_ARR_256 real4 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0
Counter dword 0

RED_GIMP_BT601 real4 0.299
GREEN_GIMP_BT601 real4 0.587
BLUE_GIMP_BT601 real4 0.114

RED_BT709 real4 0.2126
GREEN_BT709 real4 0.7152
BLUE_BT709 real4 0.0722

RED_BT2100 real4 0.2627
GREEN_BT2100 real4 0.6780
BLUE_BT2100 real4 0.0593

Quotient real4 3.0

.CODE

DllEntry PROC hInstDLL:DWORD, reason:DWORD, reserved1:DWORD
mov	eax, 1 	
ret

DllEntry ENDP


Grayscale_GIMP_BT601 proc arr: PTR DWORD, len: DWORD
mov eax, len
cmp eax, 0
jne not_empty
jmp empty

not_empty:
mov edx, DWORD ptr ds:[arr]
xor eax, eax
push esi
xor esi, esi
push ebx
xor ebx, ebx
push ecx
xor ecx, ecx
VBROADCASTSS ymm3, RED_GIMP_BT601
VBROADCASTSS ymm4, GREEN_GIMP_BT601
VBROADCASTSS ymm5, BLUE_GIMP_BT601

start_loop:
xor ecx, ecx
mov Counter, 0
loop1:
mov ebx, [edx + esi * 4]
mov [RED_TEMP_ARR_256 + ecx * 4], ebx
inc esi

mov ebx, [edx + esi * 4]
mov [GREEN_TEMP_ARR_256 + ecx * 4], ebx
inc esi

mov ebx, [edx + esi * 4]
mov [BLUE_TEMP_ARR_256 + ecx * 4], ebx
inc esi

add Counter, 3
inc ecx
cmp esi, len
je loop2
cmp Counter, 24
jne loop1

loop2:
vmulps  ymm0, ymm3, ymmword ptr[RED_TEMP_ARR_256]
vmulps  ymm1, ymm4, ymmword ptr[GREEN_TEMP_ARR_256]
vmulps  ymm2, ymm5, ymmword ptr[BLUE_TEMP_ARR_256]

vaddps ymm0, ymm0, ymm1
vaddps ymm0, ymm0, ymm2

vroundps ymm0,ymm0, 0
vmovups ymmword ptr[GRAY_RES_ARR_256], ymm0

sub esi, Counter

xor ecx, ecx
loop3:
mov ebx, [GRAY_RES_ARR_256 + ecx * 4]
mov [edx + esi * 4], ebx
inc esi
mov [edx + esi * 4], ebx
inc esi
mov [edx + esi * 4], ebx
inc esi
inc ecx

cmp esi, len
je empty

cmp ecx, 8
jne loop3

cmp esi, len
jne start_loop

empty:
pop ecx
pop ebx
pop esi

ret
Grayscale_GIMP_BT601 endp

Grayscale_BT709 proc arr: PTR DWORD, len: DWORD
mov eax, len
cmp eax, 0
jne not_empty
jmp empty

not_empty:
mov edx, DWORD ptr ds:[arr]
xor eax, eax
push esi
xor esi, esi
push ebx
xor ebx, ebx
push ecx
xor ecx, ecx
VBROADCASTSS ymm3, RED_BT709
VBROADCASTSS ymm4, GREEN_BT709
VBROADCASTSS ymm5, BLUE_BT709

start_loop:
xor ecx, ecx
mov Counter, 0
loop1:
mov ebx, [edx + esi * 4]
mov [RED_TEMP_ARR_256 + ecx * 4], ebx
inc esi

mov ebx, [edx + esi * 4]
mov [GREEN_TEMP_ARR_256 + ecx * 4], ebx
inc esi

mov ebx, [edx + esi * 4]
mov [BLUE_TEMP_ARR_256 + ecx * 4], ebx
inc esi

add Counter, 3
inc ecx
cmp esi, len
je loop2
cmp Counter, 24
jne loop1

loop2:
vmulps  ymm0, ymm3, ymmword ptr[RED_TEMP_ARR_256]
vmulps  ymm1, ymm4, ymmword ptr[GREEN_TEMP_ARR_256]
vmulps  ymm2, ymm5, ymmword ptr[BLUE_TEMP_ARR_256]

vaddps ymm0, ymm0, ymm1
vaddps ymm0, ymm0, ymm2

vroundps ymm0,ymm0, 0
vmovups ymmword ptr[GRAY_RES_ARR_256], ymm0

sub esi, Counter

xor ecx, ecx
loop3:
mov ebx, [GRAY_RES_ARR_256 + ecx * 4]
mov [edx + esi * 4], ebx
inc esi
mov [edx + esi * 4], ebx
inc esi
mov [edx + esi * 4], ebx
inc esi
inc ecx

cmp esi, len
je empty

cmp ecx, 8
jne loop3

cmp esi, len
jne start_loop

empty:
pop ecx
pop ebx
pop esi

ret
Grayscale_BT709 endp


Grayscale_BT2100 proc arr: PTR DWORD, len: DWORD
mov eax, len
cmp eax, 0
jne not_empty
jmp empty

not_empty:
mov edx, DWORD ptr ds:[arr]
xor eax, eax
push esi
xor esi, esi
push ebx
xor ebx, ebx
push ecx
xor ecx, ecx
VBROADCASTSS ymm3, RED_BT2100
VBROADCASTSS ymm4, GREEN_BT2100
VBROADCASTSS ymm5, BLUE_BT2100

start_loop:
xor ecx, ecx
mov Counter, 0
loop1:
mov ebx, [edx + esi * 4]
mov [RED_TEMP_ARR_256 + ecx * 4], ebx
inc esi

mov ebx, [edx + esi * 4]
mov [GREEN_TEMP_ARR_256 + ecx * 4], ebx
inc esi

mov ebx, [edx + esi * 4]
mov [BLUE_TEMP_ARR_256 + ecx * 4], ebx
inc esi

add Counter, 3
inc ecx
cmp esi, len
je loop2
cmp Counter, 24
jne loop1

loop2:
vmulps  ymm0, ymm3, ymmword ptr[RED_TEMP_ARR_256]
vmulps  ymm1, ymm4, ymmword ptr[GREEN_TEMP_ARR_256]
vmulps  ymm2, ymm5, ymmword ptr[BLUE_TEMP_ARR_256]

vaddps ymm0, ymm0, ymm1
vaddps ymm0, ymm0, ymm2

vroundps ymm0,ymm0, 0
vmovups ymmword ptr[GRAY_RES_ARR_256], ymm0

sub esi, Counter

xor ecx, ecx
loop3:
mov ebx, [GRAY_RES_ARR_256 + ecx * 4]
mov [edx + esi * 4], ebx
inc esi
mov [edx + esi * 4], ebx
inc esi
mov [edx + esi * 4], ebx
inc esi
inc ecx

cmp esi, len
je empty

cmp ecx, 8
jne loop3

cmp esi, len
jne start_loop

empty:
pop ecx
pop ebx
pop esi

ret
Grayscale_BT2100 endp

Grayscale_arithmetic proc arr: PTR DWORD, len: DWORD
mov eax, len
cmp eax, 0
jne not_empty
jmp empty

not_empty:
mov edx, DWORD ptr ds:[arr]
xor eax, eax
push esi
xor esi, esi
push ebx
xor ebx, ebx
push ecx
xor ecx, ecx
VBROADCASTSS ymm1, Quotient

start_loop:
xor ecx, ecx
mov Counter, 0
loop1:
mov ebx, [edx + esi * 4]
mov [RED_TEMP_ARR_256 + ecx * 4], ebx
inc esi

mov ebx, [edx + esi * 4]
mov [GREEN_TEMP_ARR_256 + ecx * 4], ebx
inc esi

mov ebx, [edx + esi * 4]
mov [BLUE_TEMP_ARR_256 + ecx * 4], ebx
inc esi

add Counter, 3
inc ecx
cmp esi, len
je loop2
cmp Counter, 24
jne loop1

loop2:
vmovups ymm0, ymmword ptr[RED_TEMP_ARR_256]
vaddps  ymm0, ymm0, ymmword ptr[GREEN_TEMP_ARR_256]
vaddps  ymm0, ymm0, ymmword ptr[GREEN_TEMP_ARR_256]
vdivps  ymm0, ymm0, ymm1

vroundps ymm0,ymm0, 0
vmovups ymmword ptr[GRAY_RES_ARR_256], ymm0

sub esi, Counter

xor ecx, ecx
loop3:
mov ebx, [GRAY_RES_ARR_256 + ecx * 4]
mov [edx + esi * 4], ebx
inc esi
mov [edx + esi * 4], ebx
inc esi
mov [edx + esi * 4], ebx
inc esi
inc ecx

cmp esi, len
je empty

cmp ecx, 8
jne loop3

cmp esi, len
jne start_loop

empty:
pop ecx
pop ebx
pop esi

ret
Grayscale_arithmetic endp

END DllEntry

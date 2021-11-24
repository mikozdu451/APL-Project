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
RED real8	0.2126
GREEN real8 0.7152
BLUE real8	0.0722
GREY real8 0.0
.CODE

DllEntry PROC hInstDLL:DWORD, reason:DWORD, reserved1:DWORD

mov	eax, 1 	;TRUE
ret

DllEntry ENDP

;-------------------------------------------------------------------------
; This is an example function. It's here to show
; where to put your own functions in the DLL
;-------------------------------------------------------------------------



MyProc3 proc Red: real8, Green: real8, Blue:real8

movq xmm0, Red
movq xmm1, Green
movq xmm2, Blue
movq xmm3, RED
movq xmm4, GREEN
movq xmm5, BLUE
mulpd xmm0, xmm3
mulpd xmm1, xmm4
mulpd xmm2, xmm5
addpd xmm0, xmm1
addpd xmm0, xmm2
movlpd	GREY, xmm0
fld GREY
ret

MyProc3 endp

END DllEntry
;-------------------------------------------------------------------------

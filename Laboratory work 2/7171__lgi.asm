.386
.model flat, stdcall, C
include c:/masm32/include/windows.inc
include c:/masm32/include/user32.inc
include c:/masm32/include/kernel32.inc
includelib c:/masm32/lib/user32.lib
includelib c:/masm32/lib/kernel32.lib
include c:/masm32/include/msvcrt.inc 
includelib c:/masm32/lib/msvcrt.lib 
.data
		Array 		db 		50, 2, 198, 202 
		n 			equ 	$-Array 
		MsgValue1	db 		'Value in the array: %d ', 0
		MsgValue2 	db 		' | %d <- Value after checking the conditions', 0dh, 0ah, 0  
		MsgSum	 	db		'Summa: %d', 0dh, 0ah, 0
		Summa 		db 		0 
		TemporaryValueForSum db 0 
		
.code
main:
		mov 		ebx, 	0 
@@next: 
		cmp 		ebx, 	n 
		je 			@@Exit 
		xor 		eax, 	eax 
		mov 		al, 	[Array+ebx] 
		invoke 		crt_printf, addr MsgValue1, al 
		mov 		al, 	[Array+ebx]
		test 		al, 	10000000b 
		jz 			@@sumOfTheValues 
		jnz 		@@valueIzOne 
@@valueIzOne: 
		shr			al, 	1
		jmp 		@@sumOfTheValues 
@@sumOfTheValues: 
		mov 		TemporaryValueForSum, al 
		xor			eax, 	eax 
		mov 		al, 	Summa
		add 		al, 	TemporaryValueForSum 
		mov			Summa, 	al 
		invoke		crt_printf, addr MsgValue2, TemporaryValueForSum
		inc 		ebx 
		jmp 		@@next
@@Exit: 
		invoke 		crt_printf,addr MsgSum, Summa
	end main

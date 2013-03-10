/*
Author: Jonathan Drouillard
Assignment: 6
Filename: Drouillard6_1.cpp
Date Created: 8/8/11
Description: Implement even parity setter on each character in an array.
*/

#include <iostream>
#include <string.h>

using namespace std;

void __declspec (naked) asmParity(char[], short)
{
	__asm
	{
		push ebp					;save previous location of ebp
		pushfd						;save previous flags
		mov ebp, esp				;establish stack pointer
		sub ecx, ecx				;clear strlen counter
		mov cx, WORD PTR[ebp+16]	;move strlen into counter(cx)
		jecxz DONE					;jump if array is empty
		mov edx, [ebp+12]			;load address of a array into edx
		mov ebx, 6					;bit counter to 6
		sub eax, eax				;found 1's counter to 0

StrLoop:
		cmp ebx, -1					;check if bit counter < zero
		jne CheckBits				;if still remaining bits to check, check them
		shr eax, 1					;shift bits right by 1
		jc EVENPARITY				;if last shifted bit = 1, then, even parity
		jmp NEXT					;next
EVENPARITY:
		or BYTE PTR[edx], 10000000b	;set high order bit to 1
		jmp NEXT					;continue moving pointer
NEXT:
		inc edx						;no remaining bits, move up a chunk of data.
		sub eax, eax				;found 1's counter to 0
		mov ebx, 6					;reset bit counter
		loop StrLoop				;loop through character array until strlen
		jmp DONE

CheckBits:
		bt BYTE PTR[edx], ebx		;copies ebxTH bit into CF
		jnc IsOne					;if no carry from bittest, it is a 1
		dec ebx						;decrease bit counter
		jmp StrLoop					;jump back to check if zero
IsOne:
		inc eax						;increase count of found 1's
		dec ebx						;decrease bit counter
		jmp StrLoop					;jump back to check if zero
DONE:
		mov esp, ebp		;deallocate local memory
		popfd				;restore original flags
		pop ebp				;restore value of base pointer
		ret					;return even count in ax
	}
}

int main()
{
	char *a;
	a = new char[100];

	cout << "Test with:\n"
		 << "A - 0100 0001 - even parity (set)\n"
		 << "a - 0110 0001 - odd parity (unset)\n"
		 << "s - 0111 0011 - odd parity (unset)\n"
		 << "f - 0110 0110 - even parity (set)\n"
		 << "Aasf should result in A and f being altered.\n\n"
	     << "Enter a string of characters (up to 99): \n";
	
	cin.getline(a,99);

	asmParity(a,strlen(a));
	
	cout << "Results: \n" << a << endl;

	cin.get();

	return 0;
}
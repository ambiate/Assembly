/*
Author: Jonathan Drouillard
Assignment: 6
Filename: Drouillard6_0.cpp
Date Created: 8/7/11
Description: For an array, calculate strlen and amount of even and odd numbers.
*/

#include <iostream>

using namespace std;

short __declspec (naked) asmStrLen(int[])
{
	__asm
	{
		push ebp			;save previous location of ebp
		pushfd				;save previous flags
		mov ebp, esp		;establish stack pointer
		sub cx, cx			;clear counter to 0
		mov edx, [ebp + 12]	;load address of a array into edx
		
TOP:
		cmp DWORD PTR[edx], -999	;compare value at edx to -999
		je DONE						;if equal, we have reached sentinel value
		inc cx						;increment counter if not the sentinel value
		add edx, 4					;increment pointer through the array
		jmp TOP						;test again for -999

DONE:
		mov ax, cx			;place counter in ax
		mov esp, ebp		;deallocate local memory
		popfd				;restore original flags
		pop ebp				;restore value of base pointer
		ret					;return length stored in ax
	}
}

short __declspec (naked) asmOddCount(int[], short)
{
	__asm
	{
		push ebp					;save previous location of ebp
		pushfd						;save previous flags
		mov ebp, esp				;establish stack pointer
		sub ax, ax					;clear ax to store odd count
		sub ecx, ecx				;clear high order of ecx for using loop
		mov cx, WORD PTR[ebp+16]	;copy strlen into cx counter
		jecxz DONE					;jump if array is empty
		mov edx, [ebp+12]			;load address of a array into edx
TOP:	
		shr DWORD PTR[edx], 1		;shift bits right by 1
		jc ODDYAY					;check CF = 1(ODD) from shr
		add edx, 4					;increment pointer through the array
		loop top					;not odd, try again with element in the array
		jmp DONE					;Skip ODDYAY if at end of string
ODDYAY:
		inc ax						;increase even count in ax
		add edx, 4					;increment pointer through the array
		loop top					;Continue with next element in the array
DONE:
		mov esp, ebp		;deallocate local memory
		popfd				;restore original flags
		pop ebp				;restore value of base pointer
		ret					;return even count in ax
	}
}

int main()
{
	int *a, x, i=0;
	a = new int[20];

	cout << "Prompt to ask for 20 32-bit values in an array, end with -999\n";

	while(i<20)
	{
		cin >> x;
		a[i] = x;
		if(x == -999)
			i = 19;
		i++;
	}
	
	i = asmStrLen(a);

	/*cout << "The values in the array are:\n";
	
	for(int j = 0; j < i; j++)
		cout << a[j] << '\t';
	*/
	x = asmOddCount(a, i);
	cout << "\nThere are " << x << " odd numbers in a.\n"
		 << "There are " << i-x << " even numbers in a.\n";

/*	for (int j = 0; j < asmStrLen(a); j++)
		cout << a[j] << '\t';*/


	cin.get();cin.get();cin.get();cin.get();cin.get();cin.get();cin.get();cin.get();cin.get();cin.get();

	return 0;
}
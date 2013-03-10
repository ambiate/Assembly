/*
Author: Jonathan Drouillard
Assignment: 5
Filename: Drouillard5_1.cpp
Date Created: 8/4/11
Description: Move the nth value to the beginning of the array
*/

#include <iostream>

using namespace std;

const short SIZEA=10;

void __declspec (naked) asmRelocate (short[], short)
{
	__asm
	{
		push EBP            //Save previous location of EBP
		mov  EBP, ESP       //Establish stack pointer
		sub  ECX, ECX		//Zero out ECX
		mov  CX, [EBP+12]   //Initialize counter
		cmp  CX, 1			//Compare against 1
		jle  DONE			//If < 1, already sorted
		cmp  CX, SIZEA		//Compare against 10
		jg   DONE			//If > 10, cannot perform f(x)
		mov  EAX, [EBP+8]	//Load address of array
		dec  CX				//loading to n-1
PUSHIT:
		push WORD PTR[EAX]	//Push value in array onto the stack
		add  EAX, 2			//Increment pointer through word length array
		loop PUSHIT			//Loop to top
NEXT:
		mov  EDX, [EAX]		//Store value at n element in EDX
		mov  EAX, [EBP+8]	//Back to the beginning of the array
		mov  [eax], EDX		//Move Value in EDX(n element) to beginning of array
		mov  CX, [EBP+12]	//Reinitialize the counter
		dec  CX				//reloading from n-1
		imul EDX, CX, 2		//Multiply count (n-1) by 2
		add  EAX, EDX		//Move to final element in array to be changed
POPIT:
		pop  WORD PTR[EAX]	//Retrieve value from stack and place it into array
		sub  EAX, 2			//Decrement pointer through word length array
		loop POPIT			//Loop to top
DONE:
		mov  ESP, EBP		//Deallocate local memory
		pop  EBP			//Restore value of base pointer
		ret					//Return
	}
}

int main()
{
	short list[] = { 12, 48, 56, 32, -8, 98, 112, 71, 11, 8 };
	short key;

	for(int i = 0; i < 10; i++)
		cout << list[i] << '\t';
	cout << endl;

	cout << "Enter a number 1-10: " << endl;
	cin >> key;
	asmRelocate(list, key);

	for(int i = 0; i < 10; i++)
		cout << list[i] << '\t';
	cout << endl;

	cin.get(); cin.get();
	return 0;
}
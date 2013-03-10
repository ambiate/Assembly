/*
Author: Jonathan Drouillard
Assignment: 5
Filename: Drouillard5_0.cpp
Date Created: 8/4/11
Description: Sort 3 integers in ascending order
*/

#include <iostream>

using namespace std;

void __declspec (naked) asmSortThree (int&, int&, int&)
{
	__asm
	{
		push EBP            //Save previous location of EBP
		mov  EBP, ESP        //Establish stack pointer
		
		mov  EAX, [EBP+8]	//Load address of minVal(A) into EAX
		mov  EBX, [EBP+12]	//Load address of midVal(B) into EBX
		mov  ECX, [EBP+16]	//Load address of maxVal(C) into ECX

CGREATERB:
		mov  EDX, [ECX]		//move value in maxVal(C) into EDX
		cmp  EDX, [EBX]		//Compare maxVal(C) to value in midVal(B)
		jge  BGREATERA		//If EDX(maxVal(C)) >= EBX(midVal(B)), check if midVal(B) > minVal(A)
							//ELSE C < B, so swap.
		push EAX			//Push address in EAX onto stack
		mov  EAX, [EBX]		//Place value in midVal(B) into EAX
		mov  [EBX], EDX		//Value in maxVal(C) into midVal(B)
		mov  [ECX], EAX     //Value in EAX (OLD midVal(B)) into maxVal(C)
		pop  EAX			//Restore EAX with old address from stack
		jmp  BGREATERA		//Fixed B/C scenarios, check A/B scenarios
BGREATERA:
		mov  EDX, [EBX]		//move value in midVal(B) into EDX
		cmp  EDX, [EAX]		//Compare midVal(B) to  to value in minVal(A)
		jge  DONE			//IF EDX(midVal(B)) >= EAX(minVal(A)), jump to DONE.
							//ELSE B < A, so swap, and recheck C>New B
		push ECX			//Push address in ECX onto stack
		mov  ECX, [EAX]		//Place value in minVal(A) into ECX (scratch)
		mov  [EAX], EDX		//Value in midVal(B) into EAX (minVal)
		mov  [EBX], ECX		//Value in minVal(A) into EBX (midVal)
		pop  ECX			//Restore ECX with old address from stack
		jmp  CGREATERB		//Recheck if maxVal(C) >= New midVal(B)
DONE:
		mov  ESP, EBP		//Deallocate local memory
		pop  EBP			//Restore value of base pointer
		ret					//Return
	}
}

int main()
{
	int minVal, midVal, maxVal;
	cout << "This program reads in 3 values and sorts them in ascending order."
		 << endl << "Please enter 3 values: ";
	cin >> minVal >> midVal >> maxVal;
	asmSortThree (minVal, midVal, maxVal);

	cout << "Values in ascending order are: "
		 << minVal << "," << midVal << "," << maxVal << endl;
	cin.get(); cin.get();
	return 0;
}
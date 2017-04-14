/*
	ICS 51. Lab #3

	IMPORTATNT NOTES:

	- Noramally, the compiler adds the prologue/epilogue code for the callee. However, when the 
	__declspec(naked) attribute is used, it is the programmer's responsibility to write the 
	prologue/epilogue code. In this lab you need to write prologue/epilogue code sections only 
	for the functions that have been declared with the naked attribute, namely:

	   + findMinIndex
	   + recFactorial
	   + performOperation
	   + fibonacci

	- You cannot define any local variable in the C code. If you need additional variables in your
	assembly code, you have to allocate space for them in the prologue of the function. 

	- You are not allowed to change anything in this file except for adding your assembly code 
    between the lines marked "BEGIN YOUR CODE HERE" and "END YOUR CODE HERE".

	- Remember to fill in your name, student ID below.

	- ONLY submit the lab3.c file for grading.

*/

char *yourName = "Your name";
char *yourStudentID = "Your student ID";

/***********************************************************************************************

	PART 1: Selection Sort

	Selection sort is an in-place comparison sort algorithm that works by dividing the input list 
	into two parts: the sublist of items already sorted, which is built up from left to right of 
	the list, and the sublist of items remaining to be sorted that occupy the rest of the list. 
	Initially, the sorted sublist is empty and the unsorted sublist is the entire input list. 
	The algorithm proceeds by finding the smallest element in the unsorted sublist, exchanging it 
	with the leftmost unsorted element (putting it in sorted order), and moving the sublist 
	boundaries one element to the right. To learn more, read: 
	https://en.wikipedia.org/wiki/Selection_sort#Example

	Our implementation here uses a function called "findMinIndex" to find the index of smallest
	element between ith index and jth index of the array. The function "selectionSort" uses
	this function to find the smallest number and exchanges it with the leftmost unsorted element
	in each iteration. You need to implement the behavior of both functions in x86 assembly.

************************************************************************************************/

__declspec(naked) 
int findMinIndex (int integer_array[], int i, int j)
{

// C code to be converted to x86 assembly
/*
    int iMin = i;
    // test against elements after i and before j to find the smallest 
    for ( i ; i < j; i++) {
        // if this element is less, then it is the new minimum   
        if (integer_array[i] < integer_array[iMin]) {
            // found new minimum; remember its index 
            iMin = i;
        }
    }

    return iMin;
*/

	__asm{
			// BEGIN YOUR CODE HERE



			// END YOUR CODE HERE
			ret
	}

}

void selectionSort (int integer_array[], int array_size)
{

// C code to be converted to x86 assembly
/*  
	int j;
	int iMin;
	int temp;

	// advance the position through the entire array //
	// (could do j < n-1 because single element is also min element) //
	for (j = 0; j < array_size-1; j++) {

		// find the index of min element in the unsorted a[j .. n-1] //
 		iMin = findMinIndex (integer_array, j, array_size);
 
		if(iMin != j) { // swap values
			temp = integer_array[iMin];
			integer_array[iMin] = integer_array [j];
			integer_array[j] = temp;	
		}
	}
*/

	__asm{
			// BEGIN YOUR CODE HERE



			// END YOUR CODE HERE
	}

}

/***********************************************************************************************

    PART 2: Recursive Factorial

	Implement two functions that calculates the factorial of an integer not greater than 12.

	The 1st function, factorial (unsigned int input, unsigned int *output), is the non 
	recursive wrapper function which takes the input, sets up the stack, calls the recursive 
	function and finally puts the result in the location pointed to by the pointer argument called
    output.

	The 2nd function, recFactorial(unsigned int n), is the recursive function that actually 
	calculates the factorial.

	Given an unsigned integer number n,we define FACTORIAL(n) as:

        FACTORIAL(n) =  1                   ,    if n = 0 or n = 1
                        n * FACTORIAL(n-1)  ,    if n > 1
		
	Tip:
		
	- You need to use IMUL instruction to multiply unsigned integers. Learn how to use it:
	http://www.cs.virginia.edu/~evans/cs216/guides/x86.html#instructions

************************************************************************************************/

__declspec(naked) 
unsigned int recFactorial (unsigned int n)
{

// C code to be converted to x86 assembly
/*
	if (n<=1) 
		return 1;
	else 
		return n * recFactorial(n-1); 
*/

	__asm{
			// BEGIN YOUR CODE HERE
            push ebp
            mov ebp, esp
        
            //IF STMT
            cmp dword[ebp+8], 1
            jg Recursion
            mov eax, 1
            jmp Exit
    Recursion:
            push eax
            push ebx
            push edx
        
        

			// END YOUR CODE HERE
			ret
	}

}

void factorial (unsigned int input, unsigned int *output)
{

// C code to be converted to x86 assembly
/*
	*output = recFactorial (input);
*/

	__asm{
			// BEGIN YOUR CODE HERE
            push eax
            mov eax, input
        
            push eax
            call recFactorial
            pop eax
        
            // END YOUR CODE HERE
	}

}

/***********************************************************************************************

    PART 3: Vector Operation

	The vectorOperations function gets as parameters 4 arrays of the same length and
	the number of elements in those arrays. 

	For each pair of elements in first_array and second_array, it calls performOperation
	and stores the returned result in the same index of output_array.

	output_array[index] = performOperation(operation_array[index], first_array[index], second_array[index]).

	You also need to implement the body of performOperation function according to the provided
	C code.
  
************************************************************************************************/

__declspec(naked) 
int performOperation (int operation, int first, int second)
{

// C code to be converted to x86 assembly
/*
	if (operation==0) 
		return first + second;
	else if (operation==1)
		return first - second;
	else if (operation==2)
		return (first > second)? first : second;  returns whichever is grater
	else if (operation==3)
		return (first < second)? first : second; returns whichever is lower
	else
		return first;
*/

	__asm {
			// BEGIN YOUR CODE HERE
            push ebp
            mov ebp, esp
        
            push edi
            push esi
            push ebx
        
            push eax, [ebp+8]
            push edx, [ebp+12]
            push ecx, [ebp+16]
        
            cmp eax, 0
            je Addition
            cmp eax, 1
            je Subtraction
            cmp eax, 2
            je greaterThan
            //otherwise see if it's less than
            cmp edx, ecx
            jg LessThan
            mov eax, edx
    LessThan:
        mov eax, ecx
        
    Addition:
        add edx, ecx
        mov eax, ecx
        
    Subtraction:
        sub edx, ecx
        mov eax, edx
        
    greaterThan:
        cmp edx, ecx
        jl otherGT
        mov eax, ecx
    
    otherGT:
        mov eax, ecx
        
    Exit:
        pop ecx
        pop edx
        pop eax
        pop ebx
        pop esi
        pop edi
        
        mov esp, ebp;
        pop ebp;
        
        
        
        
        
        
        
        ///
        
        push ebp;
        mov ebp, esp;
        
        sub esp, 4;
        
        mov ebx, [ebp + 8];
        mov ecx, [ebp + 12];
        mov edx, [ebp + 16];
        
        cmp ebx, 0;
        jne IF_2;
        
        mov[ebp - 4], ecx;
        add [ebp - 4], edx;
        mov eax, [ebp - 4];
        jmp CONTINUE;
    IF_2:
        cmp ebx, 1;
        jne IF_3;
        
        mov[ebp - 4], ecx;
        sub[ebp - 4], edx;
        mov eax, [ebp - 4];
        jmp CONTINUE;
    IF_3:
        cmp ebx, 2;
        jne IF_4;
        
        cmp ecx, edx;
        jle IF_3_B;
        
        mov eax, ecx;
        jmp CONTINUE;
    IF_3_B:
        mov eax, edx;
        jmp CONTINUE;
    IF_4:
        cmp ebx, 3;
        jne ELSE;
        
        cmp ecx, edx;
        jge IF_4_B;
        
        mov eax, ecx;
        jmp CONTINUE;
    IF_4_B:
        mov eax, edx;
        jmp CONTINUE;
    ELSE:
        mov eax, ecx;
    CONTINUE:
        mov esp, ebp;
        
        pop ebp;
        ///
        
			// END YOUR CODE HERE
			ret
	}
  
}

void vectorOperations (int number_of_elements, int *first_array, int *second_array, 
					   int *operation_array, int *output_array)
{
// C code to be converted to x86 assembly
/*
	int i;
	for (i=0; i<number_of_elements; i++)
	{
		output_array[i] = performOperation(operation_array[i], first_array[i], second_array[i]);
	}
*/

	__asm {
			// BEGIN YOUR CODE HERE
            mov eax, output_array
            mov ebx, 0
    
    StartLoop:
            cmp ebx, number_of_elements
            jge Exit
        
            push eax
            push ecx
            push edx
        
            mov edi, operation_array;
            mov edi, [edi + 4*esi];
            mov edx, first_array;
            mov edx, [edx + 4*esi]
            mov ecx, second_array;
            mov ecx, [ecx + 4*esi];
        
            push edi
            push ecx
            push edx
        
            call performOperation
            add esp, 12
            mov [eax + 4 * ebx], eax
            pop edx
            pop ecx
            pop eax
        
            jmp IncCounter
        
        
    IncCounter:
        inc ebx
        jmp StartLoop
        
    Exit:
        mov output_array, eax
        

			// END YOUR CODE HERE
	}
}

/***********************************************************************************************

    PART 4: Change Letter Case

	You are given an array of characters (a string) that may contain numbers, upper and	lower case 
    letters, punctuations symbols, etc. Implement a function to convert all uppercase letters to 
    lowercase and vice versa. 
    For example "ThisIsTheFinalLabOf51" should be converted to "tHISiStHEfINALlABoF51". 
	The function has the following argument: An array of charaters and the size of the array. The 
	array should be changed in place. There is no explicit output for this function.

	Tips:

	- Note that each element of the arrays is a char (1 byte). You can NOT use a 32-bit register 
	to read/write from/to a memory location. Instead you should use the 8-bit version of the x86
	general-purpose registers. 
	More info: http://www.cs.virginia.edu/~evans/cs216/guides/x86.html#registers

	- The link to the ascii codes is here: http://www.asciitable.com/

************************************************************************************************/

void changeCase (char char_array[], int array_size ) {

	__asm{
			// BEGIN YOUR CODE HERE
            mov eax, char_array
            mov edi, 0
    
        StartLoop:
            cmp edi, array_size
            jge Exit
            mov bl, [eax + edi]
            //check for upper case where bl is between 65-90
            cmp bl, 65
            jl IncCounter
            cmp bl, 90
            jg checkLowerCase
            add bl, 32
            mov [eax + edi], bl
            jmp IncCounter
        //check for lower case where bl is btwn 97-122
        checkLowerCase:
            cmp bl, 97
            jl IncCounter
            cmp bl, 122
            jg IncCounter
            sub bl, 32
            mov [eax + edi], bl
        
        IncCounter:
            inc edi
            jmp StartLoop
    
        Exit:
            mov char_array, eax

			// END YOUR CODE HERE
	}
}

/***********************************************************************************************

    PART 5: Fibonacci

	Implement a recursive function in assembly which returns the Nth number in the fibbonaci
	series (1, 1, 2, 3, 5, 8, ...).

************************************************************************************************/

__declspec(naked) 
unsigned int fibonacci (unsigned int n) {

// C code to be converted to x86 assembly
/*
	if (n < 2) 
		return 1;
	else 
		return fibonacci(n - 1) + fibonacci(n - 2);
*/

	__asm{
			// BEGIN YOUR CODE HERE
        push ebp;
        mov ebp, esp;
        push edi;
        push esi;
        push ebx;
        
        mov ebx, [ebp + 8];
        cmp ebx, 2;
        jae RECURSIVE;
        
        mov eax, 1;
        jmp END;
    RECURSIVE:
        push eax;
        push ecx;
        
        mov ecx, ebx;
        dec ecx;
        
        push ecx;
        
        call fibonacci;
        
        add esp, 4;
        
        mov esi, eax;
        
        mov ecx, ebx;
        sub ecx, 2;
        
        push ecx;
        
        call fibonacci;
        
        add esp, 4;
        
        mov edi, eax;
        
        pop ecx;
        pop eax;
        
        mov eax, esi;
        add eax, edi;
        
    END:
        pop ebx;
        pop esi;
        pop edi;
        
        mov esp, ebp;
        pop ebp;



			// END YOUR CODE HERE
			ret
	}
}






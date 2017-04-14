//
//	ICS 51, Lab #2
//
//	-----------------------------------------------------------------
// 
//	IMPORTATNT NOTES:
//	
//	- To test your code use the tests in lab2-testing.cpp
//	
//	- Write your assembly code only in the marked blocks.
//	
//	- Do NOT change anything outside the marked blocks.
//
//	- Remember to fill in your name, student ID below.
// 
//	- This lab has to be done individually.
//
//  - Use lodepng.h and lodepng.cpp to read/write png files.
//
//  - Two test images are provided to you.
//	
//	- Submit ONLY lab2.cpp file for grading.
// 


char *yourName = "brookedl";
char *yourStudentID = "33256705";


//
// This function should takes in a square sized grayscale image and applies thresholding on each pixel.
// Width and height of the image are equal to dim.
// NOTE: you can't define additional variables.
//
void imageThresholding(unsigned char* image, int dim) {
	
	__asm {
    
// YOUR CODE STARTS HERE
		
        mov eax, image
        mov ebx, 0
        mov ecx, 0
        mov esi, 0
        
    ComputeDim:
        cmp ebx, dim
        jge ExitLabel
        shl dim, 1  //Figures out the size of dim I DONT THINK ITD BE SHL BUT ADD
        inc ebx, 1
        jmp StartComparison
    
        
    StartComparison:
        mov ebx, 0
        cmp ebx, dim
        jge EndLoop
        mov edi, [eax(4*esi)]
        cmp edi, 0x80
        jge ChangeWhite
        and edi, 0xA000
        mov [eax($*esi)], edi
        inc esi, 1
        jmp StartComparison
        
    ChangeWhite:
        or edi, 0xFFFF
        mov [eax(4*esi)], edi
        inc esi
        jmp StartComparison
    
    Endloop:
        mov image, eax
        
    ExitLabel:
        //terminate 
        
// YOUR CODE ENDS HERE
	
  }
}



// This function flips an square iamge of given dimension horizontally/vertically.
// Width and height of the image are equal to dim.
// if direction is 0, image should be flipped horizontally
// otherwise image should be flipped vertically.
//
// Two variables are defined to help you with implemetanion.
// NOTE: you can't define additional variables.
//
void imageFlip(unsigned int* image, int dim, int direction) {
  
  unsigned int a_p, a_p_m;
  
  __asm {
    
// YOUR CODE STARTS HERE
      mov eax, image
      mov ebx, 0    //interchange-able to row and column
      mov edx, dim
      mov esi, 0
      mov edi, dim
      shr edi, 1
//      div edi, 2

      
  VorH:
      cmp direction, 0
      je BeginRow
      jmp BeginColH
      
  BeginRow:
      cmp ebx, edx
      jge Exit
      //mov ecx, 0
      jmp LoopCol
      
  LoopCol:
      mov ecx, 0
      cmp ecx, edi //ie: if dim = 5, ecx is only col 1 and 2
      jge NextRow
    //starting the computation of __ row and __ column
      mov esi, dim //(dim - 1 - col_index)
      sub esi, 1
      sub esi, ecx
      
      cmp ecx, esi
      je NextRow
      
      mov a_p, ebx
      mov edx, dim
      mul edx
      //mul a_p, edx
      add a_p, ecx
      shl a_p, 2
      add a_p, eax
      //mov dl, [eax+a_p]
      
      mov a_p_m, ebx
      mov edx, dim
      mul edx
      //mul a_p_m, edx
      add a_p_m, esi
      shl a_p_m, 2
      add a_p_m, eax
      //mov cl, [eax + a_p_m]
      mov [eax + a_p], cl
      mov [eax + a_p_m], dl
      inc ecx
      jmp LoopCol
      
  NextRow:
      inc ebx
      jmp BeginRow
    
  Exit:
      mov image, eax
// YOUR CODE ENDS HERE
  
  }
  
}










// YOUR CODE STARTS HERE
mov eax, image
mov ebx, 0  //ROW
mov ecx, 0 //COL
mov edx, dim
mov esi, 0
mov edi, dim
shr edi, 1
jmp VorH

VorH:
    mov edx, direction
    cmp edx, 0
    je BeginRow
    jmp Exit //FIX TO OTHER CASE WHICH IS FLIP V

BeginRow:

    cmp ebx, edx
    jge Exit
    jmp LoopCol

LoopCol:
    //wouldnt want to declare a ecx, 0 here because then every time it reloops 0 will start as the init value
    cmp ecx, edi
    jge NextRow
    //starting the computation of respective row and col
    mov esi, dim
    sub esi, 1
    sub esi, ecx //this will always get the right (mirrored) column

    cmp ecx, esi
    je NextRow

    //calculation of current address
    mov a_p, ebx
    mov edx, dim
    mul edx
    add a_p, ecx
    shl a_p, 2
    add a_p, eax

    //calculation of mirrored pixel
    mov a_p_m, ebx
    mov edx, dim
    mul edx
    add a_p_m, esi
    shl a_p_m, 2
    add a_p_m, eax

    //Swap current and mirrored pixel

    /*mov esi, [a_p]
     mov edx, [a_p_m]
     mov [a_p_m], esi
     mov [a_p], edx */

    //increment the column counter and loop again
    inc ecx
    jmp LoopCol

NextRow:
    inc ebx
    //i think here ECX should be reset to 0
    jmp BeginRow

Exit:
    mov image, eax


//might be a problem with the column looping where it constantly adds







mov eax, image
mov edi, 0

BEGIN_FOR_ROW:

cmp edi, dim

jge END_FOR_ROW

mov esi, 0




BEGIN_FOR_COL:

cmp esi, dim

jge END_FOR_COL

mov ebx, 0 //Transfer row to ebx




mov edx, 0 //Multiply row by dim (add row to row dim times)

BEGIN_FOR_MUL:

cmp edx, dim

jge END_FOR_MUL

add ebx, edi

inc edx

jmp BEGIN_FOR_MUL

END_FOR_MUL:




add ebx, esi

xor edx, edx

mov dl, [eax + ebx]

mov cl, 0x80

and cl, dl

cmp cl, 0x00

jne IF_HIGHER

xor edx, edx //set to Min

jmp CONT

IF_HIGHER:

or edx, 0xFFFFFFFF

CONT:

mov [eax + ebx], dl

inc esi

jmp BEGIN_FOR_COL




END_FOR_COL:

inc edi

jmp BEGIN_FOR_ROW




END_FOR_ROW:

mov image, eax


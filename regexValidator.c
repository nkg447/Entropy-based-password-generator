
/*
* A header file to validate a regex using stack in C language
*/

#include <stdio.h>
#include "stack.c"

/*
* A function to check if the first character passed is
  the same kind of bracket as the second character
* Requires Parameter - two characters
* Returns -1 - are not matching
		   1 - are matching
*/
int areMatchingBrackets(char ch1,char ch2){
	if(ch1=='{' && ch2!='}')
		return -1;
	if(ch1=='(' && ch2!=')')
		return -1;
	if(ch1=='[' && ch2!=']')
		return -1;
	return 1;
	
}

/*
* A function to check the validity of the regex on 
  the basis of the structure of the brackets used in the regex
* Requires Parameter - pointer to the character array
* Returns -1 - is not valid
		   1 - is valid
*/
int isValidRegex(char * regex){
	int i=0;
	char currentChar,poppedChar;
	Stack stack;
	init(&stack);
	while(regex[i]!='\0'){
		currentChar=regex[i];

		if(currentChar=='(' || currentChar=='[' || currentChar=='{'){
			push(&stack,currentChar);
			//printf("pushed - %c\n",currentChar);
		}
		else if(currentChar==')' || currentChar==']' || currentChar=='}'){
			//printf("size %d\n",stack.top);
			if(isEmpty(&stack)==1)
				return -1;
				
			poppedChar=pop(&stack);
			//printf("poped - %c\n",poppedChar);
			if(areMatchingBrackets(poppedChar,currentChar)!=1)
				return -1;
		}
		i++;
	}
	if(isEmpty(&stack)!=1)
		return -1;
	
	return 1;
}

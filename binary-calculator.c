/*
Jack Bjelland
jbjella
ECE2220
Spring 2020
Assignment 1

Purpose: The purpose of this program is to add, subtract, divide, or multiply
binary inputs.

Assumptions:
1. The user will enter something similar to the format. If the user enters
numbers in any other base than base 2, the program will remind them.
2. If the user makes an error the program will warn them, disregard their input,
and continue instead of exiting.

Known Bugs:
The base change formula does not work with larger numbers (30 or 31 bits)
*/

#include<stdio.h>
#include<string.h>

//Function Prototype
long long baseChange(long long num,long long newBase,long long oldBase);

void mathOperation(long long operand1,long long operand2,int operator,int
	endCondition,char *number1,char *number2);

int isValid(char *entry,int quit);

//Main Function
int main(void){
	printf("Please enter binary numbers no larger than 31 bits.\n");
	int quit=0;
	while(quit==0){
		printf("Please enter [BINARY NUMBER] [OPERATOR] [BINARY NUMBER]:  ");
		int check=0,call=0;
		long long num1=0,num2=0;
		char operator,input[64],num1string[32],num2string[32];

		//Input the string so it can be manipulated without reentry
		scanf(" %[^\n]s",input);

		//Check string and input numbers as decimal or exit loop
		sscanf(input,"%s %c %s",num1string,&operator,num2string);

		if(!(strcmp(input,"quit"))){
			quit=1;
			call=1; //Call is used to supress the mathOperation function.
		}

		check+=isValid(num1string,quit);
		check+=isValid(num2string,quit);

		if(check!=0){
			call=1;
		}

		sscanf(input,"%lli %c %lli",&num1,&operator,&num2);

		//Convert Binary to Decimal
		num1=baseChange(num1,2,10);
		num2=baseChange(num2,2,10);

		//Determine operator and complete operation
		mathOperation(num1,num2,operator,call,num1string,num2string);

	}
	printf("Good bye.\n");
	return 0;
}
////FUNCTIONS/////////////////////////////////////////////////////////////////

/*Base Change Function
The base change function inputs the number, the current base, and the desired
base. The function takes the modulo of the number and multiplies the remainder
and the old base. This is added to output, which is a running total that gives
the total value in the new base.
*/
long long baseChange(long long num,long long oldBase,long long newBase){
	long long output=0,remain=0,base=1;
	while(num>0){
		remain=num%newBase;
		output=output+remain*base;
		num=num/newBase;
		base=base*oldBase;
	}
	return(output);
}

/*Math Operation Function
This function does the proper arithmetic based on the ASCII value of the
operator character. The multiplication section checks if the either operand
exceeds 16 characters. The division section checks to make sure the user does
not try to divide be zero. The endCondition constraint supresses the output
in the case of a 'quit' condition or an error.
*/
void mathOperation(long long operand1,long long operand2,int operator,int
	endCondition,char * number1,char *number2){
	long long answer,final,remainder;
	if(endCondition==0){
			if(operator==42||operator==120){
				if(strlen(number1)>16||strlen(number2)>16){
					printf("One of your operands is too long. Please try again.\n");
				}
				else{
					answer=operand1*operand2;
					final=baseChange(answer,10,2);
					printf("= %lli\n",final);
				}
			}
			else if(operator==47){
				if(operand2==0){
					printf("Cannot divide by zero. Please enter again.\n");
				}
				else{
					answer=operand1/operand2;
					final=baseChange(answer,10,2);
					remainder=baseChange(operand1%operand2,10,2);
					printf("= %lli R %lli\n",final,remainder);
				}
			}
			else if(operator==43){
				answer=operand1+operand2;
				final=baseChange(answer,10,2);
				printf("= %lli\n",final);
			}
			else if(operator==45){
				answer=operand1-operand2;
				final=baseChange(answer,10,2);
				printf("= %lli\n",final);
			}
			else{
				printf("Invalid Operator. Please check and reenter.\n");
			}
	}
}

/*Checking Validity Function
This function checks if the input string (entry) fulfills the constraints
of the program. It checks for length, and also checks if the number is
written in a base 2 format.
*/
int isValid(char *entry,int quit){
	int valid=0;
	if(quit==0){
		int i=0;
		if(strlen(entry)>31){
			printf("One of your operands is too long. Please try again.\n");
			valid=1;
		}
		for(i=0;i<strlen(entry);i++){
			if(entry[i]!=49&&entry[i]!=48){
				printf(" %i! Please be sure to enter binary numbers only.\n",entry[i]);
				valid=1;
			}
		}
	}
	return(valid);
}

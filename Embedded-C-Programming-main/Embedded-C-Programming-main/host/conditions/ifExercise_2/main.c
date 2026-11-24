#include <stdio.h>
#include <stdint.h>

void waitForUserInput(void);

int main(){
	float num1, num2;

	printf("Enter first number(integer): ");
	if(scanf("%f", &num1) == 0){
		printf("\nInvalid input!\nExiting...");
		waitForUserInput();
		return 0;
	}

	printf("Enter second number(integer): ");
	if(scanf("%f", &num2) == 0){
		printf("\nInvalid input!\nExiting...");
		waitForUserInput();
		return 0;
	}

	// Storing only integer part of real numbers.
	int32_t n1 = num1, n2 = num2;

	if((n1 != num1) || (n2 != num2))
		printf("\nWarning, comparing only integer part!\n");

	if(n1 > n2)
		printf("\n%d is bigger.\n", n1);
	else if(n2 > n1)
		printf("\n%d is bigger.\n", n2);
	else
		printf("\nBoth numbers are equal!\n");

	waitForUserInput();

	return 0;
}

void waitForUserInput(void){
	printf("\nPress enter key to exit the application... ");
	while(getchar() != '\n'){}
	getchar();
}

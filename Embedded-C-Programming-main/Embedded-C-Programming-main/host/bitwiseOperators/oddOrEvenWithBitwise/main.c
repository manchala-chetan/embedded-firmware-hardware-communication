#include <stdio.h>
#include <stdint.h>

void waitForUserInput(void);

int main(){
	int32_t number;

	printf("----- Odd or Even Number with Bitwise AND(\'&\') Operator -----\n");

	printf("Enter number: ");
	if(scanf("%d", &number) != 1){
		printf("Invalid input!\nExiting...");
		waitForUserInput();
		return 0;
	}

	if(number & 1)
		printf("\nNumber is Odd.\n");
	else
		printf("\nNumber is Even.\n");

	waitForUserInput();

	return 0;
}

void waitForUserInput(void){
	printf("\nPress enter key to exit the application... ");
	while(getchar() != '\n'){}
	getchar();
}

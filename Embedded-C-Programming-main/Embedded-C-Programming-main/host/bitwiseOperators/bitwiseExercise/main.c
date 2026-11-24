#include <stdio.h>
#include <stdint.h>

void waitForUserInput(void);

int main(){
	int32_t a, b;

	printf("----- Bitwise operators(&, |, ^, ~) Calculator -----\n");

	printf("\nEnter first(A) integer number: ");
	if(scanf("%d", &a) != 1){
		printf("Invalid input!\nExiting...");
		waitForUserInput();
		return 0;
	}

	printf("Enter second(B) integer number: ");
	if(scanf("%d", &b) != 1){
		printf("Invalid input!\nExiting...");
		waitForUserInput();
		return 0;
	}

	printf("\n--- Results ---\n");

	printf("- AND(&): %d\n", (a & b));
	printf("- OR(|): %d\n", (a | b));
	printf("- XOR(^): %d\n", (a ^ b));
	printf("- NOT(~) First(A) number: %d\n", (~a));
	printf("- NOT(~) Second(B) number: %d\n", (~b));

	waitForUserInput();

	return 0;
}

void waitForUserInput(void){
	printf("\nPress enter key to exit the application... ");
	while(getchar() != '\n'){}
	getchar();
}

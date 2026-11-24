#include <stdio.h>
#include <stdint.h>

void waitForUserInput(void);

int main(){
	int32_t number;

	printf("----- Bit Clearing for 4th, 5th and 6th-bit position of a number -----\n");

	printf("Enter number: ");
	if(scanf("%d", &number) != 1){
		printf("Invalid input!\nExiting...");
		waitForUserInput();
		return 0;
	}

	printf("\n--- Result ---\n");
	printf("Input: 0x%x\n", number);
	printf("Output: 0x%x\n", (number & 0x8f)); // also can use (number & ~(0x70)))

	waitForUserInput();

	return 0;
}

void waitForUserInput(void){
	printf("\nPress enter key to exit the application... ");
	while(getchar() != '\n'){}
	getchar();
}

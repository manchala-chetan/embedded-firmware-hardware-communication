#include <stdio.h>
#include <stdint.h>

void waitForUserInput(void);

int main(){
	int32_t startNumber, endNumber;
	uint32_t counter = 0;

	printf("Enter Start and End number in one line with space: ");
	if(scanf("%d %d", &startNumber, &endNumber) != 2){
		printf("Invalid input!\nExiting...");
		waitForUserInput();
		return 0;
	}

	if(startNumber >= endNumber){
		printf("End number should be greater than Start number!\nExiting...");
		waitForUserInput();
		return 0;
	}

	printf("\nEven numbers between %d to %d:\n", startNumber, endNumber);

	for(; startNumber <= endNumber; startNumber++){
		if(!(startNumber & 1)){
			printf("%4d\t", startNumber);
			counter++;
		}
	}

	printf("\n\nNumber of even numbers found: %d\n", counter);

	waitForUserInput();

	return 0;
}

void waitForUserInput(void){
	printf("\nPress enter key to exit the application... ");
	while(getchar() != '\n'){}
	getchar();
}

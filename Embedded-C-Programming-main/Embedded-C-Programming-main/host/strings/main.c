#include <stdio.h>
#include <stdint.h>

void waitForUserInput(void);

int main(){
	uint8_t name[30];

	printf("Enter your name: ");
	scanf("%[^\n]s", name);

	printf("\nWhat's up %s?\n", name);

	waitForUserInput();

	return 0;
}

void waitForUserInput(void){
	printf("\nPress enter key to exit the application... ");
	while(getchar() != '\n'){}
	getchar();
}

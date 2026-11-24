#include <stdio.h>
#include <stdint.h>

void waitForUserInput(void);

int main(){
	int32_t pyramidHeight;

	printf("Enter height of pyramid: ");
	if(scanf("%u", &pyramidHeight) != 1){
		printf("Invalid input!\nExiting...");
		waitForUserInput();
		return 0;
	}

	if(pyramidHeight <= 0){
		printf("Pyramid's height should be greater than zero!\nExiting...");
		waitForUserInput();
		return 0;
	}

	for(uint32_t i = 1; i <= pyramidHeight; i++){
		for(uint32_t j = i; j > 0; j--){
			printf("%3u", j);
		}

		printf("\n");
	}

	waitForUserInput();

	return 0;
}

void waitForUserInput(void){
	printf("\nPress enter key to exit the application... ");
	while(getchar() != '\n'){}
	getchar();
}

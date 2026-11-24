#include <stdio.h>
#include <stdint.h>
#include "areaCalculator.h"

void waitForUserInput(void);

int main(){
	char figureCode;

	printf("----- Area Calculation Program -----\n");
	printf("\nGeometrical figures codes:\n");
	printf("- triangle: \'t\'\n- trapezoid: \'z\'\n- circle: \'c\'\n- square: \'s\'\n- rectangle: \'r\'\n");

	printf("\nEnter the figure code(t, z, c, s, r): ");
	if(scanf(" %c", &figureCode) != 1){
		printf("Invalid input!\nExiting...");
		return 0;
	}

	switch (figureCode) {
		case 't':
			calculateTriangleArea();
			break;

		case 'z':
			calculateTrapezoidArea();
			break;

		case 'c':
			calculateCircleArea();
			break;

		case 's':
			calculateSquareArea();
			break;

		case 'r':
			calculateRectangleArea();
			break;

		default:
			printf("Invalid input!\nExiting...");
			break;
	}

	waitForUserInput();

	return 0;
}

void waitForUserInput(void){
	printf("\nPress enter key to exit the application... ");
	while(getchar() != '\n'){}
	getchar();
}

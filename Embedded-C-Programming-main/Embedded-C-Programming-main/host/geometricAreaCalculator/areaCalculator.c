#include <stdio.h>
#include <stdint.h>

/* Functions Implementation */
void calculateTriangleArea(void){
	double base, height, area;

	printf("\nEnter the base of the triangle: ");
	if(scanf("%lf", &base) != 1){
		printf("\nInvalid input!\nExiting...");
		return;
	}

	if(base <= 0){
		printf("\nBase must be greater than zero!\nExiting...");
		return;
	}

	printf("Enter the height of the triangle: ");
	if(scanf("%lf", &height) != 1){
		printf("\nInvalid input!\nExiting...");
		return;
	}

	if(height <= 0){
		printf("\nHeight must be greater than zero!\nExiting...");
		return;
	}

	area = (base * height) / 2;

	printf("\nArea of the triangle: %.2f\n", area);
}

void calculateTrapezoidArea(void){
	double base1, base2, height, area;

	printf("\nEnter the first base of the trapezoid: ");
	if(scanf("%lf", &base1) != 1){
		printf("\nInvalid input!\nExiting...");
		return;
	}

	if(base1 <= 0){
		printf("\nBase must be greater than zero!\nExiting...");
		return;
	}

	printf("Enter the second base of the trapezoid: ");
	if(scanf("%lf", &base2) != 1){
		printf("\nInvalid input!\nExiting...");
		return;
	}

	if(base2 <= 0){
		printf("\nBase must be greater than zero!\nExiting...");
		return;
	}

	printf("Enter the height of the trapezoid: ");
	if(scanf("%lf", &height) != 1){
		printf("\nInvalid input!\nExiting...");
		return;
	}

	if(height <= 0){
		printf("\nHeight must be greater than zero!\nExiting...");
		return;
	}

	area = ((base1 + base2) * height) / 2;

	printf("\nArea of the trapezoid: %.2f\n", area);
}

void calculateCircleArea(void){
	double radius, area;
	const double PI = 3.14159;

	printf("\nEnter the radius of the circle: ");
	if(scanf("%lf", &radius) != 1){
		printf("\nInvalid input!\nExiting...");
		return;
	}

	if(radius <= 0){
		printf("\nRadius must be greater than zero!\nExiting...");
		return;
	}

	area = PI * radius * radius;

	printf("\nArea of the circle: %.2f\n", area);
}

void calculateSquareArea(void){
	double sideLength, area;

	printf("\nEnter the side length of the circle: ");
	if(scanf("%lf", &sideLength) != 1){
		printf("\nInvalid input!\nExiting...");
		return;
	}

	if(sideLength <= 0){
		printf("\nSide length must be greater than zero!\nExiting...");
		return;
	}

	area = sideLength * sideLength;

	printf("\nArea of the square: %.2f\n", area);
}

void calculateRectangleArea(void){
	double length, width, area;

	printf("\nEnter the length of the rectangle: ");
	if(scanf("%lf", &length) != 1){
		printf("\nInvalid input!\nExiting...");
		return;
	}

	if(length <= 0){
		printf("\nLength must be greater than zero!\nExiting...");
		return;
	}

	printf("\nEnter the width of the rectangle: ");
	if(scanf("%lf", &width) != 1){
		printf("\nInvalid input!\nExiting...");
		return;
	}

	if(width <= 0){
		printf("\nWidth must be greater than zero!\nExiting...");
		return;
	}

	area = length * width;

	printf("\nArea of the rectangle: %.2f\n", area);
}

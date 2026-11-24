#include <stdio.h>
#include <stdint.h>

typedef struct {
	uint32_t id;
	uint32_t price;
	uint16_t speed;
	float weight;
} Car_t;

void waitForUserInput(void);

void printCarData(Car_t *car);

int main() {
	Car_t BMW_M5 = { 2021, 15000, 220, 1330 };
	Car_t BenzAMG = { 4031, 35000, 160, 1900.96 };

	printf("\n--- BMW M5 ---\n");
	printCarData(&BMW_M5);

	printf("\n--- Benz AMG ---\n");
	printCarData(&BenzAMG);

	waitForUserInput();

	return 0;
}

void waitForUserInput(void) {
	printf("\nPress enter key to exit the application... ");
	while (getchar() != '\n') {}
	getchar();
}

void printCarData(Car_t *car){
	printf("id: %u\n", car->id);
	printf("price: %u\n", car->price);
	printf("speed: %u\n", car->speed);
	printf("weight: %f\n\n", car->weight);
}

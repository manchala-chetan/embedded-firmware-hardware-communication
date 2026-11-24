#include <stdio.h>
#include <stdint.h>

void waitForUserInput(void);

// Without typedef
/*
struct Car {
	uint32_t id;
	uint32_t price;
	uint16_t speed;
	float weight;
};
*/

// With typedef
typedef struct {
	uint32_t id;
	uint32_t price;
	uint16_t speed;
	float weight;
} Car_t;

int main(){
	// Without typedef
	/*
	struct Car BMW_M5 = {2021, 15000, 220, 1330};
	struct Car BenzAMG = {4031, 35000, 160, 1900.96};
	*/

	// With typedef
	Car_t BMW_M5 = {2021, 15000, 220, 1330};
	Car_t BenzAMG = {4031, 35000, 160, 1900.96};

	printf("--- BMW_M5 ---\nid: %u, price: %u, speed: %u, weight: %f\n", BMW_M5.id, BMW_M5.price, BMW_M5.speed, BMW_M5. weight);
	printf("\n--- BenzAMG ---\nid: %u, price: %u, speed: %u, weight: %f\n", BenzAMG.id, BenzAMG.price, BenzAMG.speed, BenzAMG. weight);

	// printf("Size of struct Car: %I64u", sizeof(struct Car));

	waitForUserInput();
}

void waitForUserInput(void){
	printf("\nPress enter key to exit the application... ");
	while(getchar() != '\n'){}
	getchar();
}

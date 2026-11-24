#include <stdio.h>

int main(){
	float floatNumber = 43.514556255554515451815;
	printf("Float Number: %f\n", floatNumber);
	printf("Scientific Float Number: %e\n", floatNumber);

	double doubleNumber = 43.514556255554515451815;
	printf("Double Number: %0.14lf\n", doubleNumber);
	printf("Scientific Double Number: %le\n", doubleNumber);

	/*-----------------------------------------------------------*/

	double electronCharge = -1.60217662e-19; // -1.60217662 * 10-19
	printf("Charge of Electron: %0.8lf\n", electronCharge);
	printf("Charge of Electron(scientific): %0.8le\n", electronCharge);

	return 0;
}

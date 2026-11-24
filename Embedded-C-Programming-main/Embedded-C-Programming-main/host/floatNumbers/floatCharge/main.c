#include <stdio.h>

int main(){
	double charge, electronCharge, electrons;

	printf("Enter the charge: ");
	scanf("%lf", &charge);

	printf("Enter the charge of an electron: ");
	scanf("%le", &electronCharge);

	electrons = (charge / electronCharge) * -1;

	printf("\nTotal number of electrons: %lf\n", electrons);
	printf("Total number of electrons(scientific): %le\n", electrons);

	printf("\nPress enter key to exit the application... ");
	while(getchar() != '\n'){}
	getchar();

	return 0;
}

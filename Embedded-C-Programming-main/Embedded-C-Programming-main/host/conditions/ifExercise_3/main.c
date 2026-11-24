#include <stdio.h>
#include  <stdint.h>

void waitForUserInput(void);

int main(){
	uint64_t income, payableTax;
	double tempIncome;

	printf("Enter your total income: ");
	if(scanf("%lf", &tempIncome) == 0){
		printf("\nInvalid input!\nExiting...");
		waitForUserInput();
		return 0;
	}

	if(tempIncome < 0){
		printf("\nIncome cannot be negative!\nExiting...");
		waitForUserInput();
		return 0;
	}

	income = (uint64_t)tempIncome;

	if(income <= 9525)
		payableTax = 0;
	else if((income > 9525) && (income <= 38700))
		payableTax = income * 0.12;
	else if((income > 38700) && (income <= 82500))
		payableTax = income * 0.22;
	else if(income > 82500)
		payableTax = (income * 0.32) + 1000;

	printf("Payable Tax: $%llu\n", payableTax);

	waitForUserInput();

	return 0;
}

void waitForUserInput(void){
	printf("\nPress enter key to exit the application... ");
	while(getchar() != '\n'){}
	getchar();
}

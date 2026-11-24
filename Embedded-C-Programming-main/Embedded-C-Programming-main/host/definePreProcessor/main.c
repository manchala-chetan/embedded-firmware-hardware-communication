#include <stdio.h>

#define PI_VALUE (3.1415f)
#define CIRCLE_AREA(r) ((PI_VALUE) * (r) * (r))

#define VERSION 2

#define DEBUG
//#undef DEBUG

#define STM32

int main(){
	/*
	float circleArea;
	circleArea = CIRCLE_AREA(2);

	printf("Circle Area: %f\n", circleArea);
	*/

	/*
	#if VERSION == 1
		printf("--- Version 1 ---\n");
	#elif VERSION == 2
		printf("--- Version 2 ---\n");
	#endif
	*/

	/*
	#ifdef DEBUG
		printf("--- DEBUG mode is ON ---\n");
	#endif
	*/

	/*
	#ifndef BAUD_RATE
		#define BAUD_RATE 9600
	#endif

	printf("--- Baud Rate: %d ---\n", BAUD_RATE);
	*/

	/*
	#ifdef DEBUG
		#warning "--- DEBUG mode is ON ---\n"
	#else
		#warning "--- DEBUG mode is OFF ---\n"
	#endif
	*/

	#if defined(STM32)
		#define LED_PIN 5
	#elif defined(AVR)
		#define LED_PIN 13
	#else
		#error "Unknown MCU!"
	#endif

	printf("LED_PIN: %d", LED_PIN);

	return 0;
}

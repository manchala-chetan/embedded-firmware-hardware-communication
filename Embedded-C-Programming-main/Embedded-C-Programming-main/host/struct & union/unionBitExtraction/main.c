#include <stdio.h>
#include <stdint.h>

typedef union {
	uint32_t packetValue;
	struct{
		uint32_t crc: 2;
		uint32_t status: 1;
		uint32_t payload: 12;
		uint32_t bat: 3;
		uint32_t sensor: 3;
		uint32_t longAddr: 8;
		uint32_t shortAddr: 2;
		uint32_t addrMode: 1;
	} packetFields;
} Packet_t;

void waitForUserInput(void);

void printPacketData(Packet_t *packet);

int main(){
	Packet_t packet;

	printf("Enter the 32bit packet value: ");
	if(scanf("%X", &packet.packetValue) != 1){
		printf("Invalid input!\nExiting...");
		waitForUserInput();
		return 0;
	}

	printPacketData(&packet);

	printf("Size of Extracted Packet is: %llu Byte\n", sizeof(packet));

	waitForUserInput();

	return 0;
}

void waitForUserInput(void){
	printf("\nPress enter key to exit the application... ");
	while(getchar() != '\n'){}
	getchar();
}

void printPacketData(Packet_t *packet){
	printf("\n--- Packet Data ---\n");
	printf("CRC          : %#x\n", packet->packetFields.crc);
	printf("Status       : %#x\n", packet->packetFields.status);
	printf("Payload      : %#x\n", packet->packetFields.payload);
	printf("Bat          : %#x\n", packet->packetFields.bat);
	printf("Sensor       : %#x\n", packet->packetFields.sensor);
	printf("Long Address : %#x\n", packet->packetFields.longAddr);
	printf("Short Address: %#x\n", packet->packetFields.shortAddr);
	printf("Address Mode : %#x\n\n", packet->packetFields.addrMode);
}

#include<stdio.h>
#include<string.h>
#include<wiringPi.h>
#include<wiringPiSPI.h>

#define CS_EEPROM		8
#define SPI_CHANNEL		0
#define SPI_SPEED		1000000

#define WREN			0x06
#define WRDI			0x04
#define RDSR			0x05
#define WRSR 			0x01
#define READ			0x03
#define WRITE			0x02

int main(void){
char buff[9];
wiringPiSetupGpio();

if(wiringPiSPISetup(SPI_CHANNEL,SPI_SPEED)<0)
{
	return -1;
}

pinMode(CS_EEPROM,OUTPUT);
digitalWrite(CS_EEPROM,HIGH);

digitalWrite(CS_EEPROM,LOW);
delayMicroseconds(1);
buff[0] = WREN;
wiringPiSPIDataRW(SPI_CHANNEL,buff,1);
delayMicroseconds(1);
digitalWrite(CS_EEPROM,HIGH);
delay(1);

printf("SAVE : RASPI\n");
digitalWrite(CS_EEPROM,LOW);
delayMicroseconds(1);

buff[0] = WRITE;
buff[1] = 0x00;
buff[2] = 0x11;
buff[3]	= 'R';
buff[4] = 'A';
buff[5] = 'S';
buff[6] = 'P';
buff[7] = 'I';
buff[8] = '\n';

wiringPiSPIDataRW(SPI_CHANNEL,buff,9);
delayMicroseconds(1000);
digitalWrite(CS_EEPROM,HIGH);
delay(5000);

digitalWrite(CS_EEPROM,LOW);
delayMicroseconds(1);
buff[0] = WRDI;

wiringPiSPIDataRW(SPI_CHANNEL,buff,1);
delayMicroseconds(1);
digitalWrite(CS_EEPROM,HIGH);
delay(1);

digitalWrite(CS_EEPROM, LOW);
delayMicroseconds(1);
buff[0] = READ;
buff[1] = 0x00;
buff[2] = 0x11;

wiringPiSPIDataRW(SPI_CHANNEL,buff,9);
delayMicroseconds(1000);
digitalWrite(CS_EEPROM,HIGH);
delay(1000);

printf("READ : ");
int i;
for(i=3; i<9; i++);
{
	printf("%c",buff[i]);
}
printf("\n");
return 0;
}

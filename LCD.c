#include "defines.h"
#include <inttypes.h>
#include "tiva.h"
#include "Timer.h"
#define RS 0x04 //Bit 2 in Port A
#define RW 0x02 //Bit 1 in Port A
#define EN 0x01 //Bit 0 in Port A

void LCD_Init(){

    System_Init(); // Port A - B
    //Enable PortA bits 0-2 for Rs Rw Enable
    	GPIO_PORTA_CR_R |= 0x07;
		GPIO_PORTA_AMSEL_R &= ~0x07;
		GPIO_PORTA_PCTL_R &= ~0x0000FFF;
		GPIO_PORTA_AFSEL_R &= ~0x07;
		GPIO_PORTA_DIR_R |= 0x07;						
		GPIO_PORTA_DEN_R |= 0x07;	
	//Enable port B bits 0-7 for
		GPIO_PORTB_CR_R |= 0xFF;
		GPIO_PORTB_AMSEL_R &= ~0xFF;
		GPIO_PORTB_PCTL_R &= ~0xFFFFFFFF;
		GPIO_PORTB_AFSEL_R &= ~0xFF;
		GPIO_PORTB_DIR_R |= 0xFF;						
		GPIO_PORTB_DEN_R |= 0xFF;	
}
//LCD Control
void LCD_CMD(unsigned char signal){
		GPIO_PORTA_DATA_R = 0x00; //Set RS,RW to 0 to Enable write
		GPIO_PORTB_DATA_R = signal; //Set Data of PortB
		GPIO_PORTA_DATA_R |= EN; //Enable write data
		SysTick_Wait(80);//waits 1 micro sec
		GPIO_PORTA_DATA_R = 0x00; //To Disable changes for LCD
		/*Commands of code 0000 --> 0111 Requires 2ms to be sure they are executed
		Commands above that Requires 40 microsec to be sure they are executed*/
		if(signal < 4) SysTick_Wait(160000); // 2ms
		else SysTick_Wait(3200); // 40 micro sec
}
#include <stdio.h>
#include <stdarg.h>
#include "sam.h"
#include "uart.h"
#include "can.h"

#define BAUDRATE 9600
#define F_CPU 84000000


/*
 * Remember to update the Makefile with the (relative) path to the uart.c file.
 * This starter code will not compile until the UART file has been included in the Makefile. 
 * If you get somewhat cryptic errors referencing functions such as _sbrk, 
 * _close_r, _write_r, _fstat etc, you have most likely not done that correctly.

 * If you get errors such as "arm-none-eabi-gcc: no such file", you may need to reinstall the arm gcc packages using
 * apt or your favorite package manager.
 */
//#include "../path_to/uart.h"

int main()
{

	//PMC->PMC_PCER0 |= (1<<ID_PIOB); //Peripheral clock enable register 0 
		
	//PIOB->PIO_PER = PIO_PB13; //Sets it as a PIO Control
	//PIOB->PIO_OER = PIO_PB13; //Sets PB13 as output
	//PIOB->PIO_SODR = PIO_PB13; //Sets it high (Set Output Data Register)

    SystemInit();

    WDT->WDT_MR = WDT_MR_WDDIS; //Disable Watchdog Timer

	uart_init(F_CPU, BAUDRATE);

	CanInit init = {0};
	can_init(init, 0);


	//printf("SystemCoreClock = %lu Hz\n\r", (unsigned long)SystemCoreClock);

	CanMsg rx;
    while (1)
    {
		//printf("SystemCoreClock = %lu Hz\n\r", (unsigned long)SystemCoreClock);
		
		//uart_tx('a');

		if(can_rx(&rx)){
			can_printmsg(rx);
		}
		
    }
    
}
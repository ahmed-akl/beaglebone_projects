#include <stdint.h>
#include <pru_cfg.h>
#include "resource_table_empty.h"

volatile register uint32_t __R30;   
volatile register uint32_t __R31;   

void main(void)
{
	volatile uint32_t led, button;

	//use pru0_pru_r30_5 as an output (0x0020 = 100000)
	led = 0x0020;
        // Use pru0_pru_r31_3 as a button (0x0008 = 1000)
        button = 0x0008;

	//stop the loop when the button is pressed
	while (!(__R31 && button))
	{
		__R30 ^= led;
                // delay for 1sec (PRU works on 200MHz)
		__delay_cycles(200000000);
	}
        __halt();
}

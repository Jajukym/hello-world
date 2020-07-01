#include "nrf51.h"
#include "nrf51_bitfields.h"

#define LED_BLUE		23
#define LED_GREEN		22
#define LED_RED			21
#define TOGGLE_TICKS	400000

int main(void)
{
	volatile uint32_t toggle_timer=TOGGLE_TICKS;
    /*configure BLUE LED as output*/
    NRF_GPIO->PIN_CNF[LED_GREEN] = (GPIO_PIN_CNF_SENSE_Disabled << GPIO_PIN_CNF_SENSE_Pos)
                                            | (GPIO_PIN_CNF_DRIVE_S0S1 << GPIO_PIN_CNF_DRIVE_Pos)
                                            | (GPIO_PIN_CNF_PULL_Disabled << GPIO_PIN_CNF_PULL_Pos)
                                            | (GPIO_PIN_CNF_INPUT_Disconnect << GPIO_PIN_CNF_INPUT_Pos)
                                            | (GPIO_PIN_CNF_DIR_Output << GPIO_PIN_CNF_DIR_Pos);
    /*toggle the LED*/
    while (1){
    	toggle_timer--;
    	if(toggle_timer == 0){
    		/*get the status of the LED pin and toggle it*/
    		if(((NRF_GPIO->OUT >> LED_GREEN) & 1UL) == 0){
    			NRF_GPIO->OUTSET = (1UL << LED_GREEN);
    		}
    		else{
    			NRF_GPIO->OUTCLR = (1UL << LED_GREEN);
    		}
    		toggle_timer = TOGGLE_TICKS;
    	}
    }
}
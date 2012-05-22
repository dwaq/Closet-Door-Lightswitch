#include <msp430g2231.h>

#define left_LED	BIT6
#define left_SW		BIT7
#define right_LED	BIT4
#define right_SW	BIT5
#define relay		BIT0

void delay(void); 							// Will be used as a shutoff timer

void main(void) {

    WDTCTL = WDTPW + WDTHOLD;

    P1OUT = 0;
    P1DIR |= left_LED + right_LED + relay;  // LED pins to outputs, SW's and relay
                                 			// are still inputs by default

    for (;;) {

	   if ((P1IN & left_SW) != left_SW){	// Wait for left reed switch to disengage
			P1OUT |= left_LED;   			// Left LED on
			P1OUT |= relay;   				// Relay on
	   }
	   if ((P1IN & left_SW) == left_SW){  	// Wait for left reed switch to engage
			P1OUT &= ~left_LED;  			// Left LED off
			P1OUT &= ~relay;  				// Relay off
	   }  									
	   if ((P1IN & right_SW) != right_SW){  // Wait for right reed switch to disengage
			P1OUT |= right_LED;				// Right LED on 
        	P1OUT |= relay;   				// Relay on
	   }  
	   if ((P1IN & right_SW) == right_SW){  // Wait for right reed switch to engage
			P1OUT &= ~right_LED;  			// Right LED off
			P1OUT &= ~relay;  				// Relay off
	   }
	   
	}
	
}

void delay(void) {
    unsigned int count;
    for (count=0; count<60000; count++);
}

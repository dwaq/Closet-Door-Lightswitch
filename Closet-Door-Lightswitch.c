#include <msp430g2001.h>

#define left_LED	BIT4
#define left_SW		BIT5
#define right_LED	BIT6
#define right_SW	BIT7
#define relay		BIT0

void delay(unsigned int);					// Used to wait for one second
void openTooLong(void);						// Used as a shutoff timer

int counter = 0;
int leftOn, rightOn;

void main(void) {

	WDTCTL = WDTPW + WDTHOLD;

	P1OUT = 0;
	P1DIR |= left_LED + right_LED + relay;	// LED and relay pins to outputs,  
											// SW's are inputs by default

	for (;;) {

		if ((P1IN & left_SW) != left_SW){	// Wait for left reed switch to disengage
			P1OUT |= left_LED;				// Left LED on
			leftOn = 1;
		}
		if ((P1IN & left_SW) == left_SW){	// Wait for left reed switch to engage
			P1OUT &= ~left_LED;				// Left LED off
			leftOn = 0;
		}
		if ((P1IN & right_SW) != right_SW){	// Wait for right reed switch to disengage
			P1OUT |= right_LED;				// Right LED on 
			rightOn = 1;
		}
		if ((P1IN & right_SW) == right_SW){	// Wait for right reed switch to engage
			P1OUT &= ~right_LED;			// Right LED off
			rightOn = 0;
		}
		
		// At least one of the doors is open, turn on relay and
		// count up a second until 5 minutes (300 seconds) is reached
		if ((rightOn | leftOn) == 1){
			P1OUT |= relay;					// Relay on
			delay(1);
			++counter;
			if (counter == 300000){
				openTooLong();
			}
		}
		
		// Both doors are closed, turn off the light and reset the counter
		if ((rightOn | leftOn) == 0){
			P1OUT &= ~relay;				// Relay off
			counter = 0;
		}
		
	}
	
}

// Delays by the specified Milliseconds
void delay(unsigned int ms) {
	while (ms--) {
		__delay_cycles(1000);
	}
}

// Wait for both doors to close, then resets to main
void openTooLong(void) {
	P1OUT &= ~relay;						// Relay off
	for (;;){
		if ((P1IN & left_SW) != left_SW){	// Wait for left reed switch to disengage
			P1OUT |= left_LED;				// Left LED on
			leftOn = 1;
		}
		if ((P1IN & left_SW) == left_SW){	// Wait for left reed switch to engage
			P1OUT &= ~left_LED;				// Left LED off
			leftOn = 0;
		}
		if ((P1IN & right_SW) != right_SW){	// Wait for right reed switch to disengage
			P1OUT |= right_LED;				// Right LED on 
			rightOn = 1;
		}
		if ((P1IN & right_SW) == right_SW){	// Wait for right reed switch to engage
			P1OUT &= ~right_LED;			// Right LED off
			rightOn = 0;
		}
		
		// When both are closed, reset
		if ((rightOn | leftOn) == 0){
			counter = 0;
			main();
		}
	}
}

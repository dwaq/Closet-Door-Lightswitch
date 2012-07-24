#include <msp430g2231.h>

#define left_LED	BIT6
#define left_SW		BIT7
#define right_LED	BIT4
#define right_SW	BIT5
#define relay		BIT0

void delay(unsigned int);						// Used to wait for a second
void openTooLong(void);							// Used as a shutoff timer

int counter;
int leftOn;
int rightOn;

void main(void) {

	WDTCTL = WDTPW + WDTHOLD;

	P1OUT = 0;
	P1DIR |= left_LED + right_LED + relay;	// LED and relay pins to outputs, 
	P1DIR &= !(left_SW + right_SW)			// SW's are inputs by default

	counter = 0;

	for (;;) {

		if ((P1IN & left_SW) != left_SW){	// Wait for left reed switch to disengage
			P1OUT |= left_LED;				// Left LED on
			P1OUT |= relay;					// Relay on
			leftOn = 1;
		}
		if ((P1IN & left_SW) == left_SW){	// Wait for left reed switch to engage
			P1OUT &= ~left_LED;				// Left LED off
			P1OUT &= ~relay;				// Relay off
			leftOn = 0;
		}
		if ((P1IN & right_SW) != right_SW){	// Wait for right reed switch to disengage
			P1OUT |= right_LED;				// Right LED on 
			P1OUT |= relay;					// Relay on
			rightOn = 1;
		}
		if ((P1IN & right_SW) == right_SW){	// Wait for right reed switch to engage
			P1OUT &= ~right_LED;			// Right LED off
			P1OUT &= ~relay;				// Relay off
			rightOn = 0;
		}

		// Each time the relay is open, count up a second until 15 seconds 
		// (5 min) are reached, then turn the relay off until the doors are shut
		if (rightOn == 1 || leftOn == 1){	// OR
			delay(1);
			++counter;
			if (counter == 15000){
				openTooLong();
			}
		}
		// If both doors are closed, reset the counter
		if ((rightOn && leftOn) == 0){	// AND
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
		if ((P1IN & left_SW) != left_SW){	// Left door open
			P1OUT |= left_LED;				// Left LED on
			leftOn = 1;
		}
		if ((P1IN & left_SW) == left_SW){	// Left door closed
			P1OUT &= ~left_LED;				// Left LED off
			leftOn = 0;
		}
		if ((P1IN & right_SW) != right_SW){	// Right door open
			P1OUT |= right_LED;				// Right LED on 
			rightOn = 1;
		}
		if ((P1IN & right_SW) == right_SW){	// Right door closed
			P1OUT &= ~right_LED;			// Right LED off
			rightOn = 0;
		}

		// if both doors are closed
		if ((rightOn && leftOn) == 0){	// AND
			main();
		}
	}
}

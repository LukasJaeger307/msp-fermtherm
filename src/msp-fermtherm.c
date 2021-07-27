/* This file is part of msp-fermtherm.
 *
 * msp-fermtherm is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * msp-fermtherm is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with msp-fermtherm.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <msp430g2553.h>
#include <stdlib.h>
#include <stdio.h>
#include "ds18b20.h"

// IO definitions
#define BUTTON BIT3

// Timer definitions
#define TIMER_DELAY (6249) // Equal to 0.5 seconds
#define ENABLE_TIMER (TASSEL_2 | ID_3 | MC_1 |TACLR)

// Some magic numbers
#define FLASHES (10)

static void uart_tx_string(char const * const s){
	size_t i = 0;
	while(s[i] != 0x00) {
		while (UCA0STAT & UCBUSY); 
		UCA0TXBUF = s[i]; 
		i++;
	}
}

static void show_temperature(float temp) {
	// Reset it all
	P1OUT = 0x00;
	P2OUT = 0x00;
	// Too cold to ferment anything
	if (temp < 3.0) {
		for (size_t i = 0; i < FLASHES; i++) {
			YEAST_LAGER_PORT |= YEAST_LAGER_BIT;
			RANGE_LOW_PORT |= RANGE_LOW_BIT;
			TEMP_LOW_PORT |= TEMP_LOW_BIT;
			__delay_cycles(10000);
			YEAST_LAGER_PORT &= ~YEAST_LAGER_BIT;
			RANGE_LOW_PORT &= ~RANGE_LOW_BIT;
			TEMP_LOW_PORT &= ~TEMP_LOW_BIT;
			__delay_cycles(10000);
		}
	} 
	// Good enough for Lager yeast
	else if (temp < 15.0) {
		YEAST_LAGER_PORT |= YEAST_LAGER_BIT;
		if (temp < 7.0) {
			// Low Range
			RANGE_LOW_PORT |= RANGE_LOW_BIT;
			if (temp < 4.0) {
				// Low Temperature
				TEMP_LOW_PORT |= TEMP_LOW_BIT;
			}
			else if (temp < 5.0) {
				// Mid low Temperature
				TEMP_MIDLOW_PORT |= TEMP_MIDLOW_BIT;
			}
			else if (temp < 6.0) {
				// Mid high Temperature
				TEMP_MIDHIGH_PORT |= TEMP_MIDHIGH_BIT;
			}
			else {
				// High Temperature
				TEMP_HIGH_PORT |= TEMP_HIGH_BIT;
			}
		}
		else if (temp < 11.0) {
			// Mid Range
			RANGE_MID_PORT |= RANGE_MID_BIT;
			if (temp < 8.0) {
				// Low Temperature
				TEMP_LOW_PORT |= TEMP_LOW_BIT;
			}
			else if (temp < 9.0) {
				// Mid low Temperature
				TEMP_MIDLOW_PORT |= TEMP_MIDLOW_BIT;
			}
			else if (temp < 10.0) {
				// Mid high Temperature
				TEMP_MIDHIGH_PORT |= TEMP_MIDHIGH_BIT;
			}
			else {
				// High Temperature
				TEMP_HIGH_PORT |= TEMP_HIGH_BIT;
			}
		}
		else {
			// High Range
			RANGE_HIGH_PORT |= RANGE_HIGH_BIT;
			if (temp < 12.0) {
				// Low Temperature
				TEMP_LOW_PORT |= TEMP_LOW_BIT;
			}
			else if (temp < 13.0) {
				// Mid low Temperature
				TEMP_MIDLOW_PORT |= TEMP_MIDLOW_BIT;
			}
			else if (temp < 14.0) {
				// Mid high Temperature
				TEMP_MIDHIGH_PORT |= TEMP_MIDHIGH_BIT;
			}
			else {
				// High Temperature
				TEMP_HIGH_PORT |= TEMP_HIGH_BIT;
			}
		}
	}
	// Good enough for Ale yeast
	else if (temp < 27.0) {
		YEAST_ALE_PORT |= YEAST_ALE_BIT;	
		if (temp < 19.0) {
			// Low Range
			RANGE_LOW_PORT |= RANGE_LOW_BIT;
			if (temp < 16.0) {
				// Low Temperature
				TEMP_LOW_PORT |= TEMP_LOW_BIT;
			}
			else if (temp < 17.0) {
				// Mid low Temperature
				TEMP_MIDLOW_PORT |= TEMP_MIDLOW_BIT;
			}
			else if (temp < 18.0) {
				// Mid high Temperature
				TEMP_MIDHIGH_PORT |= TEMP_MIDHIGH_BIT;
			}
			else {
				// High Temperature
				TEMP_HIGH_PORT |= TEMP_HIGH_BIT;
			}
		}
		else if (temp < 23.0) {
			// Mid Range
			RANGE_MID_PORT |= RANGE_MID_BIT;
			if (temp < 20.0) {
				// Low Temperature
				TEMP_LOW_PORT |= TEMP_LOW_BIT;
			}
			else if (temp < 21.0) {
				// Mid low Temperature
				TEMP_MIDLOW_PORT |= TEMP_MIDLOW_BIT;
			}
			else if (temp < 22.0) {
				// Mid high Temperature
				TEMP_MIDHIGH_PORT |= TEMP_MIDHIGH_BIT;
			}
			else {
				// High Temperature
				TEMP_HIGH_PORT |= TEMP_HIGH_BIT;
			}
		}
		else {
			// High Range
			RANGE_HIGH_PORT |= RANGE_HIGH_BIT;
			if (temp < 24.0) {
				// Low Temperature
				TEMP_LOW_PORT |= TEMP_LOW_BIT;
			}
			else if (temp < 25.0) {
				// Mid low Temperature
				TEMP_MIDLOW_PORT |= TEMP_MIDLOW_BIT;
			}
			else if (temp < 26.0) {
				// Mid high Temperature
				TEMP_MIDHIGH_PORT |= TEMP_MIDHIGH_BIT;
			}
			else {
				// High Temperature
				TEMP_HIGH_PORT |= TEMP_HIGH_BIT;
			}
		}
	}
	// Good enough for Kveik yeas
	else if (temp < 39.0) {
		YEAST_KVEIK_PORT = YEAST_KVEIK_BIT;
		if (temp < 31.0) {
			// Low Range
			RANGE_LOW_PORT |= RANGE_LOW_BIT;
			if (temp < 28.0) {
				// Low Temperature
				TEMP_LOW_PORT |= TEMP_LOW_BIT;
			}
			else if (temp < 29.0) {
				// Mid low Temperature
				TEMP_MIDLOW_PORT |= TEMP_MIDLOW_BIT;
			}
			else if (temp < 30.0) {
				// Mid high Temperature
				TEMP_MIDHIGH_PORT |= TEMP_MIDHIGH_BIT;
			}
			else {
				// High Temperature
				TEMP_HIGH_PORT |= TEMP_HIGH_BIT;
			}
		}
		else if (temp < 35.0) {
			// Mid Range
			RANGE_MID_PORT |= RANGE_MID_BIT;
			if (temp < 32.0) {
				// Low Temperature
				TEMP_LOW_PORT |= TEMP_LOW_BIT;
			}
			else if (temp < 33.0) {
				// Mid low Temperature
				TEMP_MIDLOW_PORT |= TEMP_MIDLOW_BIT;
			}
			else if (temp < 34.0) {
				// Mid high Temperature
				TEMP_MIDHIGH_PORT |= TEMP_MIDHIGH_BIT;
			}
			else {
				// High Temperature
				TEMP_HIGH_PORT |= TEMP_HIGH_BIT;
			}
		}
		else {
			// High Range
			RANGE_HIGH_PORT |= RANGE_HIGH_BIT;
			if (temp < 36.0) {
				// Low Temperature
				TEMP_LOW_PORT |= TEMP_LOW_BIT;
			}
			else if (temp < 37.0) {
				// Mid low Temperature
				TEMP_MIDLOW_PORT |= TEMP_MIDLOW_BIT;
			}
			else if (temp < 38.0) {
				// Mid high Temperature
				TEMP_MIDHIGH_PORT |= TEMP_MIDHIGH_BIT;
			}
			else {
				// High Temperature
				TEMP_HIGH_PORT |= TEMP_HIGH_BIT;
			}
		}
	}
	// Too hot to ferment anything
	else {
		for (size_t i = 0; i < FLASHES; i++) {
			YEAST_KVEIK_PORT |= YEAST_KVEIK_BIT;
			RANGE_HIGH_PORT |= RANGE_HIGH_BIT;
			TEMP_HIGH_PORT |= TEMP_HIGH_BIT;
			__delay_cycles(10000);
			YEAST_KVEIK_PORT &= ~YEAST_KVEIK_BIT;
			RANGE_HIGH_PORT &= ~RANGE_HIGH_BIT;
			TEMP_HIGH_PORT &= ~TEMP_HIGH_BIT;
		__delay_cycles(10000);
	}
	}

}

int main (void)
{	
	// Disable WD timer
	WDTCTL = WDTPW + WDTHOLD;

	// TODO: Clock down
	// Set clocks
	BCSCTL1 = 0;//CALBC1_1MHZ;
	DCOCTL = 0; //CALDCO_1MHZ;
	
	// Make button pin input
	P1DIR &= ~BUTTON;
	// Enable pull-up resistor
	P1REN |= BUTTON;
	// Some inversion magic?
	P1OUT = BUTTON;
	// Interrupt at high-to-low transition
	P1IES |= BUTTON;
	// Initial interrupt flag clear
	P1IFG &= ~BUTTON;
	// Enable interrupt for button
	P1IE |= BUTTON;

	// Enable timer interrupt
	TACCTL0 = CCIE;

	// Select UART Pins
	UART_PORT_CONF = UART_RX_PIN + UART_TX_PIN;
	UART_PORT_CONF2 = UART_RX_PIN + UART_TX_PIN;
	// Set clock
	UCA0CTL1 |= UCSSEL_2;
	// Set 9600 baud at 1MHz
	UCA0BR0 = 0x0A;
	UCA0BR1 = 0;
	// Set modulation
	UCA0MCTL = UCBRS0;
	// Start state machine
	UCA0CTL1 &= ~UCSWRST;

	// Make all temperature pins outputs
	P1DIR |= TEMPLEDS_P1;
 	P2DIR |= TEMPLEDS_P2;	
	

	/*for (float temp = 2.5; temp < 40.0; temp+=1.0) {
		show_temperature(temp);
		__delay_cycles(100000);
	}*/
	
	// Globally enable interrupts
	//_BIS_SR(GIE);

	// Go to LPM4
	//LPM4;

	// Loop forever
	while(1){
			// Get temp and print
			float temperature = ds_get_temperature(); 
			// Print a debug string
			char string [6];
			sprintf(string, "%u.%02u", (int) temperature, (int) ((temperature - (float)((int)(temperature))) * 100));
			uart_tx_string("Temperature: ");
			uart_tx_string(string);
			uart_tx_string("\r\n");
			__delay_cycles(10000);
	}
}

// Semaphore-ish variable that stores, whether or not the device is just
// displaying temperatures
static volatile int is_inactive = 1;

// ISR for port 1 
static void __attribute__((__interrupt__(PORT1_VECTOR))) p1_isr(void) {
	// Check if button push caused it
	if (P1IFG & BUTTON) {
		// Clear flag
		P1IFG = P1IFG & ~BUTTON;

		// Only start activity if it does not yet happen
		if (is_inactive) {
			// Wake up
			LPM4_EXIT;
			is_inactive = 0;

			// Get temp and print
			float temperature = ds_get_temperature(); 
			// Print a debug string
			char string [6];
			sprintf(string, "%u.%02u", (int) temperature, (int) ((temperature - (float)((int)(temperature))) * 100));
			uart_tx_string("Temperature: ");
			uart_tx_string(string);
			uart_tx_string("\r\n");

			// Enable and start timer
			TA0CTL |= ENABLE_TIMER;
			TACCR0 =  TIMER_DELAY;
		}
	}
}

// ISR for TimerA0
static void __attribute__((__interrupt__(TIMER1_A0_VECTOR))) ta0_isr(void) {
	// Disable timer
	TACCR0 = 0;
	// Deactivate stuff
	is_inactive = 1;
	// And go back to LPM4
	LPM4;
}

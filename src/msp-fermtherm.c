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
#define LED2 BIT6

// Timer definitions
#define TIMER_DELAY (62499) // Equal to 0.5 seconds
#define ENABLE_TIMER (TASSEL_2 | ID_3 | MC_1 |TACLR)

static void uart_tx_string(char const * const s){
	size_t i = 0;
	while(s[i] != 0x00) {
		while (UCA0STAT & UCBUSY); 
		UCA0TXBUF = s[i]; 
		i++;
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

	// Enable LED2
	P1DIR |= LED2;
		
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

	// Globally enable interrupts
	_BIS_SR(GIE);

	// Go to LPM4
	LPM4;

	// Loop forever
	while(1);
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
			
			// Activate LED
			P1OUT |= LED2;

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
	// Disable LED2
	P1OUT &= ~LED2;
	// Disable timer
	TACCR0 = 0;
	// Deactivate stuff
	is_inactive = 1;
	// And go back to LPM4
	LPM4;
}

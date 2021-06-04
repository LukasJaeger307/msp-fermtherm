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

#ifndef _PINOUT_H_
#define _PINOUT_H_


// DS18B20
#define DS18B20_PORT (P1OUT)
#define DS18B20_PORTCONF (P1DIR)
#define DS18B20_PIN (BIT0)

// UART
#define UART_PORT_CONF (P1SEL)
#define UART_PORT_CONF2 (P1SEL2)
#define UART_RX_PIN (BIT1)
#define UART_TX_PIN (BIT2)

// Temperature pins
#define TEMPLEDS_P1 (BIT4 | BIT5 | BIT6 | BIT7)
#define TEMPLEDS_P2 (BIT0 | BIT1 | BIT2 | BIT3 | BIT4 | BIT5)

#define YEAST_LAGER_PORT (P1OUT)
#define YEAST_LAGER_BIT (BIT4)
#define YEAST_ALE_PORT (P1OUT)
#define YEAST_ALE_BIT (BIT5)
#define YEAST_KVEIK_PORT (P2OUT)
#define YEAST_KVEIK_BIT (BIT0)

#define RANGE_LOW_PORT (P2OUT)
#define RANGE_LOW_BIT (BIT1)
#define RANGE_MID_PORT (P2OUT)
#define RANGE_MID_BIT (BIT2)
#define RANGE_HIGH_PORT (P1OUT)
#define RANGE_HIGH_BIT (BIT7)

#define TEMP_LOW_PORT (P1OUT)
#define TEMP_LOW_BIT (BIT6)
#define TEMP_MIDLOW_PORT (P2OUT)
#define TEMP_MIDLOW_BIT (BIT5)
#define TEMP_MIDHIGH_PORT (P2OUT)
#define TEMP_MIDHIGH_BIT (BIT4)
#define TEMP_HIGH_PORT (P2OUT)
#define TEMP_HIGH_BIT (BIT3)

#endif // PINOUT_H_

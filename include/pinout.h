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

#endif // PINOUT_H_

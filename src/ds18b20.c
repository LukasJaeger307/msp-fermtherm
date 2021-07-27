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

#include "ds18b20.h"
#include <stdint.h>

static void ds_initialize(){
	DS18B20_PORTCONF |= DS18B20_PIN;
	DS18B20_PORT &= ~DS18B20_PIN;
	__delay_cycles(500);
	DS18B20_PORT |= DS18B20_PIN;
	DS18B20_PORTCONF &= ~DS18B20_PIN;
	__delay_cycles(500);
}


static void ds_send_char(uint8_t data){
	for (uint8_t i = 0; i < 8; i++){
		DS18B20_PORTCONF |= DS18B20_PIN;
		DS18B20_PORT &= ~DS18B20_PIN;
		__delay_cycles(2);
		if ((data & 0x01) != 0x00){
			DS18B20_PORT |= DS18B20_PIN;	
		}
		__delay_cycles(60);
		DS18B20_PORT |= DS18B20_PIN;
		DS18B20_PORTCONF &= ~DS18B20_PIN;			
		data >>=1;
	}
}


static void ds_read(uint16_t * const data){
	for(uint8_t i = 0; i < 16; i++){
		DS18B20_PORTCONF |= DS18B20_PIN;
		DS18B20_PORT &= ~DS18B20_PIN;
		__delay_cycles(2);
		DS18B20_PORT |= DS18B20_PIN;
		DS18B20_PORTCONF &= ~DS18B20_PIN;
		__delay_cycles(8);
		if(P1IN & DS18B20_PIN){
			*data |= 0x8000;
		}
		*data = *data >> 1;
		__delay_cycles(12);
	}
}


float ds_get_temperature(){
	ds_initialize();
	ds_send_char(0xcc);   
	ds_send_char(0x44);
	__delay_cycles(100);

	ds_initialize();
	ds_send_char(0xcc);
	ds_send_char(0xbe);

	uint16_t temp = 0; 
	ds_read(&temp);
	return ((float)temp/8.0);
} 

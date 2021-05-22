#ifndef _DS18B20_H_
#define _DS18B20_H_

#include <msp430g2553.h>

#define DS18B20_PORT (P1OUT)
#define DS18B20_PORTCONF (P1DIR)

#define DS18B20_PIN (BIT0)

float ds_get_temperature();

#endif //_DS18B20_H_



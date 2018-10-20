/*
  pins_arduino.h - Pin definition functions for Arduino
  Part of Arduino - http://www.arduino.cc/

  Copyright (c) 2007 David A. Mellis

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General
  Public License along with this library; if not, write to the
  Free Software Foundation, Inc., 59 Temple Place, Suite 330,
  Boston, MA  02111-1307  USA

  $Id: wiring.h 249 2007-02-03 16:52:51Z mellis $
*/

#ifndef Pins_Arduino_h
#define Pins_Arduino_h

#define ATTINYX7 1       //backwards compat
#define __AVR_ATtinyX7__ //recommended

#include <avr/pgmspace.h>

#define NUM_DIGITAL_PINS            16
#define NUM_ANALOG_INPUTS           11
#define analogInputToDigitalPin(p)  (p<8?p:p+5)

#define digitalPinHasPWM(p)         ((p) == 2 || (p) == 11 || (p) == 14)

#define SS   6
#define MOSI 4
#define MISO 2
#define SCK  5

#define SDA 4
#define SCL 5

//Ax constants cannot be used for digitalRead/digitalWrite/analogWrite functions, only analogRead().
static const uint8_t A0 = NUM_DIGITAL_PINS;
static const uint8_t A1 = NUM_DIGITAL_PINS+1;
static const uint8_t A2 = NUM_DIGITAL_PINS+2;
static const uint8_t A3 = NUM_DIGITAL_PINS+3;
static const uint8_t A4 = NUM_DIGITAL_PINS+4;
static const uint8_t A5 = NUM_DIGITAL_PINS+5;
static const uint8_t A6 = NUM_DIGITAL_PINS+6;
static const uint8_t A7 = NUM_DIGITAL_PINS+7;
static const uint8_t A8 = NUM_DIGITAL_PINS+8;
static const uint8_t A9 = NUM_DIGITAL_PINS+9;
static const uint8_t A10 = NUM_DIGITAL_PINS+10;

//----------------------------------------------------------
//----------------------------------------------------------
//Core Configuration (used to be in core_build_options.h)

//If Software Serial communications doesn't work, run the TinyTuner sketch provided with the core to give you a calibrated OSCCAL value.
//Change the value here with the tuned value. By default this option uses the default value which the compiler will optimise out. 
#define TUNED_OSCCAL_VALUE                        OSCCAL
//e.g
//#define TUNED_OSCCAL_VALUE                        0x57

//Choosing not to initialise saves power and flash. 1 = initialise.
#define INITIALIZE_ANALOG_TO_DIGITAL_CONVERTER    1
#define INITIALIZE_SECONDARY_TIMERS               0

#define TIMER_TO_USE_FOR_MILLIS                   0

#define HAVE_BOOTLOADER                           1

/*
  Where to put the software serial? (Arduino Digital pin numbers)
*/
//WARNING, if using software, TX is on AIN0, RX is on AIN1. Comparator is favoured to use its interrupt for the RX pin.
#define USE_SOFTWARE_SERIAL						  0
//Please define the port on which the analog comparator is found.
#define ANALOG_COMP_DDR						 	  DDRA
#define ANALOG_COMP_PORT						  PORTA
#define ANALOG_COMP_PIN						 	  PINA
#define ANALOG_COMP_AIN0_BIT					  6
#define ANALOG_COMP_AIN1_BIT					  7

/*
  Analog reference bit masks.
*/
// VCC used as analog reference, disconnected from PA0 (AREF)
#define DEFAULT (0)
// External voltage reference at PA0 (AREF) pin, internal reference turned off
#define EXTERNAL (1)
// Internal 1.1V voltage reference
#define INTERNAL (2)


//----------------------------------------------------------
//----------------------------------------------------------
//----------------------------------------------------------
//----------------------------------------------------------



#define digitalPinToPCICR(p)    (&PCICR)
#define digitalPinToPCICRbit(p) (((p) >= 8 ? 0 : 1)
#define digitalPinToPCMSK(p)    ((p) >= 8 ?(&PCMSK0) : (&PCMSK1))
#define digitalPinToPCMSKbit(p) (p&15)

#ifdef ARDUINO_MAIN

// On the Arduino board, digital pins are also used
// for the analog output (software PWM).  Analog input
// pins are a separate set.

// ATMEL ATTINY167
//
//                   +-\/-+
// RX   (D  0) PA0  1|    |20  PB0 (D  8)
// TX   (D  1) PA1  2|    |19  PB1 (D  9)
//     *(D  2) PA2  3|    |18  PB2 (D 10)
//      (D  3) PA3  4|    |17  PB3 (D 11)*
//            AVCC  5|    |16  GND
//            AGND  6|    |15  VCC
// INT1 (D  4) PA4  7|    |14  PB4 (D 12)
//      (D  5) PA5  8|    |13  PB5 (D 13)
//      (D  6) PA6  9|    |12  PB6 (D 14)* INT0
//      (D  7) PA7 10|    |11  PB7 (D 15)
//                   +----+
//
// * indicates PWM pin.

// these arrays map port names (e.g. port B) to the
// appropriate addresses for various functions (e.g. reading
// and writing)
const uint16_t PROGMEM port_to_mode_PGM[] = 
{
	NOT_A_PORT,
	(uint16_t)&DDRA,
	(uint16_t)&DDRB,
};

const uint16_t PROGMEM port_to_output_PGM[] = 
{
	NOT_A_PORT,
	(uint16_t)&PORTA,
	(uint16_t)&PORTB,
};

const uint16_t PROGMEM port_to_input_PGM[] = 
{
	NOT_A_PORT,
	(uint16_t)&PINA,
	(uint16_t)&PINB,
};

const uint8_t PROGMEM digital_pin_to_port_PGM[] = 
{
	PA, /* 0 */
	PA,
	PA, /* 2 */
	PA, /* 3 */
	PA, /* 4 */
	PA,
	PA,
	PA,
	PB,
	PB,
	PB, /* 10 */
	PB,
	PB,
	PB,
	PB,
	PB, /* 15 */
};

const uint8_t PROGMEM digital_pin_to_bit_mask_PGM[] = 
{
	_BV(0), /* 0 */
	_BV(1),
	_BV(2), /* 2 */
	_BV(3), /* 3 */
	_BV(4), /* 4 */
	_BV(5),
	_BV(6),
	_BV(7),
	_BV(0),
	_BV(1),
	_BV(2), /* 10 */
	_BV(3),
	_BV(4),
	_BV(5),
	_BV(6),
	_BV(7), /* 15 */
};

const uint8_t PROGMEM digital_pin_to_timer_PGM[] = 
{
	NOT_ON_TIMER, 
	NOT_ON_TIMER,
	TIMER0A,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	TIMER1B,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	TIMER1A,
	NOT_ON_TIMER,
};

#endif

#endif




//Old code, just here for temporary backup until I decide it is not needed.
//WARNING, if using software, RX must be on a pin which has a Pin change interrupt <= 7 (e.g. PCINT6, or PCINT1, but not PCINT8)
/*#define USE_SOFTWARE_SERIAL						  1
//These are set to match Optiboot pins.

#define SOFTWARE_SERIAL_PORT 					  PORTB
#define SOFTWARE_SERIAL_TX 						  0
#define SOFTWARE_SERIAL_PIN 					  PINB
#define SOFTWARE_SERIAL_RX 						  1*/

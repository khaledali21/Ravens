

#ifndef DDIO_128_H_
#define DDIO_128_H_


#include "STD_TYPES.h"
#include "UTILS.h"

/*
 * Define ATMEGA128 Registers
 */

/* PORT A Registers */
#define PINA  (* (volatile u8 *) ( 0x39) )
#define DDRA  (* (volatile u8 *) ( 0x3A) )
#define PORTA (* (volatile u8 *) ( 0x3B) )


/* PORT B Registers */
#define PINB (* (volatile u8 *) ( 0x36) )
#define DDRB  (* (volatile u8 *) ( 0x37) )
#define PORTB (* (volatile u8 *) ( 0x38) )

/* PORT C Registers */
#define PINC  (* (volatile u8 *) ( 0x33) )
#define DDRC  (* (volatile u8 *) ( 0x34) )
#define PORTC (* (volatile u8 *) ( 0x35) )

/* PORT D Registers */
#define PIND  (* (volatile u8 *) ( 0x30) )
#define DDRD  (* (volatile u8 *) ( 0x31) )
#define PORTD (* (volatile u8 *) ( 0x32) )

/* PORT E Registers */
#define PINE  (* (volatile u8 *) ( 0x23) )
#define DDRE  (* (volatile u8 *) ( 0x22) )
#define PORTE (* (volatile u8 *) ( 0x2E) )

/* PORT F Registers */
#define PINF  (* (volatile u8 *) ( 0x20) )
#define DDRF  (* (volatile u8 *) ( 0x61) )
#define PORTF (* (volatile u8 *) ( 0x62) )

/* PORT G Registers */
#define PING  (* (volatile u8 *) ( 0x63) )
#define DDRG  (* (volatile u8 *) ( 0x64) )
#define PORTG (* (volatile u8 *) ( 0x65) )




#define INPUT_PULL_UP	    0
#define INPUT_FLOAT         2
#define OUTPUT				1

#define LOW					0
#define HIGH				1




#define PINA_0 0
#define PINA_1 1
#define PINA_2 2
#define PINA_3 3
#define PINA_4 4
#define PINA_5 5
#define PINA_6 6
#define PINA_7 7


#define PINB_0 8
#define PINB_1 9
#define PINB_2 10
#define PINB_3 11
#define PINB_4 12
#define PINB_5 13
#define PINB_6 14
#define PINB_7 15


#define PINC_0 16
#define PINC_1 17
#define PINC_2 18
#define PINC_3 19
#define PINC_4 20
#define PINC_5 21
#define PINC_6 22
#define PINC_7 23


#define PIND_0 24
#define PIND_1 25
#define PIND_2 26
#define PIND_3 27
#define PIND_4 28
#define PIND_5 29
#define PIND_6 30
#define PIND_7 31


#define PINE_0 32
#define PINE_1 33
#define PINE_2 34
#define PINE_3 35
#define PINE_4 36
#define PINE_5 37
#define PINE_6 38
#define PINE_7 39


#define PINF_0 40
#define PINF_1 41
#define PINF_2 42
#define PINF_3 43
#define PINF_4 44
#define PINF_5 45
#define PINF_6 46
#define PINF_7 47


#define PING_0 48
#define PING_1 49
#define PING_2 50
#define PING_3 51
#define PING_4 52
#define PING_5 53
#define PING_6 54
#define PING_7 55






void SetPinDir(u8 PinNumber,u8 PinDirection);
void SetPinVal(u8 PinNumber,u8 PinValue);
u8 ReadPinVal(u8 PinNumber);


#endif /* DDIO_128_H_ */

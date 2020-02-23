/*
 * USART.h
 *
 *  Created on: 6 Oct 2018
 *      Author: mahmoud
 */

#ifndef USART_H_
#define USART_H_

#include"STD_TYPES.h"
#include"UTILS.h"
//#include"micro_config.h"
/* FUNCTION DECLARATIONS                */
void UART0_init(u8 baudrate);
void UART1_init(u8 baudrate);
void UART2_init();
u8 UART0_receiveByte (void);
void UART0_sendByte(u8 data);
u8 UART1_receiveByte (void);
void UART1_sendByte(u8 data);
u8 UART2_receiveByte (void);
void UART2_sendByte(u8 data);
void UART0_receiveString (u8 *str);
void UART0_sendString (const u8 *str);
void UART1_receiveString (u8 *str);
void UART1_sendString (const u8 *str);
void UART2_receiveString (u8 *str);
void UART2_sendString (const u8 *str);

#define UCSR0A  (* (volatile u8 *) (0xC0) )
#define UCSR0B  (* (volatile u8 *) (0xC1) )
#define UCSR0C  (* (volatile u8 *) (0xC2) )
#define UBRR0H  (* (volatile u8 *) (0xC5) )
#define UBRR0L  (* (volatile u8 *) (0xC4) )
#define UDR0    (* (volatile u8 *) (0xC6) )


#define UCSR1A  (* (volatile u8 *) (0xC8) )
#define UCSR1B  (* (volatile u8 *) (0xC9) )
#define UCSR1C  (* (volatile u8 *) (0xCA) )
#define UBRR1H  (* (volatile u8 *) (0xCD) )
#define UBRR1L  (* (volatile u8 *) (0xCC) )
#define UDR1    (* (volatile u8 *) (0xCE) )



#define UCSR2A  (* (volatile u8 *) (0xD0) )
#define UCSR2B  (* (volatile u8 *) (0xD1) )
#define UCSR2C  (* (volatile u8 *) (0xD2) )
#define UBRR2H  (* (volatile u8 *) (0xD5) )
#define UBRR2L  (* (volatile u8 *) (0xD4) )
#define UDR2    (* (volatile u8 *) (0xD6) )



#define U2X		1
#define RXEN	4
#define TXEN	3
#define UPM0	4
#define UPM1	5
#define UCSZ0	1
#define UCSZ1	2
#define TXC		6
#define RXC		7


#define USART_BAUDRATE 9600
#define BAUD_PRESCALE 51


#endif /* USART_H_ */

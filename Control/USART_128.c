/*
 * USART.c
 *
 *  Created on: 6 Oct 2018
 *      Author: mahmoud
 */
#include "USART_128.h"
/*
 * FUNCTION TO US :
 * UART_sendByte(DATA) send byte
 * UART_receiveByte()  receive byte
 * baud rate = 9600 symbol/second
 * UART_sendString(" ... #") NOTE : you must send '#' at the end of the string
 * UART_receiveString()
 *
 */
void UART0_init()
{
	//UCSR0A=(1<<U2X);											// double speed mode

	UCSR0B	=	0b00011000;									//sender and receiver
	UCSR0C	= 	0b10000110;							//no parity check and send 8 bits

	UBRR0L=103;

}

void UART1_init()
{
	//UCSR1A=(1<<U2X);											// double speed mode
	UCSR1B	=	0b00011000;										//sender and receiver
	UCSR1C	= 	0b10000110;							//no parity check and send 8 bits
	//UBRR1H=BAUD_PRESCALE<<8; 								//baud rate 9600
	UBRR1L	=	103;

}


void UART2_init()
{
	//UCSR2A	=	(1<<U2X);											// double speed mode
	UCSR2B	= 	0b00011000;									//sender and receiver
	UCSR2C	=	0b10000110;							//no parity check and send 8 bits
	//UBRR2H=BAUD_PRESCALE<<8; 								//baud rate 9600
	UBRR2L=103;
}



/* this fun sends a byte and waits till the U DATA is sent then send another byte  to avoid overwriting  */
void UART0_sendByte (u8 data)
{
	UDR0=data;
	while (!GET_BIT(UCSR0A,5)){}
	SET_BIT(UCSR0A,TXC);

}
/* this fun receive a byte and waits until the data is empty to avoid overwriting */
u8 UART0_receiveByte (void)
{
	while (!GET_BIT(UCSR0A,7)){}
	/*
	 * wait until the last byte is received
	 */
	return UDR0;
}

/* this fun sends a byte and waits till the U DATA is sent then send another byte  to avoid overwriting  */
void UART1_sendByte (u8 data)
{
	UDR1=data;
	while (!GET_BIT(UCSR1A,5)){}
	SET_BIT(UCSR1A,TXC);

}
/* this fun receive a byte and waits untill the data is empty to avoid overwriting */
u8 UART1_receiveByte (void)
{
	while (!GET_BIT(UCSR1A,7)){}
	/*
	 * wait until the last byte is received
	 */
	return UDR1;
}


/* this fun sends a byte and waits till the U DATA is sent then send another byte  to avoid overwriting  */
void UART2_sendByte (u8 data)
{
	UDR2=data;
	while (!GET_BIT(UCSR2A,5)){}
	SET_BIT(UCSR2A,TXC);

}
/* this fun receive a byte and waits untill the data is empty to avoid overwriting */
u8 UART2_receiveByte (void)
{
	while (!GET_BIT(UCSR2A,7)){}
	/*
	 * wait until the last byte is received
	 */
	return UDR2;
}



void UART0_sendString (const u8 *str)
{
	while (*str != '\0')
	{
		UART0_sendByte(*str);
		str++;
	}
}


void UART0_receiveString (u8 *str)
{
	*str=UART0_receiveByte();
	while (*str != '#')
	{
		str++;
		*str=UART0_receiveByte();

	}
	*str='\0';

}


void UART1_sendString (const u8 *str)
{
	while (*str != '\0')
	{
		UART1_sendByte(*str);
		str++;
	}
}


void UART1_receiveString (u8 *str)
{
	*str=UART1_receiveByte();
	while (*str != '#')
	{
		str++;
		*str=UART1_receiveByte();

	}
	*str='\0';

}



void UART2_sendString (const u8 *str)
{
	while (*str != '\0')
	{
		UART2_sendByte(*str);
		str++;
	}
}


void UART2_receiveString (u8 *str)
{
	*str=UART2_receiveByte();
	while (*str != ',')
	{
		str++;
		*str=UART2_receiveByte();

	}
	*str='\0';

}

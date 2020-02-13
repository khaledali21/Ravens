#include "DDIO_128.h"
#include "STD_TYPES.h"
#include "UTILS.h"

void SetPinDir(u8 PinNumber,u8 PinDirection)
{
	u8 PortLetter = PinNumber/8;

	switch(PortLetter){
		case (0):
			if(PinDirection)
			SET_BIT(DDRA,PinNumber%8);
			else
			CLEAR_BIT(DDRA,PinNumber%8);
			break;

		case (1):
		    if(PinDirection)
			SET_BIT(DDRB,PinNumber%8);
	        else
			CLEAR_BIT(DDRB,PinNumber%8);
			break;

		case  (2):
			if(PinDirection)
			SET_BIT(DDRC,PinNumber%8);
			else
			CLEAR_BIT(DDRC,PinNumber%8);
            break;

		case (3):
			if(PinDirection)
			SET_BIT(DDRD,PinNumber%8);
			else
			CLEAR_BIT(DDRD,PinNumber%8);
			break;

		case (4):
			if(PinDirection)
			SET_BIT(DDRE,PinNumber%8);
			else
			CLEAR_BIT(DDRE,PinNumber%8);
			break;

		case (5):
			if(PinDirection)
			SET_BIT(DDRF,PinNumber%8);
			else
			CLEAR_BIT(DDRF,PinNumber%8);
			break;

		case (6):
			if(PinDirection)
			SET_BIT(DDRG,PinNumber%8);
			else
			CLEAR_BIT(DDRG,PinNumber%8);
			break;


	}
}





void SetPinVal(u8 PinNumber,u8 PinValue)
{
	u8 PortLetter = PinNumber/8;

	switch(PortLetter){
		case (0):
		   if(PinValue)
			   SET_BIT(PORTA,PinNumber%8);
		   else
			   CLEAR_BIT(PORTA,PinNumber%8);
				break;

		case (1):
			if(PinValue)
			    SET_BIT(PORTB,PinNumber%8);
			else
			    CLEAR_BIT(PORTB,PinNumber%8);
				break;

		case (2):
			if(PinValue)
				SET_BIT(PORTC,PinNumber%8);
			else
				CLEAR_BIT(PORTC,PinNumber%8);
         	 	break;

		case (3):
			if(PinValue)
				SET_BIT(PORTD,PinNumber%8);
			else
				CLEAR_BIT(PORTD,PinNumber%8);
        		break;

		case (4):
			if(PinValue)
				SET_BIT(PORTE,PinNumber%8);
			else
				CLEAR_BIT(PORTE,PinNumber%8);
        		break;

		case (5):
			if(PinValue)
				SET_BIT(PORTF,PinNumber%8);
			else
				CLEAR_BIT(PORTF,PinNumber%8);
				break;

		case (6):
			if(PinValue)
				SET_BIT(PORTG,PinNumber%8);
			else
				CLEAR_BIT(PORTG,PinNumber%8);
        		break;


	}

}

u8 ReadPinVal(u8 PinNumber)
{
	u8 PortLetter = PinNumber/8;

	switch(PortLetter)
	{
		case (0):
				return (GET_BIT(PINA,PinNumber%8));
				break;
		case (1):
				return (GET_BIT(PINB,PinNumber%8));
				break;
		case (2):
				return (GET_BIT(PINC,PinNumber%8));
				break;
		case (3):
				return (GET_BIT(PIND,PinNumber%8));
				break;
		case (4):
				return (GET_BIT(PINE,PinNumber%8));
				break;
		case (5):
				return (GET_BIT(PINF,PinNumber%8));
				break;
		case (6):
				return (GET_BIT(PING,PinNumber%8));
				break;
	}

}









/*
 * PREZIBEE
 *
 * Created: 22-08-2016 21:54:34
 * Author : rv
 */ 

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	
	
	uint8_t u8data = 0x00;
	uint8_t u8addr;
	
	
	void TWIInit(void) //initialization of TWI
	{
		//set SCL to 400kHz
		TWSR = 0x00;
		TWBR = 0x0C;
		//enable TWI
		TWCR = (1<<TWEN);
	}
	
	
	void TWIStart(void)//start signal
	{
		TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
		while ((TWCR & (1<<TWINT)) == 0);
	}
	
	void TWIStop(void)//stop TWI
	{
		TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
	}
	
	
	
	uint8_t TWIReadACK(void)
	{
		TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
		while ((TWCR & (1<<TWINT)) == 0);
		return TWDR;
	}
	
	
	uint8_t TWIGetStatus(void)
	{
		uint8_t status;
		//mask status
		status = TWSR & 0xF8;
		return status;
	}
	
		
	TWIInit();
    /* Replace with your application code */
    while (1) 
    {
		u8addr = 0b1101000;
		//correct
		
		TWIStart();//correct
		if (TWIGetStatus() != 0x08)
		{
			_delay_ms(1000);
			PORTD = 0xff;//correct
			_delay_ms(1000);//correct
			PORTD = 0x00;//correct
		}
		
		
		
		TWDR = 0b11010000;
		//Initiate Transfer
		TWCR=(1<<TWINT)|(1<<TWEN);

		//Poll Till Done
		while(!(TWCR & (1<<TWINT)));
		if (TWIGetStatus() != 0x18)
		{
			_delay_ms(1000);
			PORTD = 0xff;
			_delay_ms(1000);
			PORTD = 0x00;
		}
		
		//Initiate Transfer
		TWCR=(1<<TWINT)|(1<<TWSTA)|(1<<TWEN);

		//Poll Till Done
		while(!(TWCR & (1<<TWINT)));
		if (TWIGetStatus() != 0x10)
		{
			_delay_ms(1000);
			PORTD = 0xff;
			_delay_ms(1000);
			PORTD = 0x00;
		}
		
		
		
		TWDR = 0b11010001;
		//Initiate Transfer
		TWCR=(1<<TWINT)|(1<<TWEN);

		//Poll Till Done
		while(!(TWCR & (1<<TWINT)));
		while(TWIGetStatus() != 0x40);
		
		u8data = TWIReadACK();
		if (u8data == 0x00)
		{
			_delay_ms(1000);
			PORTD = 0xff;//correct
			_delay_ms(1000);//correct
			PORTD = 0x00;//correct
		}
		else
		PORTD = 0xf0;
		
		TWIStop();
		
		USART_Init(9600);
		USART_TransmitString("bluetooth HC06 code");
		
		USART_Transmitchar(uint8_t u8data);
		
    }
}


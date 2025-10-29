#include "stm32f446xx.h"

void delay(long d)
{
	while(d--);
}

void Printdata(unsigned char data)  // data = 8 bit hexadecimal data
{
	// Bit 0 => d0 // d0 = PA10
	if((data&0x01) == 0x01) { GPIOA->ODR |= (1<<10);     }
	else                    { GPIOA->ODR &= (~(1<<10));  }
	// Bit 0 => d1 // d1 = PB3
	if((data&0x02) == 0x02) { GPIOB->ODR |= (1<<3);    }
	else                    { GPIOB->ODR &= (~(1<<3)); }
	// Bit 0 => d2 // d2 = PB5
	if((data&0x04) == 0x04) { GPIOB->ODR |= (1<<5);    }
	else                    { GPIOB->ODR &= (~(1<<5)); }
	// Bit 0 => d3 // d3 = PB4
	if((data&0x08) == 0x08) { GPIOB->ODR |= (1<<4);    }
	else                    { GPIOB->ODR &= (~(1<<4)); }
	// Bit 0 => d4 // d4 = PB10
	if((data&0x10) == 0x10) { GPIOB->ODR |= (1<<10);   }
	else                    { GPIOB->ODR &= (~(1<<10));}
	// Bit 0 => d5 // d5 = PA8
	if((data&0x20) == 0x20) { GPIOA->ODR |= (1<<8);    }
	else                    { GPIOA->ODR &= (~(1<<8)); }
	// Bit 0 => d6 // d6 = PA9
	if((data&0x40) == 0x40) { GPIOA->ODR |= (1<<9);    }
	else                    { GPIOA->ODR &= (~(1<<9)); }
	// Bit 0 => d7 // d7 = PC7
	if((data&0x80) == 0x80) { GPIOC->ODR |= (1<<7);    }
	else                    { GPIOC->ODR &= (~(1<<7)); }
}

void Lcd_data(unsigned char data)
{
	Printdata(data);
	GPIOA->ODR = GPIOA->ODR & (~(1<<7));
	GPIOB->ODR = GPIOB->ODR | (1<<6);
	GPIOA->ODR = GPIOA->ODR | (1<<6);
	delay(80000);
	GPIOA->ODR = GPIOA->ODR & (~(1<<6));
}

void Lcd_Command(unsigned char command)
{
	Printdata(command);
	GPIOA->ODR = GPIOA->ODR & (~(1<<7));
	GPIOB->ODR = GPIOB->ODR & (~(1<<6));
	GPIOA->ODR = GPIOA->ODR | (1<<6);
	delay(80000);
	GPIOA->ODR = GPIOA->ODR & (~(1<<6));
}

void Lcd_String(char *str,unsigned char length)
{
	unsigned char i=0;
	for(i=0;i<length;i++)
	{
		Lcd_data(str[i]);
	}
}

void Lcd_Initialise(void)
{
	Lcd_Command(0x38);
	Lcd_Command(0x06);
	Lcd_Command(0x0C);
	Lcd_Command(0x01);
}

int main(void)
{
	RCC->AHB1ENR = RCC->AHB1ENR | (1<<0) | (1<<1) | (1<<2);  // Clock of GPIO's Enabled GPIOA, GPIOB, GPIOC
	
	GPIOA->MODER = GPIOA->MODER | (1<<12) | (1<<14) | (1<<16) | (1<<18) | (1<<20);
  GPIOA->MODER = GPIOA->MODER & (1<<13) & (1<<15) & (1<<17) & (1<<19) & (1<<21);   // PA10,PA9,PA8,PA6,PA7 as Output
	
	GPIOB->MODER = GPIOB->MODER | (1<<6) | (1<<8) | (1<<10) | (1<<12) | (1<<20);
  GPIOB->MODER = GPIOB->MODER & (1<<7) & (1<<9) & (1<<11) & (1<<13) &(1<<21);  // PB3,PB4,PB5,PB6,PB10 as Output
	
	GPIOC->MODER = GPIOC->MODER | (1<<14); 
  GPIOC->MODER = GPIOC->MODER & (1<<15);	// PC7 as Output
	
	Lcd_Initialise();
	
	while(1)
	{
		Lcd_Command(0x80);
		Lcd_String("Embedded",8);
		Lcd_Command(0xC0);
		Lcd_String("Systems",7);
	}
}
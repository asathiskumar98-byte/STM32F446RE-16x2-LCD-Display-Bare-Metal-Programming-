# 🖥️ STM32F446RE – 16x2 LCD Display (Bare Metal Programming)

## 📘 Project Overview
This project demonstrates how to **interface a 16x2 LCD display** with the **STM32F446RE** microcontroller using **bare-metal programming** in **Keil µVision**.  
All operations are performed using **register-level access** to the STM32 peripherals — **no HAL**, **no CubeMX**, just pure C and CMSIS.

The LCD is driven in **8-bit mode**, and data/command operations are handled via GPIO control.

---

## ⚙️ Hardware Setup

**Microcontroller:** STM32F446RE  
**IDE:** Keil µVision  
**Programming Type:** Bare Metal (Register-level)  
**LCD Type:** 16x2 Character LCD (HD44780 compatible)  
**Connection Mode:** 8-bit Parallel  

---

## 🧩 Pin Configuration

| LCD Pin | Signal | STM32 Pin | Port | Pin No. | Direction |
|----------|---------|------------|------|----------|------------|
| D0 | Data 0 | PA10 | GPIOA | 10 | Output |
| D1 | Data 1 | PB3  | GPIOB | 3  | Output |
| D2 | Data 2 | PB5  | GPIOB | 5  | Output |
| D3 | Data 3 | PB4  | GPIOB | 4  | Output |
| D4 | Data 4 | PB10 | GPIOB | 10 | Output |
| D5 | Data 5 | PA8  | GPIOA | 8  | Output |
| D6 | Data 6 | PA9  | GPIOA | 9  | Output |
| D7 | Data 7 | PC7  | GPIOC | 7  | Output |
| RS | Register Select | PA7 | GPIOA | 7 | Output |
| RW | Read/Write | PB6 | GPIOB | 6 | Output |
| EN | Enable | PA6 | GPIOA | 6 | Output |

---

## 🧠 Code Explanation

### 1️⃣ GPIO Clock Enable
```c
RCC->AHB1ENR |= (1<<0) | (1<<1) | (1<<2); // Enable clock for GPIOA, GPIOB, GPIOC

2️⃣ GPIO Mode Configuration

All LCD control and data pins are configured as output.

GPIOA->MODER |= (1<<12) | (1<<14) | (1<<16) | (1<<18) | (1<<20);
GPIOB->MODER |= (1<<6) | (1<<8) | (1<<10) | (1<<12) | (1<<20);
GPIOC->MODER |= (1<<14);

3️⃣ LCD Command & Data Flow
Command Function

Sends control instructions to the LCD.

void Lcd_Command(unsigned char command)
{
	Printdata(command);
	GPIOA->ODR &= ~(1<<7);  // RS = 0 for command
	GPIOB->ODR &= ~(1<<6);  // RW = 0 for write
	GPIOA->ODR |= (1<<6);   // EN = 1 (Enable pulse)
	delay(80000);
	GPIOA->ODR &= ~(1<<6);  // EN = 0
}

Data Function

Sends ASCII characters or data bytes to the LCD.

void Lcd_data(unsigned char data)
{
	Printdata(data);
	GPIOA->ODR |= (1<<7);   // RS = 1 for data
	GPIOB->ODR &= ~(1<<6);  // RW = 0 for write
	GPIOA->ODR |= (1<<6);   // EN = 1 (Enable pulse)
	delay(80000);
	GPIOA->ODR &= ~(1<<6);  // EN = 0
}

LCD Initialization
void Lcd_Initialise(void)
{
	Lcd_Command(0x38); // 8-bit, 2-line, 5x7 matrix
	Lcd_Command(0x06); // Increment cursor
	Lcd_Command(0x0C); // Display ON, cursor OFF
	Lcd_Command(0x01); // Clear display
}

💬 Display Output
Command	Action
0x80	Set cursor to first line
0xC0	Set cursor to second line
"Embedded"	Displayed on first line
"Systems"	Displayed on second line
🖼️ Output

LCD Display:

Embedded
Systems

🧩 Functions Summary
Function	Description
Printdata()	Maps 8-bit data to GPIO pins
Lcd_Command()	Sends LCD command instructions
Lcd_data()	Sends display characters
Lcd_String()	Displays string on LCD
Lcd_Initialise()	Initializes LCD configuration
🕹️ Working Principle

GPIO ports are configured as outputs.

LCD initialized with command set.

Data bytes (characters) are sent one by one to form text.

Enable (EN) pulse latches each data/command to the LCD.

🧠 Key Learning Points

Register-level programming using RCC, GPIO MODER, and ODR.

Understanding LCD 8-bit communication without libraries.

Timing control via manual enable pulse and software delay.

Writing clean modular functions for LCD display control.

🚀 Future Enhancements

Implement 4-bit LCD mode to reduce pin usage.

Use SysTick timer for accurate delays.

Add custom character display using CGRAM commands.

Integrate with sensors and show data dynamically on LCD.

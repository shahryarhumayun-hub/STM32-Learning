// Include stdint library to be able to use uint in this case we need uint32_t
#include <stdint.h>

//define all the peripheral base addresses necessary for this project
#define PERIPH_BASE (0x40000000UL)
#define AHB1PERIPH_BASE (PERIPH_BASE + 0x00020000UL)
#define APB1PERIPH_BASE (PERIPH_BASE + 0x00000000UL)
#define RCC_BASE (AHB1PERIPH_BASE + 0x00003800UL)
#define GPIOA_BASE (AHB1PERIPH_BASE + 0x00000000UL)
#define USART2_BASE (APB1PERIPH_BASE + 0x00004400UL)

//type def structures to easier access registers
typedef struct {
    volatile uint32_t MODER;
    volatile uint32_t OTYPER;
    volatile uint32_t OSPEEDR;
    volatile uint32_t PUPDR;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t LCKR;
    volatile uint32_t AFRL;
} GPIO_Typedef;

typedef struct {
    volatile uint32_t SR;
    volatile uint32_t DR;
    volatile uint32_t BRR;
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t CR3;
    volatile uint32_t GTPR;
} USART_Typedef;

typedef struct {
    volatile uint32_t dummy[12];
    volatile uint32_t AHB1ENR;
    volatile uint32_t dummy2[3];
    volatile uint32_t APB1ENR;
} RCC_Typedef;

//variables that connect structures to the base memory addresses for each peripheral
#define GPIOA  ((GPIO_Typedef *)  GPIOA_BASE)
#define USART2 ((USART_Typedef *) USART2_BASE)
#define RCC    ((RCC_Typedef *)   RCC_BASE)
#define RCC_AHB1ENR_GPIOAEN  (1 << 0)
#define RCC_APB1ENR_USART2EN (1 << 17)

// Function for sending one character to the Data Register, it waits until the Status Register is ready.
// Thereafter it sends the character out the TX pin.
void uart_send_char(char c)
{
    while(!(USART2->SR & (1 << 7)));
    USART2->DR = c;
}

// Wrapper function for the uart_send_char function.
// Here it loops through all of the memory addresses that the string contains.
void uart_send_string(char *str)
{
    while (*str)
    {
        uart_send_char(*str);
        str++;
    }
}

// Function that takes a binary value from a register and serial prints.
// Primarily used to debug and read register values
void uart_send_binary(uint32_t value)
{
	for (int i = 31; i >= 0; i--)
	{
		if (value & 1 << i)
			uart_send_string("1");
		else uart_send_string("0");
	}
	uart_send_string("\r\n");
}

int main(void)
{
	// Starting the clocks for GPIOA and USART2 peripheral.
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
    // Small delay to let clocks stabilize before configuring peripherals
    for(int i = 0; i < 1000; i++);

    // Set bits in the MODER register that control PA 2's mode to 00 (input), this is a precaution in case the bits have a different state in startup.
    GPIOA->MODER &= ~(3 << 4); // 00
    // Set bits in the MODER register that control PA 2's mode to 10 (alternate function). this is what is necessary if we are going to use USART.
    GPIOA->MODER |=  (2 << 4); //10

    // Set bits in the MODER register that control PA 3's mode to 00 (input).
    GPIOA->MODER &= ~(3 << 6); //00
    // Set bits in the MODER register that control PA 3's mode to 10 (alternate function).
    GPIOA->MODER |=  (2 << 6); //10

    // Set the bits of PA 2's Alternate function register lower to 0000.
    GPIOA->AFRL &= ~(0xF << 8); // 0000
    // Set the bits of the Alternate function register lower to 1110 = 7.
    // Set PA 2's alternate function register lower to 7, in this configuration PA 2 will use USART2
    GPIOA->AFRL |=  (7 << 8);

    // Set the bits of PA 3's Alternate function register lower to 0000.
    GPIOA->AFRL &= ~(0xF << 12);
    // Set the bits of the Alternate function register lower to 1110 = 7.
    // Set PA 3's alternate function register lower to 7, in this configuration PA 2 will use USART2
    GPIOA->AFRL |=  (7 << 12);

    // Set the Baud Rate Register 139 which is 16MHz / 115200 baudrate.
    USART2->BRR = 139;
    // Set bit 3 to 1, enables transmission
    USART2->CR1 |= (1 << 3);
    // set bit 13 to 1, enables USART2
    USART2->CR1 |= (1 << 13);

    // USART2 Status Register read and print
    uart_send_binary(USART2->SR);

    // System initialization check
    uart_send_string("System initialized");

    for(;;)
    {
    	// serial prints and loops after delay.
        uart_send_string("Hello from STM32!\r\n");
        for(int i = 0; i < 1000000; i++);
    }
}

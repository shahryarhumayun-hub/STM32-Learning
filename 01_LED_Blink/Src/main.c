// Include stdint library to be able to use uint32_t
#include <stdint.h>

// Define all peripheral base addresses required for this project
#define PERIPH_BASE     (0x40000000UL)
#define AHB1PERIPH_BASE (PERIPH_BASE + 0x00020000UL)
#define RCC_BASE        (AHB1PERIPH_BASE + 0x3800UL)
#define GPIOA_BASE      (AHB1PERIPH_BASE + 0x0000UL)

// Type def structures to easier access registers
typedef struct {
    volatile uint32_t MODER;
    volatile uint32_t OTYPER;
    volatile uint32_t OSPEEDR;
    volatile uint32_t PUPDR;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
} GPIO_TypeDef;

typedef struct {
    volatile uint32_t dummy[12];
    volatile uint32_t AHB1ENR;
} RCC_TypeDef;

// Variables that connect structures and base memory addresses
#define GPIOA ((GPIO_TypeDef *) GPIOA_BASE)
#define RCC ((RCC_TypeDef *) RCC_BASE)

// Variable that holds bit mask needed to enable the clock for AHB1
#define RCC_AHB1ENR_GPIOAEN (1 << 0)

int main(void)
{
	// Enabling the clock for GPIOA which is on the AHB1 bus
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

	// Set the Moder pins for PA5.
	// Set the bits responsible for PA5's mode to 00
	GPIOA->MODER &= ~(3 << 10); // 00
	// Set bit 10 to 1, that way the bits reponsible for PA5's state will be 01 (output)
	GPIOA->MODER |= (1 << 10); // 01



	for(;;)
	{
		// Switches the bit state og bit 5 in Output data register, which in turn makes PA5 HIGH or LOW depending on what it was prior.
		// In the reference manual it says that the bit will normaly be set to 0 which means that in the first loop it will turn on.
		GPIOA->ODR ^= (1 << 5);
		// Small delay before loop starts anew.
		for(int i = 0; i < 500000; i++);
	}
}

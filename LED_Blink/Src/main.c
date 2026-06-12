#include <stdint.h>

#define PERIPH_BASE     (0x40000000UL)
#define AHB1PERIPH_BASE (PERIPH_BASE + 0x00020000UL)
#define RCC_BASE        (AHB1PERIPH_BASE + 0x3800UL)
#define GPIOA_BASE      (AHB1PERIPH_BASE + 0x0000UL)

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

#define GPIOA ((GPIO_TypeDef *) GPIOA_BASE)
#define RCC ((RCC_TypeDef *) RCC_BASE)

#define RCC_AHB1ENR_GPIOAEN (1 << 0)

int main(void)
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

	GPIOA->MODER |= (1 << 10);
	GPIOA->MODER &= ~(1 << 11);

	for(;;)
	{
		GPIOA->ODR ^= (1 << 5);

		for(int i = 0; i < 500000; i++);
	}
}

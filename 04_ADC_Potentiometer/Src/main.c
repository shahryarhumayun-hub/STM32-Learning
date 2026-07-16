#include <stdint.h>

/* ========================== Peripheral base addresses ========================== */
#define PERIPH_BASE 	(0x40000000UL)
#define AHB1PERIPH_BASE (PERIPH_BASE + 0x00020000UL)
#define APB1PERIPH_BASE (PERIPH_BASE + 0x00000000UL)
#define APB2PERIPH_BASE (PERIPH_BASE + 0x00010000UL)

#define RCC_BASE 		(AHB1PERIPH_BASE + 0x00003800UL)
#define GPIOA_BASE 		(AHB1PERIPH_BASE + 0x00000000UL)
#define USART2_BASE 	(APB1PERIPH_BASE + 0x00004400UL)
#define ADC1_BASE 		(APB2PERIPH_BASE + 0x00002000UL)

/* ========================== Peripheral register structures ==========================*/
typedef struct{
	volatile uint32_t CR;
	volatile uint32_t PLLCFGR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t AHB1RSTR;
	volatile uint32_t AHB2RSTR;
	volatile uint32_t AHB3RSTR;
	uint32_t RESERVED0;
	volatile uint32_t APB1RSTR;
	volatile uint32_t APB2RSTR;
	uint32_t RESERVED1[2];
	volatile uint32_t AHB1ENR;
	volatile uint32_t AHB2ENR;
	volatile uint32_t AHB3ENR;
	uint32_t RESERVED2;
	volatile uint32_t APB1ENR;
	volatile uint32_t APB2ENR;
}RCC_Typedef;

typedef struct{
	volatile uint32_t MODER;
	volatile uint32_t OTYPER;
	volatile uint32_t OSPEEDR;
	volatile uint32_t PUPDR;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t LCKR;
	volatile uint32_t AFR[2]; // AFR[0] = AFRL, AFR[1] = AFRH
}GPIO_Typedef;

typedef struct{
	volatile uint32_t SR;
	volatile uint32_t DR;
	volatile uint32_t BRR;
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t CR3;
	volatile uint32_t GTPR;
}USART_Typedef;

typedef struct{
	volatile uint32_t SR;
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t SMPR1;
	volatile uint32_t SMPR2;
	volatile uint32_t JOFR1;
	volatile uint32_t JOFR2;
	volatile uint32_t JOFR3;
	volatile uint32_t JOFR4;
	volatile uint32_t HTR;
	volatile uint32_t LTR;
	volatile uint32_t SQR1;
	volatile uint32_t SQR2;
	volatile uint32_t SQR3;
	volatile uint32_t JSQR;
	volatile uint32_t JDR1;
	volatile uint32_t JDR2;
	volatile uint32_t JDR3;
	volatile uint32_t JDR4;
	volatile uint32_t DR;
}ADC_Typedef;

/* ========================== Peripheral pointers ========================== */

#define RCC ((RCC_Typedef *) RCC_BASE)

#define GPIOA ((GPIO_Typedef *) GPIOA_BASE)
#define USART2 ((USART_Typedef *) USART2_BASE)
#define ADC1 ((ADC_Typedef *) ADC1_BASE)

/* ========================== Bit definitions ==========================*/

#define RCC_AHB1ENR_GPIOAEN 	(1U << 0)
#define RCC_APB1ENR_USART2EN 	(1U << 17)
#define RCC_APB2ENR_ADC1EN 		(1U << 8)

#define GPIO_MODER_RESET 		(3U)
#define GPIO_MODER_AF 			(2U)
#define GPIO_MODER_ANALOG 		(3U)

/* ========================== MAIN ========================== */
int main(void){
	// Enable clocks
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;

	//Set PA1 to analog
	GPIOA->MODER &= ~(GPIO_MODER_RESET << 2);
	GPIOA->MODER |= (GPIO_MODER_ANALOG << 2);

	//Set PA2 and PA3 to alternate function
	GPIOA->MODER

	for(;;){

	}
}































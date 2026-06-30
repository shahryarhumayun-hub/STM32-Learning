#include <stdint.h>

/* ======================Peripheral base addresses ====================== */
#define PERIPH_BASE (0x40000000UL)
#define AHB1PERIPH_BASE (PERIPH_BASE + 0x00020000UL)
#define APB1PERIPH_BASE (PERIPH_BASE + 0x00000000UL)

#define RCC_BASE (AHB1PERIPH_BASE + 0x00003800UL)
#define GPIOB_BASE (AHB1PERIPH_BASE + 0x00000800UL)
#define I2C1_BASE (APB1PERIPH_BASE + 0x00005400UL)

/* ========================= Peripheral register structures ========================= */
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
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t OAR1;
	volatile uint32_t OAR2;
	volatile uint32_t DR;
	volatile uint32_t SR1;
	volatile uint32_t SR2;
	volatile uint32_t CCR;
	volatile uint32_t TRISE;
	volatile uint32_t FLTR;
}I2C_Typedef;

/* ========================= Peripheral pointers ========================= */
#define RCC ((RCC_Typedef *) RCC_BASE)
#define GPIOB ((GPIO_Typedef *) GPIOB_BASE)
#define I2C1 ((I2C_Typedef *) I2C1_BASE)

/* ========================= Bit definitions =========================*/

/* RCC */
#define RCC_AHB1ENR_GPIOBEN (1U << 1)
#define RCC_APB1ENR_I2C1EN 	(1U << 21)

/* GPIO */
#define GPIO_MODER_AF 		(2U)
#define GPIO_MODER_RESET 	(3U) //for setting MODER pins to 00 first
#define GPIO_OTYPER_OD 		(1U)
#define GPIO_AFR_AF4		(4U)
#define GPIO_OSPEEDR_HIGH	(3U)

/* I2C */
#define I2C_CR1_PE		(1U << 0)
#define I2C_CR1_START	(1U << 8)
#define I2C_CR1_STOP	(1U << 9)
#define I2C_CR1_ACK		(1U << 10)
#define I2C_CR2_FREQ    (16U << 0)
#define I2C_SR1_SB      (1U << 0)
#define I2C_SR1_ADDR	(1U << 1)
#define I2C_SR1_TXE		(1U << 7)
#define I2C_SR1_BTF		(1U << 2)



int main(void){
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
	RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;

	GPIOB->MODER &= ~(GPIO_MODER_RESET << 16);
	GPIOB->MODER |= (GPIO_MODER_AF << 16);

	GPIOB->MODER &= ~(GPIO_MODER_RESET << 18);
	GPIOB->MODER |= (GPIO_MODER_AF << 18);

	GPIOB->AFR[1] &= ~(0xF << 0);
	GPIOB->AFR[1] |= (GPIO_AFR_AF4 << 0);

	GPIOB->AFR[1] &= ~(0xF << 4);
	GPIOB->AFR[1] |= (GPIO_AFR_AF4 << 4);

	GPIOB->OTYPER &= ~(1 << 8);
	GPIOB->OTYPER |= (GPIO_OTYPER_OD << 8);

	GPIOB->OTYPER &= ~(1 << 9);
	GPIOB->OTYPER |= (GPIO_OTYPER_OD << 9);

	GPIOB->OSPEEDR &= ~(3 << 16);
	GPIOB->OSPEEDR |= (GPIO_OSPEEDR_HIGH << 16);

	GPIOB->OSPEEDR &= ~(3 << 18);
	GPIOB->OSPEEDR |= (GPIO_OSPEEDR_HIGH << 18);

	// Start by disabling the peripheral so that we are able to edit
	I2C1->CR1 &= ~I2C_CR1_PE;

	// Set APB1 clock frequency in Mhz (16Mhz)
	I2C1->CR2 |= I2C_CR2_FREQ;

	// Set clock control register for 100khz standard mode
	// CCR = 16 000 000 / (2 * 100 000) = 80
	I2C1->CCR = 80U;

	// Set maximum rise time
	// TRISE = (1000ns * 16MHz) + 1 = 17
	I2C1->TRISE = 17U;

	// Enable peripheral
	I2C1->CR1 |= I2C_CR1_PE;

	for(;;){

	}
}


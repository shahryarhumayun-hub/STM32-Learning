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
	volatile uint32_t OSPEEDER;
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
#define RCC_AHB1ENR_GPIOBEN (1U << 1)
#define RCC_APB1ENR_I2C1EN (1U << 21)


int main(void){


	for(;;){

	}
}


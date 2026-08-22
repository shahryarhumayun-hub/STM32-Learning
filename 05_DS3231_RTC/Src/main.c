#include <stdint.h>
/* ===================================================================================== Peripheral base addresses ===================================================================================== */
#define PERIPH_BASE 	(0x40000000UL)
#define AHB1PERIPH_BASE (PERIPH_BASE + 0x00020000UL)
#define APB1PERIPH_BASE (PERIPH_BASE + 0x00000000UL)

#define RCC_BASE 		(AHB1PERIPH_BASE + 0x00003800UL)
#define GPIOB_BASE 		(AHB1PERIPH_BASE + 0x00000400UL)
#define GPIOA_BASE 		(AHB1PERIPH_BASE + 0x00000000UL)
#define I2C1_BASE 		(APB1PERIPH_BASE + 0x00005400UL)
#define USART2_BASE 	(APB1PERIPH_BASE + 0x00004400UL)

/* ===================================================================================== Peripheral register structures ===================================================================================== */
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

typedef struct{
	volatile uint32_t SR;
	volatile uint32_t DR;
	volatile uint32_t BRR;
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t CR3;
	volatile uint32_t GTPR;
}USART_Typedef;

/* ===================================================================================== Peripheral pointers ===================================================================================== */

#define RCC 	((RCC_Typedef *) RCC_BASE)
#define GPIOA ((GPIO_Typedef *) GPIOA_BASE)
#define GPIOB 	((GPIO_Typedef *) GPIOB_BASE)
#define USART2 	((USART_Typedef *) USART2_BASE)
#define I2C1 	((I2C_Typedef *) I2C1_BASE)

/* ===================================================================================== Bit definitions ===================================================================================== */
#define RCC_AHB1ENR_GPIOAEN 	(1U << 0)
#define RCC_AHB1ENR_GPIOBEN 	(1U << 1)
#define RCC_APB1ENR_USART2EN 	(1U << 17)
#define RCC_APB1ENR_I2C1EN 		(1U << 21)

#define GPIO_MODER_RESET 		(3U)
#define GPIO_MODER_AF 			(2U)
#define GPIO_AFR_AF7 			(7U)
#define GPIO_AFR_AF4			(4U)
#define GPIO_AFR_RESET 			(0xF)
#define GPIO_OTYPER_OD			(1U)
#define GPIO_OSPEEDR_HIGH		(3U)
#define GPIO_PUPDR_PU			(1U)

#define USART_SR_TXE 			(1U << 7)

#define I2C_CR1_PE      (1U << 0)
#define I2C_CR1_START   (1U << 8)
#define I2C_CR1_STOP    (1U << 9)
#define I2C_CR1_ACK     (1U << 10)
#define I2C_CR2_FREQ    (16U)
#define I2C_SR1_SB      (1U << 0)
#define I2C_SR1_ADDR    (1U << 1)
#define I2C_SR1_TXE     (1U << 7)
#define I2C_SR1_BTF     (1U << 2)
#define I2C_SR1_RXNE    (1U << 6)
#define I2C_SR2_BUSY 	(1U << 1)

#define DS3231_ADDR		(0x68)
#define DS3231_ADDR_W 	(DS3231_ADDR << 1)
#define DS3231_ADDR_R	((DS3231_ADDR << 1) | 1U)
#define DS3231_SR 		(0x00)
#define DS3231_MR 		(0x01)
#define DS3231_HR		(0x02)


/* ===================================================================================== Functions ===================================================================================== */

/* ======================================== USART functions ======================================== */
void uart_send_char(char c){
	while(!(USART2->SR & USART_SR_TXE));
	USART2->DR = c;
}

void uart_send_string(char *str){
	while(*str)
	{
		uart_send_char(*str);
		str++;
	}
}

/*
Function takes a uint8 value and prints this binary value out the uart.
it does this by checking each bit and depending on what it is writes 1 or 0 to the uart.
*/
void uart_send_uint8(uint8_t value){
	for (int i = 7; i >= 0; i--)
	{
		if (value & (1U << i))
			uart_send_char('1');
		else
			uart_send_char('0');
	}
	uart_send_string("\r\n");
}

/*
Function takes a uint8 value and prints it out uart in a decimal format.
f.eks 00001110 = 14
first it extracts 1 by dividing with 10 and then adds '0' to turn it into the ASCII value of 1.

*/
void uart_send_uint8_decimal(uint8_t value){
	uart_send_char((value / 10) + '0');
	uart_send_char((value % 10) + '0');
}

/* ======================================== I2C Functions ======================================== */
void i2c_start(void){
	I2C1->CR1 |= I2C_CR1_START;

	while(!(I2C1->SR1 & I2C_SR1_SB));
}

void i2c_stop(void)
{
    I2C1->CR1 |= I2C_CR1_STOP;
}

void i2c_send_address(uint8_t address){
	I2C1->DR = address;
	while (!(I2C1->SR1 & I2C_SR1_ADDR));
	(void)I2C1->SR2;
}

void i2c_write_byte(uint8_t data){
	while(!(I2C1->SR1 & I2C_SR1_TXE));
	I2C1->DR = data;
	while(!(I2C1->SR1 & I2C_SR1_BTF));
}




/* ======================================== DS3231 Functions ======================================== */


uint8_t decimal_to_bcd(uint8_t decimal){
	return ((decimal / 10) << 4) | (decimal % 10);
}


uint8_t bcd_to_decimal(uint8_t bcd){
	return ((bcd >> 4) & 0x0F) * 10 + (bcd & 0x0F);
	//     ^does this need to be here?^
}


void ds3231_set_time(uint8_t hours, uint8_t minutes, uint8_t seconds){
	i2c_start();
	i2c_send_address(DS3231_ADDR_W);
	i2c_write_byte(0x00);
	i2c_write_byte(decimal_to_bcd(seconds));
	i2c_write_byte(decimal_to_bcd(minutes));
	i2c_write_byte(decimal_to_bcd(hours));
	i2c_stop();
	uart_send_string("Time set!!!\r\n");
}


void ds3231_print_time(uint8_t reg){
    uint8_t time;

    /* Tell DS3231 which register we want */
    i2c_start();

    i2c_send_address(DS3231_ADDR_W);

    i2c_write_byte(reg);

    /* Switch from write to read */
    i2c_start();

    i2c_send_address(DS3231_ADDR_R);

    /* We only want one byte */
    I2C1->CR1 &= ~I2C_CR1_ACK;

    /* Wait for DS3231 to send it */
    while (!(I2C1->SR1 & I2C_SR1_RXNE));

    /* Read the byte */
    time = I2C1->DR;

    /* End transaction */
    i2c_stop();

    uart_send_uint8_decimal(bcd_to_decimal(time));
}


uint8_t ds3231_read_seconds(void)
{
    uint8_t seconds;

    /* Tell DS3231 which register we want */
    i2c_start();

    i2c_send_address(DS3231_ADDR_W);

    i2c_write_byte(0x00);

    /* Switch from write to read */
    i2c_start();

    i2c_send_address(DS3231_ADDR_R);

    /* We only want one byte */
    I2C1->CR1 &= ~I2C_CR1_ACK;

    /* Wait for DS3231 to send it */
    while (!(I2C1->SR1 & I2C_SR1_RXNE));

    /* Read the byte */
    seconds = I2C1->DR;

    /* End transaction */
    i2c_stop();

    return seconds;
}

/* ===================================================================================== MAIN ===================================================================================== */
int main (void){
	// Enable clocks
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
	RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;

	for(int i = 0; i < 1000; i++);

/* ======================================== USART2 configuration + GPIO ======================================== */
	//Set PA2 and PA3 to alternate function and configure to AF7
	//PA2
	GPIOA->MODER &= ~(GPIO_MODER_RESET << 4);
	GPIOA->MODER |= (GPIO_MODER_AF << 4);
	GPIOA->AFR[0] &= ~(GPIO_AFR_RESET << 8);
	GPIOA->AFR[0] |= (GPIO_AFR_AF7 << 8);

	//PA3
	GPIOA->MODER &= ~(GPIO_MODER_RESET << 6);
	GPIOA->MODER |= (GPIO_MODER_AF << 6);
	GPIOA->AFR[0] &= ~(GPIO_AFR_RESET << 12);
	GPIOA->AFR[0] |= (GPIO_AFR_AF7 << 12);

	// Set the Baud Rate Register 139 which is 16MHz / 115200 baudrate.
	USART2->BRR = 139;
	// Set bit 3 to 1, enables transmission
	USART2->CR1 |= (1 << 3);
	// set bit 13 to 1, enables USART2
	USART2->CR1 |= (1 << 13);

	uart_send_string("USART configuration done!\r\n");

/* ======================================== I2C1 configuration + GPIO ======================================== */
	//PB8
	GPIOB->MODER &= ~(GPIO_MODER_RESET << 16);
	GPIOB->MODER |= (GPIO_MODER_AF << 16);

	GPIOB->OTYPER &= ~(1U << 8);
	GPIOB->OTYPER |= (GPIO_OTYPER_OD << 8);

	GPIOB->OSPEEDR &= ~(3U << 16);
	GPIOB->OSPEEDR |= (GPIO_OSPEEDR_HIGH << 16);

	GPIOB->PUPDR &= ~(3U << 16);
	GPIOB->PUPDR |= (GPIO_PUPDR_PU << 16);

	GPIOB->AFR[1] &= ~(GPIO_AFR_RESET << 0);
	GPIOB->AFR[1] |= (GPIO_AFR_AF4 << 0);

	//PB9
	GPIOB->MODER &= ~(GPIO_MODER_RESET << 18);
	GPIOB->MODER |= (GPIO_MODER_AF << 18);

	GPIOB->OTYPER &= ~(1U << 9);
	GPIOB->OTYPER |= (GPIO_OTYPER_OD << 9);

	GPIOB->OSPEEDR &= ~(3U << 18);
	GPIOB->OSPEEDR |= (GPIO_OSPEEDR_HIGH << 18);

	GPIOB->PUPDR &= ~(3U << 18);
	GPIOB->PUPDR |= (GPIO_PUPDR_PU << 18);

	GPIOB->AFR[1] &= ~(GPIO_AFR_RESET << 4);
	GPIOB->AFR[1] |= (GPIO_AFR_AF4 << 4);

	//I2C
	I2C1->CR1 &= ~(I2C_CR1_PE); //Disable I2C1
	I2C1->CR2 = 16U;
	I2C1->CCR = 80U;
	I2C1->TRISE = 17U;
	I2C1->CR1 |= (I2C_CR1_PE); //Enable I2C1
	uart_send_string("I2C configuration done!\r\n");


	uart_send_string("\r\n");
	ds3231_set_time(14, 15, 32);

	uart_send_string("Time: ");
	ds3231_print_time(DS3231_HR);
	uart_send_string(":");
	ds3231_print_time(DS3231_MR);
	uart_send_string(":");
	ds3231_print_time(DS3231_SR);
	uart_send_string("\r\n");

	for(;;){
	}
}






















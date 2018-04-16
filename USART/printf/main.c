#include "stm32f10x.h"
#include "stm32f10x_conf.h"
#include "usart.h"
#include "time.h"

void delay(uint32_t delay_count)
{
	while (delay_count) delay_count--;
}
void init_led()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	/* GPIOA Periph clock enable */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	/* Configure PA0 and PA1 in output pushpull mode */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

}
void gpio_toggle(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	GPIOx->ODR ^= GPIO_Pin;
}

void send_byte(uint8_t b)
{   
	/* Send one byte */
	USART_SendData(USART1, b);

	/* Loop until USART2 DR register is empty */
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}
void send_string(uint8_t *str)
{
	while ((*str) != '\0') {

		send_byte(*str);
		str++;
	}
}
void ClockSource_check(void)
{
	if (RCC->CR & RCC_CR_HSERDY)
	{
		printf("Xtal: extern \r\n");
	}
	else
	{
		printf("Xtal:No check extern\r\n");
	}	
}

 RCC_ClocksTypeDef RCC_Clocks;

int main(void)
{
	init_led();
	init_usart1();

	char buf[8]={0};
	char buf2[8]={0};
	char *str = "test c-style string";
	char ch = 'a';
	int num = 100;
    
    printf(str);
	
	System_tim2_init();

	Delay_ms(100);
	
	// puts("start test printf!\r\n");
 //    	puts("test puts");
 //    	puts("test printf:\r\n");
 //    	printf("test string = %s\r\ntest ch = %c\r\ntest decimal number = %d\r\ntest hex number = %x\r\n", str, ch, num, num);
	// printf("test utoa: 100=%s, -100=%s\r\n", utoa(100, buf, 10), utoa(-100, buf2, 10));
	// printf("test itoa: 100=%s, -100=%s\r\n", itoa(100, buf, 10), itoa(-100, buf2, 10)); 
    RCC_GetClocksFreq(&RCC_Clocks);                   /*  µÃµ½ÏµÍ³Ê±ÖÓµÄ´óÐ¡ */
	printf("CPU: SYSCLK: %dMHz, HCLK: %dMHz, PCLK1: %dMHz, PCLK2: %dMHz\r\n",
		 RCC_Clocks.SYSCLK_Frequency/1000000,
		 RCC_Clocks.HCLK_Frequency/1000000,
		 RCC_Clocks.PCLK1_Frequency/1000000, 
		 RCC_Clocks.PCLK2_Frequency/1000000
		);
	ClockSource_check();
    while(1) {
    	//delay(0xfffff);
        //gpio_toggle(GPIOB, GPIO_Pin_14);
        //gpio_toggle(GPIOB, GPIO_Pin_15);
    }


}


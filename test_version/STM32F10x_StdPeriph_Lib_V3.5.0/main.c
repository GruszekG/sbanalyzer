#include "stm32F10x.h"

void RCC_Setup(void);
void GPIO_Setup(void);

int main(void){
	int i;
	RCC_Setup();
	GPIO_Setup();

	GPIO_SetBits(GPIOC, GPIO_Pin_9);

	while(1)
	{
		GPIO_SetBits(GPIOC, GPIO_Pin_8);
		for(i=0;i<10000000;i++)
		{
		}
		i=0;

		GPIO_ResetBits(GPIOC, GPIO_Pin_8);
		for(i=0;i<10000000;i++)
		{
		}
		i=0;
			
	}	
	
  	//while(1);
}

void RCC_Setup(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	
}

void GPIO_Setup(){

	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_8;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	
	GPIO_Init( GPIOC, &GPIO_InitStruct );
}

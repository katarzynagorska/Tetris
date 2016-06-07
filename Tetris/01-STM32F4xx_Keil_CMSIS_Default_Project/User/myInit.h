//void Clock_HSE_Configuration(void);
//void Clock_HSI_Configuration(void);
//void Clock_PLL_Configuration(void);


//void GPIO_Configuration(void);

//void EXTI_Configuration(void);
/*
void Clock_HSI_Configuration(){
	RCC_DeInit();
	
	RCC_HSICmd(ENABLE);
	RCC_SYSCLKConfig(RCC_SYSCLKSource_HSI);
	
	while (RCC_GetFlagStatus(RCC_FLAG_HSIRDY) != SET);

}

	void Clock_HSE_Configuration(){
	RCC_DeInit();
	
	RCC_HSEConfig(RCC_HSE_ON);
	RCC_SYSCLKConfig(RCC_SYSCLKSource_HSE);
	
	while (RCC_WaitForHSEStartUp() != SUCCESS);
	while (RCC_GetFlagStatus(RCC_FLAG_HSERDY) != SET);
	RCC_HSICmd(DISABLE);
}	
	*/
void my_Clock_PLL_Configuration(){
	RCC_DeInit();
	
	RCC_HSEConfig(RCC_HSE_ON);
	RCC_SYSCLKConfig(RCC_SYSCLKSource_HSE);
	
	while (RCC_WaitForHSEStartUp() != SUCCESS);
	while (RCC_GetFlagStatus(RCC_FLAG_HSERDY) != SET);
	
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
	RCC_PLLConfig(RCC_PLLSource_HSE, 4, 200, 4, 4);
	RCC_PLLCmd(ENABLE);
	RCC_HCLKConfig(RCC_SYSCLK_Div1);
	RCC_PCLK1Config(RCC_HCLK_Div2);
	RCC_PCLK2Config(RCC_HCLK_Div1);
	while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) != SET);
}


void my_GPIO_Configuration()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	/* Input pins for custom switches */
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
		/* Input pins for switches */
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}
/*
void EXTI_Configuration(void)
{
//inicjalizacja struktury konfiguracji przerwan EXTI
 EXTI_InitTypeDef EXTI_InitStructure;
//aktywowanie funkcji EXTI pinów joystick’a
 GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource8);
 GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource9);
 GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource10);
 GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource11);
 GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource12);
 EXTI_InitStructure.EXTI_Line = EXTI_Line8 | EXTI_Line9 | EXTI_
Line10 | EXTI_Line11 | EXTI_Line12;
 EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
//przerwanie przy zboczu opadajacym
 EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
//uaktywnienie kontrolera EXTI
 EXTI_InitStructure.EXTI_LineCmd = ENABLE;
 EXTI_Init(&EXTI_InitStructure);
}*/

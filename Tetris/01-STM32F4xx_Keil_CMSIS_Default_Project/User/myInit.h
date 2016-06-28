#include "tm_stm32f4_delay.h"	
#include "tm_stm32f4_disco.h"	
#include "tm_stm32f4_rng.h"


#define   APB1_FREQ        42000000                           // Clock driving TIM3
#define   CNT_FREQ         21000000                           // TIM3 counter clock (prescaled APB1)
#define   IT_PER_SEC       1                               // Interrupts per second
#define   TIM3_PULSE       ((CNT_FREQ) / (IT_PER_SEC))        // Output compare reg value
#define   TIM_PRESCALER    (((APB1_FREQ) / (CNT_FREQ))-1)     // APB1 prescaler
#define  	CLK_FREQ 					16800000

//void my_Clock_PLL_Configuration(void);
//void Configure_PE0(void);
//void Configure_PE1(void);
//void Configure_PE2(void)
//void Configure_PE4(void);
//void Configure_TIM3(void);
//void Init(void);


void my_Clock_PLL_Configuration(){
		RCC_DeInit();

		RCC_HSEConfig(RCC_HSE_ON);
		RCC_SYSCLKConfig(RCC_SYSCLKSource_HSE);

		while (RCC_WaitForHSEStartUp() != SUCCESS);
		while (RCC_GetFlagStatus(RCC_FLAG_HSERDY) != SET);

	
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
// Configure the PLL for 168MHz SysClk and 48MHz for USB OTG, SDIO
  RCC_PLLConfig(RCC_PLLSource_HSE, 8, 336, 2, 7);

	RCC_PLLCmd(ENABLE);

				// AHB 168MHz28
        RCC_HCLKConfig(RCC_SYSCLK_Div1);
        // APB1 42MHz
        RCC_PCLK1Config(RCC_HCLK_Div4);
        // APB2 84MHz
        RCC_PCLK2Config(RCC_HCLK_Div2);

	while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) != SET);
				
	}

	void Configure_PE0(){

		/* Set variables used */
		GPIO_InitTypeDef GPIO_InitStruct;
		EXTI_InitTypeDef EXTI_InitStruct;
		NVIC_InitTypeDef NVIC_InitStruct;

		/* Enable clock for GPIOE */
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
		/* Enable clock for SYSCFG */
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

		/* Set pin as input */
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
		GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
		GPIO_Init(GPIOE, &GPIO_InitStruct);

		/* Tell system that you will use PD0 for EXTI_Line0 */
		SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource0);

		/* PD0 is connected to EXTI_Line0 */
		EXTI_InitStruct.EXTI_Line = EXTI_Line0;
		/* Enable interrupt */
		EXTI_InitStruct.EXTI_LineCmd = ENABLE;
		/* Interrupt mode */
		EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
		/* Triggers on rising and falling edge */
		EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
		/* Add to EXTI */
		EXTI_Init(&EXTI_InitStruct);

		/* Add IRQ vector to NVIC */
		/* PD0 is connected to EXTI_Line0, which has EXTI0_IRQn vector */
		NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn;
		/* Set priority */
		NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x00;
		/* Set sub priority */
		NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x00;
		/* Enable interrupt */
		NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
		/* Add to NVIC */
		NVIC_Init(&NVIC_InitStruct);
	}

	void Configure_PE2(){

		/* Set variables used */
		GPIO_InitTypeDef GPIO_InitStruct;
		EXTI_InitTypeDef EXTI_InitStruct;
		NVIC_InitTypeDef NVIC_InitStruct;

		/* Enable clock for GPIOE */
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
		/* Enable clock for SYSCFG */
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

		/* Set pin as input */
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
		GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
		GPIO_Init(GPIOE, &GPIO_InitStruct);

		/* Tell system that you will use PD0 for EXTI_Line0 */
		SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource2);

		/* PD0 is connected to EXTI_Line0 */
		EXTI_InitStruct.EXTI_Line = EXTI_Line2;
		/* Enable interrupt */
		EXTI_InitStruct.EXTI_LineCmd = ENABLE;
		/* Interrupt mode */
		EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
		/* Triggers on rising and falling edge */
		EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
		/* Add to EXTI */
		EXTI_Init(&EXTI_InitStruct);

		/* Add IRQ vector to NVIC */
		/* PD0 is connected to EXTI_Line0, which has EXTI0_IRQn vector */
		NVIC_InitStruct.NVIC_IRQChannel = EXTI2_IRQn;
		/* Set priority */
		NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x00;
		/* Set sub priority */
		NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x00;
		/* Enable interrupt */
		NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
		/* Add to NVIC */
		NVIC_Init(&NVIC_InitStruct);
	}

	void Configure_PE4(){
		/* Set variables used */
		GPIO_InitTypeDef GPIO_InitStruct;
		EXTI_InitTypeDef EXTI_InitStruct;
		NVIC_InitTypeDef NVIC_InitStruct;

		/* Enable clock for GPIOE */
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
		/* Enable clock for SYSCFG */
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

		/* Set pin as input */
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
		GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
		GPIO_Init(GPIOE, &GPIO_InitStruct);

		/* Tell system that you will use PD0 for EXTI_Line0 */
		SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource4);

		/* PD0 is connected to EXTI_Line0 */
		EXTI_InitStruct.EXTI_Line = EXTI_Line4;
		/* Enable interrupt */
		EXTI_InitStruct.EXTI_LineCmd = ENABLE;
		/* Interrupt mode */
		EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
		/* Triggers on rising and falling edge */
		EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
		/* Add to EXTI */
		EXTI_Init(&EXTI_InitStruct);

		/* Add IRQ vector to NVIC */
		/* PD0 is connected to EXTI_Line0, which has EXTI0_IRQn vector */
		NVIC_InitStruct.NVIC_IRQChannel = EXTI4_IRQn;
		/* Set priority */
		NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x00;
		/* Set sub priority */
		NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x00;
		/* Enable interrupt */
		NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
		/* Add to NVIC */
		NVIC_Init(&NVIC_InitStruct);

	}

	void Configure_PE1(){
		GPIO_InitTypeDef GPIO_InitStruct;
		EXTI_InitTypeDef EXTI_InitStruct;
		NVIC_InitTypeDef NVIC_InitStruct;

		/* Enable clock for GPIOE */
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
		/* Enable clock for SYSCFG */
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

		/* Set pin as input */
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
		GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
		GPIO_Init(GPIOE, &GPIO_InitStruct);

		/* Tell system that you will use PD0 for EXTI_Line0 */
		SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, 1);

		/* PD0 is connected to EXTI_Line0 */
		EXTI_InitStruct.EXTI_Line = EXTI_Line1;
		/* Enable interrupt */
		EXTI_InitStruct.EXTI_LineCmd = ENABLE;
		/* Interrupt mode */
		EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
		/* Triggers on rising and falling edge */
		EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
		/* Add to EXTI */
		EXTI_Init(&EXTI_InitStruct);

		/* Add IRQ vector to NVIC */
		/* PD0 is connected to EXTI_Line0, which has EXTI0_IRQn vector */
		NVIC_InitStruct.NVIC_IRQChannel = EXTI1_IRQn;
		/* Set priority */
		NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x00;
		/* Set sub priority */
		NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x00;
		/* Enable interrupt */
		NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
		/* Add to NVIC */
		NVIC_Init(&NVIC_InitStruct);

	}

	void Configure_TIM3(){
		GPIO_InitTypeDef GPIO_InitStruct;                                    // GPIOC structure
		NVIC_InitTypeDef NVIC_InitStruct;                                 // NVIC structure
		TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;                      // Time base structure
		TIM_OCInitTypeDef       TIM_OCInitStruct;                            // Output Compare structure

		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);       // Clocking GPIOC (AHB1 = 168MHz)
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);        // Clocking TIM3  (APB1 = 42MHz)

		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;                             // Ch.1 (PC6)
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;                           // Alternative function
		GPIO_InitStruct.GPIO_Speed = GPIO_Fast_Speed;                        // 50MHz
		GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;                          // Push-pull
		GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;                          // Pulling-up
		GPIO_Init(GPIOC, &GPIO_InitStruct);                                  // Initializing GPIOC structure
		GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_TIM3);     // Routing TIM3 output to PC6

		NVIC_InitStruct.NVIC_IRQChannel = TIM3_IRQn;    // Specifying the channel (stm32f4xx.h)
		NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;            // Only matters for multiple interrupts
		NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;            // Only matters for multiple interrupts
		NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;       // Enabling global interrupt
		NVIC_Init(&NVIC_InitStruct);                                      // Initializing NVIC structure

		TIM_TimeBaseInitStruct.TIM_ClockDivision = 0;                        // Not dividing
		TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;       // Upcounting configuration
		TIM_TimeBaseInitStruct.TIM_Period = 65535;                    // Autoreload value (ARR) 
		TIM_TimeBaseInitStruct.TIM_Prescaler = TIM_PRESCALER;            // Dividing APB1 by 2 - 
		TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);                     // Initializing Time Base structure

		TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_Toggle;                // Output compare toggling mode
		TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;           // Enabling the Output Compare state
		TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_Low;               // Reverse polarity
		TIM_OCInitStruct.TIM_Pulse = TIM3_PULSE;                       // Output Compare 1 reg value
		TIM_OC1Init(TIM3, &TIM_OCInitStruct);                                // Initializing Output Compare 1 structure
		TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Disable);          // Disabling Ch.1 Output Compare preload

		TIM_Cmd(TIM3, ENABLE);                                      // Ready, Set, Go!
		TIM_ITConfig(TIM3, TIM_IT_CC1, ENABLE);                     // Enabling TIM3 Ch.1 interrupts
	}

	void Init(){
		/* Initialize system */
		my_Clock_PLL_Configuration();

		/*Configure pins for interrupts*/
		Configure_PE0();
		Configure_PE2();
		Configure_PE4();
		Configure_PE1();

		/*Configure for timer interrupts*/
		Configure_TIM3();

		/**/
		SysTick_Config(CLK_FREQ/1000);
		
		/*Configure board and LCD*/
		TM_DISCO_LedInit();
		TM_DELAY_Init();
		TM_RNG_Init();
		BoardInit();
	}

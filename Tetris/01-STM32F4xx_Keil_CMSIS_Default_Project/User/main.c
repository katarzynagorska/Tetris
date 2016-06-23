/**
 *	Keil project template
 *
 *	Before you start, select your target, on the right of the "Load" button
 *
 *	@author		Tilen Majerle
 *	@email		tilen@majerle.eu
 *	@website	http://stm32f4-discovery.com
 *	@ide		Keil uVision 5
 *	@conf		PLL parameters are set in "Options for Target" -> "C/C++" -> "Defines"
 *	@packs		STM32F4xx Keil packs version 2.4.0 or greater required
 *	@stdperiph	STM32F4xx Standard peripheral drivers version 1.5.0 or greater required
 */
/* Include core modules */
#include "stm32f4xx.h"
/* Include TM libraries */
#include "defines.h"
#include "tm_stm32f4_disco.h"
#include "tm_stm32f4_fonts.h"
#include "tm_stm32f4_ili9341.h"
#include "tm_stm32f4_delay.h"
/*Include my headers*/
#include "myGraphic.h"
#include "myInit.h"

#define PINLEFT GPIO_PIN_0
#define PINDOWN GPIO_PIN_2
#define PINUP GPIO_PIN_4
#define PINRIGHT GPIO_PIN_6

//void Clock_HSE_Configuration(void);
//void Clock_HSI_Configuration(void);
//void my_Clock_PLL_Configuration(void);


//void my_GPIO_Configuration(void);

//void EXTI_Configuration(void);

uint8_t  mode;
uint8_t up,down,left,right;

TileType_t tile;


int main(void) {
	
	mode = 0;

	/* Initialize system */
	my_Clock_PLL_Configuration();
	Configure_PE0();
	Configure_PE2();
	Configure_PE4();
	
	//SystemInit();
//my_Clock_PLL_Configuration();
//	my_GPIO_Configuration();

	/* Initialize leds & init on board */
	TM_DISCO_LedInit();
	TM_DELAY_Init();
	BoardInit();
	
	while (1) {
		if (mode){
			DrawNextTile(tile);
			mode = 0;
			Delayms(500);
			ClearNextTilePanel();
		}
	}
}

/* Set interrupt handlers */
/* Handle PD0 interrupt */
void EXTI0_IRQHandler(void) {
	/* Make sure that interrupt flag is set */
	if (EXTI_GetITStatus(EXTI_Line0) != RESET) {
		/* Do your stuff when PD0 is changed */
		tile = TILE_I;
		mode = 1;		
		/* Clear interrupt flag */
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}

void EXTI2_IRQHandler(void) {
	/* Make sure that interrupt flag is set */
	if (EXTI_GetITStatus(EXTI_Line2) != RESET) {
		/* Do your stuff when PD0 is changed */
		tile = TILE_O;
		mode = 1;		
		/* Clear interrupt flag */
		EXTI_ClearITPendingBit(EXTI_Line2);
	}
}

void EXTI4_IRQHandler(void) {
	/* Make sure that interrupt flag is set */
	if (EXTI_GetITStatus(EXTI_Line4) != RESET) {
		/* Do your stuff when PD0 is changed */
		tile = TILE_T;
		mode = 1;		
		/* Clear interrupt flag */
		EXTI_ClearITPendingBit(EXTI_Line4);
	}
}

void EXTI6_IRQHandler(void) {
	/* Make sure that interrupt flag is set */
	if (EXTI_GetITStatus(EXTI_Line6) != RESET) {
		/* Do your stuff when PD0 is changed */
		tile = TILE_L;
		mode = 1;		
		/* Clear interrupt flag */
		EXTI_ClearITPendingBit(EXTI_Line6);
	}
}
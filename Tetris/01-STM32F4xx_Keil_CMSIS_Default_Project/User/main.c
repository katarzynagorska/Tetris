/**
* Katarzyna Gorska
* MARM 16L
* Tetris clone
*
* Using Keil project template from http://stm32f4-discovery.net/
*
*/

/* Include core modules */
#include "stm32f4xx.h"
/* Include TM libraries */
#include "tm_stm32f4_fonts.h"
#include "tm_stm32f4_ili9341.h"
/*Include my headers*/
#include "myGraphic.h"
#include "myInit.h"
#include "myGame.h"

uint16_t timer_counter=0;
uint8_t i;


int main(void) {
	Init();
	game_StartGame();

//	while (1) {}}
while (1){
		if(!FlagGameOver)
		{
			game();
		}
		else
		{		
			game_over();						
		}
	}
}

/* Set interrupt handlers */
/* Handle PE0 interrupt */
/* LEFT */
void EXTI0_IRQHandler(void) {
	/* Make sure that interrupt flag is set */
	if (EXTI_GetITStatus(EXTI_Line0) != RESET) {
		/* Key flag set up*/
		FlagLeftKey = 1;
		/* Clear interrupt flag */
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}
/* Handle PE2 interrupt */
/* DOWN */
void EXTI2_IRQHandler(void) {
	if (EXTI_GetITStatus(EXTI_Line2) != RESET) {
		FlagDownKey = 1;
		EXTI_ClearITPendingBit(EXTI_Line2);
	}
}

/* Handle PE4 interrupt */
/* UP */
void EXTI4_IRQHandler(void) {
	if (EXTI_GetITStatus(EXTI_Line4) != RESET) {
		FlagUpKey = 1;
		EXTI_ClearITPendingBit(EXTI_Line4);
	}
}


/* Handle PE1 interrupt */
/* RIGHT */
void EXTI1_IRQHandler(void) {
	if (EXTI_GetITStatus(EXTI_Line1) != RESET) {
		FlagRightKey = 1;
		EXTI_ClearITPendingBit(EXTI_Line1);
	}
}

/* Handle SysTick interrupt */
/* DOWN */
void SysTick_Handler()
{
	static unsigned short count = 0;

	if (++count == 1000) {
		FlagTimeDown = 1;
		count = level*100;
	}
}


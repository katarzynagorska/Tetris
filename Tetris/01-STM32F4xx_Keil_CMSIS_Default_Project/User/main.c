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

uint8_t  mode;

TileType_t tile;

uint8_t FlagLeftKey, FlagRightKey, FlagUpKey, FlagDownKey;

int main(void) {
	Init();
	
	FlagLeftKey = 0;
	mode = 0;
	game_Shuffle();

	
	
	while (1) {
		
		/*Left key pressed*/
		if (FlagLeftKey){
			tile = game_nextTiles[mode];
			DrawNextTile(tile);
			mode++;
			if (mode == 7)
			{
				game_Shuffle();
				mode = 0;
			}
			FlagLeftKey = 0;
		}

		/*Right key pressed*/
		if (FlagRightKey){
		
		FlagRightKey = 0;
		}
		
		/*Up key pressed*/
		if (FlagUpKey){
		
		FlagUpKey = 0;
		}
		
		/*Down key pressed*/
		if (FlagDownKey){
		
		FlagDownKey = 0;
		}
		
		
	}
}

/* Set interrupt handlers */
/* Handle PE0 interrupt */
/* LEFT */
void EXTI0_IRQHandler(void) {
	/* Make sure that interrupt flag is set */
	if (EXTI_GetITStatus(EXTI_Line0) != RESET) {
		/* Do your stuff when PD0 is changed */
	//	tile = TILE_I;

		/* Key flag set up*/
		FlagLeftKey = 1;
		/* Clear interrupt flag */
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}
/* Handle PE2 interrupt */
/* DOWN */
void EXTI2_IRQHandler(void) {
	/* Make sure that interrupt flag is set */
	if (EXTI_GetITStatus(EXTI_Line2) != RESET) {
		/* Do your stuff when PD0 is changed */

		/* Key flag set up*/
		FlagDownKey = 1;		
		/* Clear interrupt flag */
		EXTI_ClearITPendingBit(EXTI_Line2);
	}
}

/* Handle PE4 interrupt */
/* UP */
void EXTI4_IRQHandler(void) {
	/* Make sure that interrupt flag is set */
	if (EXTI_GetITStatus(EXTI_Line4) != RESET) {
		/* Do your stuff when PD0 is changed */
		
		/* Key flag set up*/
		FlagUpKey = 1;
		/* Clear interrupt flag */
		EXTI_ClearITPendingBit(EXTI_Line4);
	}
}


/* Handle PE6 interrupt */
/* RIGHT */
void EXTI9_5_IRQHandler(void) {
	/* Make sure that interrupt flag is set */
	if (EXTI_GetITStatus(EXTI_Line6) != RESET) {
		/* Do your stuff when PD0 is changed */
		
		
		/* Key flag set up*/
		FlagDownKey = 1;		
		/* Clear interrupt flag */
		EXTI_ClearITPendingBit(EXTI_Line6);
	}
}

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



uint8_t FlagLeftKey, FlagRightKey, FlagUpKey, FlagDownKey;

int main(void) {
	Init();
	game_StartGame();

	mode = 1;
	
	while (1) {

		if (y_cor!=0){

			DrawTetrominoOnBoard(x_cor, y_cor, tetromino, tile_GetColor(tile));
			/*Left key pressed*/
			if (FlagLeftKey){
				tetromino_Move(LEFT);
				FlagLeftKey = 0;
			}

			/*Right key pressed*/
			if (FlagRightKey){
				tetromino_Move(RIGHT);
				FlagRightKey = 0;
			}

			/*Up key pressed*/
			if (FlagUpKey){
				tetromino_Rotate();
				FlagUpKey = 0;
			}

			/*Down key pressed*/
			if (FlagDownKey){
				tetromino_Move(DOWN);
				FlagDownKey = 0;

			}
		}
			else {
				FlagCollision = 0;
				game_AddTetrominoToBoard();
				game_refreshBoard();
				
				tile = game_nextTiles[mode];
				tetromino_Init(tile);

				
				mode++;

				xRefreshScore();
				yRefreshScore();
				
				if (mode < 7)
					DrawNextTile(game_nextTiles[mode]);
				
				if (mode == 7){
					game_Shuffle();
					mode = 0;
					DrawNextTile(game_nextTiles[mode]);
				
			}
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

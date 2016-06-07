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


#define SQUARE_SIZE 20
#define X_SQUARE_BEGINNING (155-SQUARE_SIZE)
#define Y_SQUARE_BEGINNING (160-SQUARE_SIZE)

//void Clock_HSE_Configuration(void);
//void Clock_HSI_Configuration(void);
//void my_Clock_PLL_Configuration(void);


//void my_GPIO_Configuration(void);

//void EXTI_Configuration(void);

uint8_t  mode;
uint8_t up,down,left,right,user;

uint16_t x,y;
uint8_t i,j,k;

int main(void) {
	
	mode = 0;
	j = 0;
	k = 0;
	x=0,y=0;

	/* Initialize system */
	//SystemInit();
	my_Clock_PLL_Configuration();
	my_GPIO_Configuration();

	/* Initialize leds & init on board */
	TM_DISCO_LedInit();
	TM_DELAY_Init();
	BoardInit();

	while (1) {
	
		/* Toggle leds */
		TM_DISCO_LedToggle(LED_ALL);
		ClearBoard();
	
		user = GPIO_ReadInputDataBit ( GPIOA, GPIO_PIN_0); 
		
		down = GPIO_ReadInputDataBit ( GPIOA, GPIO_PIN_2); 
		up = GPIO_ReadInputDataBit ( GPIOA, GPIO_PIN_4);
		left = GPIO_ReadInputDataBit ( GPIOA, GPIO_PIN_3);
		right = GPIO_ReadInputDataBit ( GPIOA, GPIO_PIN_5);
		
		if(down==0) 
		{
			if (y>0)
			{
				y-=1;
				ChangeScore(y);
				yRefreshScore();
			}
			else
				y = 22;
		}
		if(up==0)
		{
			if(y<22)
			{
				y+=1;
				ChangeScore(y);
				yRefreshScore();
			}
			else 
				y = 0;
		}
		if(left==0)
		{
			if(x>0)
			{
				x-=1;
				ChangeScore(x);
				xRefreshScore();
			}
			else
				x = 22;
		}
		if(right==0)
		{
			if (x<9)
			{
				x+=1;
				ChangeScore(x);
				xRefreshScore();
			}
			else 
				x = 0;
		}
					

		
		
		/*Drawing stuff*/
	/*	switch (mode){
			case 0:
				DrawNextTile(TILE_I);
				mode++;	
				break;
			case 1:
				DrawNextTile(TILE_O);
				mode++;	
				break;		
			case 2:
				DrawNextTile(TILE_T);
				mode++;	
				break;		
			case 3:
				DrawNextTile(TILE_S);
				mode++;
				break;
			case 4:
				DrawNextTile(TILE_Z);
				mode++;	
				break;
			
			case 5:
				DrawNextTile(TILE_J);
				mode++;	
				break;
			
			case 6:
				DrawNextTile(TILE_L);
				mode=0;	
				break;
		
		}
	*/
	
			if(left==1)
				DrawSquareOnTileBoard(8,8,ILI9341_COLOR_ORANGE);
		else
				DrawSquareOnTileBoard(8,8,ILI9341_COLOR_GREEN);	
		
	DrawSquareOnTileBoard(x,y,ILI9341_COLOR_MAGENTA);
	DrawSquareOnTileBoard(j,k,ILI9341_COLOR_BLACK);
	DrawSquareOnTileBoard(9-j,22-k,ILI9341_COLOR_BLUE2);
	if(j<9){ 
		j++;
	}
	else {
		j=0;
		k++;
	}
	if (k==22)
		k = 0; 
		
	Delayms(500);
		
	}
}



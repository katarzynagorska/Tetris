#include "tm_stm32f4_disco.h"
#include "tm_stm32f4_fonts.h"
#include "tm_stm32f4_ili9341.h"

//For testing
char score[]="99999";
char magenta[]="000x000";
char black[]="000x000";
/**
 * @brief  Possible tiles
 */
typedef enum {
	TILE_I,
	TILE_O,
	TILE_J,
	TILE_L,
	TILE_T,
	TILE_Z,
	TILE_S
} TileType_t;

/**
 * @brief  Draws filled square on Next tetromino field 
 * @param  x: X coordinate on matrix 4x4
 * @param  y: Y coordinate on matrix 4x4
 * @param  color: Square color
 * @retval None
 */
void DrawFilledSquareNextTile(uint16_t x, uint16_t y, uint32_t color);

/**
 * @brief  Draws filled square on LCD
 * @param  x: X coordinate of top left point
 * @param  y: Y coordinate of top left point
 * @param  size: square side length
 * @param  color: Square color
 * @retval None
 */
void DrawFilledSquare(uint16_t x, uint16_t y, uint16_t size, uint32_t color);

/**
 * @brief  Clears play board
 * @retval None
 */
void CleanBoard(void);

/**
 * @brief  Clears next tile panel
 * @retval None
 */
void ClearNextTilePanel(void);

/**
 * @brief  Draws next tile in next tile panel
 * @param  nextTile: tile to be drawn 
 * @retval None
 */
void DrawNextTile(TileType_t nextTile);

/**
 * @brief  Draws square on tile panel
 * @brief  (0,0) will be drawn in lower left corner
 * @brief	 (9,11) will be drawn in upper right corner
 * @param  x: x coordinate in 10x23matrix of squares
 * @param  y: y coordinate in 10x23matrix of squares
 * @param  color: color of square to be drawn
 * @retval None
 */
 void DrawSquareOnTileBoard(uint16_t x, uint16_t y, uint32_t color);

/**
 * @brief  Draws board layout on LCD
 * @retval None
 */
void BoardInit(void);


void BoardInit(){
	/*Initialize ILI9341 LCD with LTDC peripheral*/
	TM_ILI9341_Init();
	
	/*Orientation*/
	TM_ILI9341_Rotate(TM_ILI9341_Orientation_Portrait_1);
	
	/*Blue Panels*/
	TM_ILI9341_DrawFilledRectangle(0,0,240,320,ILI9341_COLOR_BLUE);
	/*Tiltle Panel*/
	TM_ILI9341_DrawFilledRectangle(0,0,240,20,ILI9341_COLOR_BLACK);
	TM_ILI9341_Puts(0,0,"KATARZYNA GORSKA",&TM_Font_11x18,ILI9341_COLOR_WHITE,ILI9341_COLOR_BLACK);
	
	/*Info Panel*/
//	TM_ILI9341_DrawFilledRectangle(0,10,70,320,ILI9341_COLOR_BLUE);	
	/**Next tetromino panel**/
	TM_ILI9341_Puts(5,30,"NEXT",&TM_Font_7x10,ILI9341_COLOR_WHITE,ILI9341_COLOR_BLUE);
	DrawFilledSquare(5,45,60,ILI9341_COLOR_WHITE);
	/**Score panel**/
	TM_ILI9341_Puts(5,110,"SCORE",&TM_Font_7x10,ILI9341_COLOR_WHITE,ILI9341_COLOR_BLUE);
	TM_ILI9341_Puts(5,125,score,&TM_Font_7x10,ILI9341_COLOR_WHITE,ILI9341_COLOR_BLUE);
	TM_ILI9341_Puts(5,140,magenta,&TM_Font_7x10,ILI9341_COLOR_MAGENTA,ILI9341_COLOR_BLUE);
	TM_ILI9341_Puts(5,155,black,&TM_Font_7x10,ILI9341_COLOR_BLACK,ILI9341_COLOR_BLUE);
}

void ClearBoard(){
	TM_ILI9341_DrawFilledRectangle(71,21,200,320,ILI9341_COLOR_WHITE);
}

void ClearNextTilePanel(){
	DrawFilledSquare(5,45,60,ILI9341_COLOR_WHITE);
}
void DrawNextTile(TileType_t nextTile){
	ClearNextTilePanel();
	
	if (nextTile==TILE_I){
		DrawFilledSquareNextTile(1, 0,ILI9341_COLOR_CYAN);
		DrawFilledSquareNextTile(1, 1,ILI9341_COLOR_CYAN);
		DrawFilledSquareNextTile(1, 2,ILI9341_COLOR_CYAN);
		DrawFilledSquareNextTile(1, 3,ILI9341_COLOR_CYAN);
	}
	if (nextTile==TILE_O){
		DrawFilledSquareNextTile(1, 1,ILI9341_COLOR_YELLOW);
		DrawFilledSquareNextTile(2, 1,ILI9341_COLOR_YELLOW);
		DrawFilledSquareNextTile(1, 2,ILI9341_COLOR_YELLOW);
		DrawFilledSquareNextTile(2, 2,ILI9341_COLOR_YELLOW);
	}
	
	if (nextTile==TILE_L){
		DrawFilledSquareNextTile(1, 1,ILI9341_COLOR_ORANGE);
		DrawFilledSquareNextTile(1, 0,ILI9341_COLOR_ORANGE);
		DrawFilledSquareNextTile(1, 2,ILI9341_COLOR_ORANGE);
		DrawFilledSquareNextTile(2, 2,ILI9341_COLOR_ORANGE);
	}
		
	if (nextTile==TILE_J){
		DrawFilledSquareNextTile(2, 0,ILI9341_COLOR_BLUE);
		DrawFilledSquareNextTile(2, 1,ILI9341_COLOR_BLUE);
		DrawFilledSquareNextTile(2, 2,ILI9341_COLOR_BLUE);
		DrawFilledSquareNextTile(1, 2,ILI9341_COLOR_BLUE);
	}
			
	if (nextTile==TILE_Z){
		DrawFilledSquareNextTile(3, 1,ILI9341_COLOR_RED);
		DrawFilledSquareNextTile(2, 1,ILI9341_COLOR_RED);
		DrawFilledSquareNextTile(2, 2,ILI9341_COLOR_RED);
		DrawFilledSquareNextTile(1, 2,ILI9341_COLOR_RED);
	}
				
	if (nextTile==TILE_S){
		DrawFilledSquareNextTile(0, 1,ILI9341_COLOR_GREEN);
		DrawFilledSquareNextTile(1, 1,ILI9341_COLOR_GREEN);
		DrawFilledSquareNextTile(1, 2,ILI9341_COLOR_GREEN);
		DrawFilledSquareNextTile(2, 2,ILI9341_COLOR_GREEN);
	}
					
	if (nextTile==TILE_T){
		DrawFilledSquareNextTile(2, 0,ILI9341_COLOR_MAGENTA);
		DrawFilledSquareNextTile(2, 1,ILI9341_COLOR_MAGENTA);
		DrawFilledSquareNextTile(2, 2,ILI9341_COLOR_MAGENTA);
		DrawFilledSquareNextTile(3, 1,ILI9341_COLOR_MAGENTA);
	}
}
void DrawFilledSquare(uint16_t x, uint16_t y, uint16_t size, uint32_t color){
	TM_ILI9341_DrawFilledRectangle(x, y, x+size, y+size, color);
}
void DrawFilledSquareNextTile(uint16_t x, uint16_t y, uint32_t color)
{
	if ((x>3) || (y>3))
		return;
	else
		DrawFilledSquare(13*x+11,13*y+49,12,color);
}

void DrawSquareOnTileBoard(uint16_t x, uint16_t y, uint32_t color){
	if (x>9 || y>22)
		return;
	else
		DrawFilledSquare(13*x+71,307-y*13,12,color);
}



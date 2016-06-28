#include "tm_stm32f4_rng.h"
#include "myTetrominos.h"

/*Game board*/
/*Buffer for tetrominos, that already fell down*/
uint16_t game_board[10][22];
/*Current tetrominio*/

uint16_t score_num;
uint8_t FlagCollision;
TileType_t game_nextTiles[] = { TILE_I, TILE_L, TILE_J, TILE_S, TILE_Z, TILE_O, TILE_T };

typedef enum {
	DOWN,
	LEFT,
	RIGHT,
} MoveDirection_t;

void game_Shuffle() {
	unsigned char i, k;
	TileType_t	tmp;
	/*Shuffling tiles*/
	for (i = 0; i < 7; i++) {
		k = TM_RNG_Get() % 7;
		tmp = game_nextTiles[k];
		game_nextTiles[k] = game_nextTiles[i];
		game_nextTiles[i] = tmp;
	}
}
void game_AddTetrominoToBoard(void);

void game_RefreshBoard(void);

void game_StartGame(void){
	score_num = 0;
	game_Shuffle();
	tile = game_nextTiles[0];
	DrawNextTile(game_nextTiles[1]);
	tetromino_Init(tile);
	
}

	
	
void game_ClearBoard(void){
	unsigned char x, y;

	for (x = 0; x < 10; x++)
	for (y = 0; y < 22; y++)
		game_board[x][y] = 0;
}



uint32_t tile_GetColor(TileType_t tile){
	uint32_t color;
	switch (tile){
	case TILE_I:
		color = ILI9341_COLOR_CYAN;
		break;
	case TILE_J:
		color = ILI9341_COLOR_BLUE;
		break;
	case TILE_L:
		color = ILI9341_COLOR_ORANGE;
		break;
	case TILE_O:
		color = ILI9341_COLOR_YELLOW;
		break;
	case TILE_S:
		color = ILI9341_COLOR_GREEN;
		break;
	case TILE_Z:
		color = ILI9341_COLOR_RED;
		break;
	case TILE_T:
		color = ILI9341_COLOR_MAGENTA;
		break;
	}
	return color;
}

//void collision_Check(uint16_t x_new_cord, uint16_t y_new_cord){
//	unsigned char i;
//	for (i = 0; i < 4; i++)
//	{
//		if (tetromino[i][1] + y_new_cord == 0){
//			FlagCollision = 1;
//			return;
//		}
//	}

//}

void tetromino_Move(MoveDirection_t move)
{
		unsigned char i;
	/*Erasing old tetromino position*/
	DrawTetrominoOnBoard(x_cor,y_cor,tetromino,ILI9341_COLOR_WHITE);
	

	switch (move){
	case LEFT:
		/*Checking if not hitting left wall*/
		//collision_Check(x_cor-1,y_cor);
		for (i = 0; i < 4; i++){
			if (tetromino[i][0] + x_cor == 0){
				return;
			}
		}

		
		x_cor -= 1;
		ChangeScore(x_cor);
		xRefreshScore();
		break;
	case RIGHT:
		/*Checking if not hitting left wall*/
		//collision_Check(x_cor-1,y_cor);
		for (i = 0; i < 4; i++){
			if (tetromino[i][0] + x_cor == 9){
				return;
			}
		}	
		
		x_cor += 1;
		ChangeScore(x_cor);
		xRefreshScore();
		break;

	case DOWN:
			/*Checking in any of tetromino's blocks touched the ground*/
		for (i = 0; i < 4; i++){
			if (tetromino[i][0] + y_cor == 0){
				FlagCollision = 1;
				return;
			}
		//TODO
		/*Checking if any of tetrominos block touched board's tetrominos*/
		for (i = 0; i < 4; i++){
			if (game_board[tetromino[i][0]+x_cor][tetromino[i][1]+y_cor]==1){
				FlagCollision = 1;
				return;
			}
		}	
		if(!FlagCollision)
		{
		y_cor -= 1;
		ChangeScore(y_cor);
		yRefreshScore();
			
		score_num+=1;
		ChangeScore(score_num);
		RefreshScore();			
		}	

	}
}
}
void game_AddTetrominoToBoard(){
	unsigned char i;
	for (i = 0 ; i < 4; i++){
		game_board[tetromino[i][0]+x_cor][tetromino[i][1]+y_cor] = 1;
	}
}

void game_RefreshBoard(){
	unsigned char x, y;

	for (x = 0; x < 10; x++)
		for (y = 0; y < 22; y++)
			if (game_board[x][y])
				DrawSquareOnTileBoard(x,y,ILI9341_COLOR_BLACK);

}


#include "tm_stm32f4_rng.h"
#include "myTetrominos.h"

/* Game board */

/* Score */
uint16_t score_num;
unsigned short level, lines;

/* Event flags */
uint8_t FlagCollision, FlagGameOver;
/* Move flags */
uint8_t FlagLeftKey, FlagRightKey, FlagUpKey, FlagDownKey, FlagTimeDown;
/* For shuffling every 7 tiles */
uint8_t  mode;
/* Tiles deck */
TileType_t game_nextTiles[] = { TILE_I, TILE_L, TILE_J, TILE_S, TILE_Z, TILE_O, TILE_T };

/* Possible movements */
typedef enum {
	DOWN,
	LEFT,
	RIGHT,
} MoveDirection_t;

/**
* @brief  Shuffles tiles deck
* @retval None
*/
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
/**
* @brief  Game initialization
* @retval None
*/
void game_StartGame(void){
	/* Board initialization */
	BoardInit();

	/* Initializing global values */
	score_num = 0;
	level = 0;
	FlagGameOver = 0;
	FlagCollision = 0;
	
	/* For new shuffling */
	mode = 1;
	game_Shuffle();
	
	/* First tile */
	tile = game_nextTiles[0];
	DrawNextTile(game_nextTiles[1]);
	tetromino_Init(tile);
}


/**
* @brief  Clears game board
* @retval None
*/
void game_ClearBoard(void){
	unsigned char x, y;

	for (x = 0; x < 10; x++)
		for (y = 0; y < 22; y++)
			game_board[x][y] = 0;
}

/**
* @brief  Adding stopped tetromino to game_board
* @retval None
*/
void game_AddTetrominoToBoard(){
	unsigned char i;
	TM_ILI9341_Puts(0, 140, "A", &TM_Font_11x18, ILI9341_COLOR_RED, ILI9341_COLOR_BLACK);
	for (i = 0; i < 4; i++){
		game_board[tetromino[i][0] + x_cor][tetromino[i][1] + y_cor] = 1;
	}
}
/**
* @brief  Drawing game_board representation on tile board
* @retval None
*/
void game_RefreshBoard(){
	unsigned char x, y;

	for (x = 0; x < 10; x++){
		for (y = 0; y < 22; y++){
			if (game_board[x][y])
				DrawSquareOnTileBoard(x, y, ILI9341_COLOR_BLACK);
			else
				DrawSquareOnTileBoard(x, y, ILI9341_COLOR_WHITE);
		}
	}
}
/**
* @brief  Deleteing full lines from game_board
* @retval None
*/
void game_DeleteLines(){
		unsigned char x, y, full, line_num;

	/* Veryfying every line in board */
	for (line_num = 0; line_num<22; line_num++)
	{
		full = 1;
		
		/*If any of elements in line is empty line is not full */
		for (x = 0; x<10; x++)
		if (game_board[x][line_num] == 0)
			full = 0;

		/* Full line */
		if (full == 1)
		{
			/* Bonus for full lines */
			score_num += 25;
			lines+=1;
			/* Display line number */
			ChangeScore(lines);
			yRefreshScore();
			/* Increase level after every 10 lines */
			/* Level 8 for max speed*/
			if (!(lines%10)&&level<8){
				level++;
				/* Display lever */
				ChangeScore(level);
				xRefreshScore();
			}
			//TODO
			/* Moving non full lines down */
			for (y = line_num; y<21; y++){
				for (x = 0; x<10; x++){
					game_board[x][y] = game_board[x][y + 1];
				}
			}
			/* Tile board update */
			game_RefreshBoard();
		}
	}
}

/**
* @brief  Function for moving tetrominos
* @param 	move: Movement direction
* @retval None
*/
void tetromino_Move(MoveDirection_t move)
{
	unsigned char i;
	/*Erasing old tetromino position*/
	DrawTetrominoOnBoard(x_cor, y_cor, tetromino, ILI9341_COLOR_WHITE);


	switch (move){
	case LEFT:
		/*Checking if not hitting left wall*/
		for (i = 0; i < 4; i++){
			if (tetromino[i][0] + x_cor == 0){
				return;
			}
		}
		/*Checking if not hitting board tetrominos*/
		for (i = 0; i < 4; i++){
			if (game_board[tetromino[i][0] + x_cor - 1][tetromino[i][1] + y_cor] == 1){
				return;
			}
		}
		/* Moving tetromino left */
		x_cor -= 1;
		break;

	case RIGHT:
		/*Checking if not hitting right wall*/
		for (i = 0; i < 4; i++){
			if (tetromino[i][0] + x_cor == 9){
				return;
			}
		}
		/*Checking if not hitting board tetrominos*/
		for (i = 0; i < 4; i++){
			if (game_board[tetromino[i][0] + x_cor + 1][tetromino[i][1] + y_cor] == 1){
				return;
			}
		}
		/* Moving tetromino right */
		x_cor += 1;
		break;

	case DOWN:
		/*Checking in any of tetromino's blocks touched the ground*/
		for (i = 0; i < 4; i++){
			if (tetromino[i][0] + y_cor == 0){
				FlagCollision = 1;
				return;
			}
			/*Checking if any of tetrominos block touched board's tetrominos*/
			for (i = 0; i < 4; i++){
				if (game_board[tetromino[i][0] + x_cor][tetromino[i][1] + y_cor - 1] == 1){
					FlagCollision = 1;
					return;
				}
			}
			/* Moving tetromino down */
				y_cor -= 1;
				score_num += 1;
				ChangeScore(score_num);
				RefreshScore();
			break;
		}
	}
}
/**
* @brief  Function for hard drop
* @retval None
*/
void tetromino_Drop(){
	while (!FlagCollision){
		/*Additional points for each line in fast drop*/
		tetromino_Move(DOWN);
		score_num += 1;
	}
}

/**
* @brief  Game
* @retval None
*/
void game()
{
	/* For tetromino iteration */
	unsigned char j;
	if (!FlagCollision){
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
		if (FlagDownKey) {
			tetromino_Drop();
			FlagDownKey = 0;
		}

		/*Time drop*/
		if (FlagTimeDown){
			tetromino_Move(DOWN);
			FlagTimeDown = 0;
		}
	}
	else {
		/*Clear collision flag*/
		FlagCollision = 0;

		/*Adding tetromino to board*/
		game_AddTetrominoToBoard();

		/*Deleting full lines*/
		game_DeleteLines();

		/* Game over if last tile is over board's edge*/
		for (j = 0; j<4; j++){
			if (tetromino[j][1] + y_cor >= 21)
				FlagGameOver = 1;
		}

			/*Changing for next tile*/
			tile = game_nextTiles[mode];

			/*Counter incrementation*/
			mode++;

			/*Drawing next tile*/
			if (mode < 7)
				DrawNextTile(game_nextTiles[mode]);

			/*Mode rst, new shuffle, drawing next tlie*/
			if (mode == 7){
				game_Shuffle();
				mode = 0;
				DrawNextTile(game_nextTiles[mode]);
			}
			
			/*Initializing next tetromino*/
			tetromino_Init(tile);
			
			/*Drawing board last with tetromino*/
			game_RefreshBoard();
	}
}

//TODO reset after up key
/* Displays game over, waits for up to restart game */
void game_over(){
	TM_ILI9341_Puts(0, 140, "GAME\nOVER", &TM_Font_11x18, ILI9341_COLOR_RED, ILI9341_COLOR_BLACK);
while(1){}
	DispGameOver();

}



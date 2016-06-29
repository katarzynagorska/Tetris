#include "tm_stm32f4_rng.h"
#include "myTetrominos.h"

/* Game board */
/* Buffer for tetrominos, that have already fallen down */
uint16_t game_board[10][22];
/* Score */
uint16_t score_num;

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

/* Shuffling tile deck */
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

void game_StartGame(void){
	BoardInit();

	score_num = 0;
	mode = 1;

	game_Shuffle();
	tile = game_nextTiles[0];
	DrawNextTile(game_nextTiles[1]);

	tetromino_Init(tile);

	FlagGameOver = 0;
}



void game_ClearBoard(void){
	unsigned char x, y;

	for (x = 0; x < 10; x++)
	for (y = 0; y < 22; y++)
		game_board[x][y] = 0;
}


void game_AddTetrominoToBoard(){
	unsigned char i;
	for (i = 0; i < 4; i++){
		game_board[tetromino[i][0] + x_cor][tetromino[i][1] + y_cor] = 1;
	}
}

void game_RefreshBoard(){
	unsigned char x, y;

	for (x = 0; x < 10; x++)
	for (y = 0; y < 22; y++)
	if (game_board[x][y])
		DrawSquareOnTileBoard(x, y, ILI9341_COLOR_BLACK);

}

void game_DeleteLines(){
	unsigned char x, y, full, line_num;
	for (line_num = 0; line_num<22; line_num++)
	{
		full = 1;
		for (x = 0; x<10; x++)
		if (game_board[x][line_num] == 0)
			full = 0;
		if (full == 1)
		{
			for (y = line_num; y<21; y++)
			for (x = 0; x<10; x++){
				game_board[x][y] = game_board[x][y + 1];
			}
		}
	}
	game_RefreshBoard();

}

void tetromino_Move(MoveDirection_t move)
{
	unsigned char i, j;
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

		x_cor -= 1;
		ChangeScore(x_cor);
		xRefreshScore();
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
		x_cor += 1;
		ChangeScore(x_cor);
		xRefreshScore();
		break;

	case DOWN:
		/*Checking in any of tetromino's blocks touched the ground*/
		for (i = 0; i < 4; i++){
			if (tetromino[i][0] + y_cor == 0){
				FlagCollision = 1;
			}
			/*Checking if any of tetrominos block touched board's tetrominos*/
			for (i = 0; i < 4; i++){
				if (game_board[tetromino[i][0] + x_cor][tetromino[i][1] + y_cor - 1] == 1){
					FlagCollision = 1;
				}
			}
			if (!FlagCollision)
			{
				y_cor -= 1;

				score_num += 1;
				ChangeScore(score_num);
				RefreshScore();
			}
		}
	}
}
void tetromino_Drop(){
	while (!FlagCollision)
		tetromino_Move(DOWN);
}


void game()
{
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
		/*Initializing tetromino*/
		tetromino_Init(tile);

		/*Counter incrementation*/
		mode++;

		/*Drawing next tile*/
		if (mode < 7)
			DrawNextTile(game_nextTiles[mode]);

		/*Couner rst, new shuffle, drawing next tlie*/
		if (mode == 7){
			game_Shuffle();
			mode = 0;
			DrawNextTile(game_nextTiles[mode]);
		}

		/*Drawing board last with tetromino*/
		game_RefreshBoard();
	}
}

//TODO reset after up key
/* Displays game over, waits for up to restart game */
void game_over(){
	DispGameOver();
	while (1)
	{
		if (FlagUpKey){
			FlagGameOver = 0;
			break;
		}
	}
	game_StartGame();
}
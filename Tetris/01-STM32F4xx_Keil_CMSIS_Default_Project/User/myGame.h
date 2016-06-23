#include "tm_stm32f4_rng.h"

/*Game board*/
/*Buffer for tetrominos, that already fell down*/
unsigned char game_board[10][22];
TileType_t game_nextTiles[] = {TILE_I, TILE_L, TILE_J, TILE_S, TILE_Z, TILE_O, TILE_T};

//extern void TM_RNG_Init(void);

void game_ClearBoard(void){
	unsigned char x,y;
	
	for (x = 0; x < 10; x++)
		for (y = 0; y < 22; y++)
			game_board[x][y] = 0;
}

void game_Shuffle() {
		unsigned char i,k;
		TileType_t	tmp;
		/*Shuffling tiles*/
    for (i = 0; i < 7; i++) {
			k = TM_RNG_Get()%7;
			tmp = game_nextTiles[k];
			game_nextTiles[k] = game_nextTiles[i];
			game_nextTiles[i] = tmp;				
    }
}

/*For current tetromino layout*/
uint16_t tetromino[4][2];
/*Current tile*/
TileType_t tile;
/*Coordinates of tetromino origin points*/
uint16_t x_cor, y_cor;
/*Current rotation*/
Rotate_t current_rot;
/* Buffer for tetrominos, that have already fallen down */
uint16_t game_board[10][22];

/**
* @brief  Rotating tetromino if possible
* @retval None
*/
void tetromino_Rotate(){
	unsigned char i, j;
	uint16_t tmp[4][2];
	/*Erasing old tetromino position*/
	DrawTetrominoOnBoard(x_cor, y_cor, tetromino, ILI9341_COLOR_WHITE);

	/*Initializing tetromino points depending on tile type and current roatation*/
	switch (tile){
	case TILE_I:
		if ((current_rot == ROTATE_0) || (current_rot == ROTATE_180))
		{
			//	I_hor = [{0,1},{1,1},{2,1},{3,1}];	
			for (i = 0; i < 4; i++){
				tmp[i][0] = 0;
				tmp[i][1] = i;
			}
		}
		else
		{
			/*Preventing rotation when to close to the wall*/
			if (x_cor>6)
				return;
			//	I_hor = [{1,0},{1,1},{1,2},{1,3}];
			for (i = 0; i < 4; i++){
				tmp[i][0] = i;
				tmp[i][1] = 0;
			}
		}

		break;
	case TILE_J:
		if (current_rot == ROTATE_0)
		{
			//	J_0 = {{0,0}{1,0}{1,1}{1,2}}
			tmp[0][0] = 0;
			tmp[0][1] = 0;

			for (i = 1; i < 4; i++){
				tmp[i][0] = 1;
				tmp[i][1] = i - 1;
			}
		}
		else if (current_rot == ROTATE_90)
		{
			if (x_cor>7)
				return;
			//	J_90 = {{0,1}{0,0}{1,0}{2,0}}
			tmp[0][0] = 0;
			tmp[0][1] = 1;

			for (i = 1; i < 4; i++){
				tmp[i][0] = i - 1;
				tmp[i][1] = 0;
			}
		}
		else if (current_rot == ROTATE_180)
		{
			//	J_180 = {{0,0}{0,1}{0,2}{1,2}}
			for (i = 0; i < 3; i++){
				tmp[i][0] = 0;
				tmp[i][1] = i;
			}
			tmp[3][0] = 1;
			tmp[3][1] = 2;
		}
		else{
			/*Preventing rotation when to close to the wall*/
			if (x_cor>7)
				return;
			//	J_270 = {{0,1}{1,1}{2,1}{2,0}}
			for (i = 0; i < 3; i++){
				tmp[i][0] = i;
				tmp[i][1] = 1;
			}
			tmp[3][0] = 2;
			tmp[3][1] = 0;
		}
		break;

	case TILE_L:
		if (current_rot == ROTATE_0)
		{
			//	L_0 = {{0,0}{0,1}{0,2}{1,0}}
			for (i = 0; i < 3; i++){
				tmp[i][0] = 0;
				tmp[i][1] = i;
			}
			tmp[3][0] = 1;
			tmp[3][1] = 0;
		}
		else if (current_rot == ROTATE_90)
		{
			/*Preventing rotation when to close to the wall*/
			if (x_cor>7)
				return;
			//	L_90 = {{0,1}{1,1}{1,2}{0,0}}
			for (i = 0; i < 3; i++){
				tmp[i][0] = i;
				tmp[i][1] = 1;
			}
			tmp[3][0] = 0;
			tmp[3][1] = 0;
		}
		else if (current_rot == ROTATE_180)
		{
			//	L_180 = {{0,0}{0,1}{0,2}{1,2}}
			for (i = 0; i < 3; i++){
				tmp[i][0] = 1;
				tmp[i][1] = i;
			}
			tmp[3][0] = 0;
			tmp[3][1] = 2;
		}
		else{
			/*Preventing rotation when to close to the wall*/
			if (x_cor>7)
				return;
			//	L_270 = {{0,0}{1,0}{2,0}{2,1}}
			for (i = 0; i < 3; i++){
				tmp[i][0] = i;
				tmp[i][1] = 0;
			}
			tmp[3][0] = 2;
			tmp[3][1] = 1;
		}
		break;
	case TILE_O:
		// O = {{0,0},{0,1},{1,0},{1,1}}
		for (i = 0; i < 2; i++){
			tmp[i][0] = 0;
			tmp[i + 2][0] = 1;
		}
		for (i = 0; i < 4; i++)
			tmp[i][1] = i % 2;
		break;

	case TILE_S:
		if ((current_rot == ROTATE_0) || (current_rot == ROTATE_180))
		{
			/*Preventing rotation when to close to the wall*/
			if (x_cor>7)
				return;
			// S_ver = {{0,0},{1,0},{1,1},{2,1}}
			for (i = 0; i < 4; i++){
				if (i<2)
				{
					tmp[i][0] = i;
					tmp[i][1] = 0;
				}
				else
				{
					tmp[i][0] = i - 1;
					tmp[i][1] = 1;
				}
			}
		}
		else
		{
			//S_hor = {{0,1}{0,2}{1,0}{1,1}}
			for (i = 0; i < 4; i++){
				if (i<2)
				{
					tmp[i][0] = 0;
					tmp[i][1] = i + 1;
				}
				else
				{
					tmp[i][0] = 1;
					tmp[i][1] = i - 2;
				}
			}
		}
		break;
	case TILE_Z:
		if ((current_rot == ROTATE_0) || (current_rot == ROTATE_180))
		{
			/*Preventing rotation when to close to the wall*/
			if (x_cor>7)
				return;
			//Z_ver = {{0,1}{1,1}{1,0}{2,0}}
			for (i = 0; i < 4; i++){
				if (i<2)
				{
					tmp[i][0] = i;
					tmp[i][1] = 1;
				}
				else
				{
					tmp[i][0] = i - 1;
					tmp[i][1] = 0;
				}
			}
		}
		else
		{
			//Z_hor = {{0,0}{0,1}{1,1}{1,2}}
			for (i = 0; i < 4; i++){
				if (i<2)
				{
					tmp[i][0] = 0;
					tmp[i][1] = i;
				}
				else
				{
					tmp[i][0] = 1;
					tmp[i][1] = i - 1;
				}
			}
		}
		break;
	case TILE_T:
		if (current_rot == ROTATE_0)
		{
			/*Preventing rotation when to close to the wall*/
			if (x_cor>7)
				return;
			//	T_0 = {{0,1}{1,1}{2,1}{1,0}}
			for (i = 0; i < 3; i++){
				tmp[i][0] = i;
				tmp[i][1] = 1;
			}
			tmp[3][0] = 1;
			tmp[3][1] = 0;
		}
		else if (current_rot == ROTATE_90)
		{
			//	T_90 = {{1,0}{1,1}{1,2}{0,1}}
			for (i = 0; i < 3; i++){
				tmp[i][0] = 1;
				tmp[i][1] = i;
			}
			tmp[3][0] = 0;
			tmp[3][1] = 1;
		}
		else if (current_rot == ROTATE_180)
		{
			/*Preventing rotation when to close to the wall*/
			if (x_cor>7)
				return;
			//	T_180 = {{0,1}{1,1}{2,1}{1,2}}
			for (i = 0; i < 3; i++){
				tmp[i][0] = i;
				tmp[i][1] = 1;
			}
			tmp[3][0] = 1;
			tmp[3][1] = 2;
		}
		else{
			//	T_270 = {{0,0}{0,1}{0,2}{1,1}}
			for (i = 0; i < 3; i++){
				tmp[i][0] = 0;
				tmp[i][1] = i;
			}
			tmp[3][0] = 1;
			tmp[3][1] = 1;
		}
		break;

	}
	/* Checking for collision with other tetrominoes on board */
	for (i = 0; i<4; i++){
		if (game_board[tmp[i][0] + x_cor][tmp[i][1] + y_cor] == 1)
			return;
	}

	/* Saving new tetromino */
	for (i = 0; i<4; i++){
		for (j = 0; j<2; j++){
		tetromino[i][j] = tmp[i][j];
		}
	}

	/*Changing current rotation*/
	switch (current_rot)
	{
	case ROTATE_0:
		current_rot = ROTATE_90;
		break;
	case ROTATE_90:
		current_rot = ROTATE_180;
		break;
	case ROTATE_180:
		current_rot = ROTATE_270;
		break;
	case ROTATE_270:
		current_rot = ROTATE_0;
		break;
	}
}


/**
* @brief  Initialization of new tetromino
* @retval None
*/
void tetromino_Init(TileType_t tile){

	/*Setting up drop origin coordinates*/
	switch (tile){
	case TILE_I:
		x_cor = 4;
		y_cor = 19;
		break;
	case TILE_J:
		x_cor = 3;
		y_cor = 20;
		break;
	case TILE_L:
		x_cor = 4;
		y_cor = 20;
		break;
	case TILE_O:
		x_cor = 4;
		y_cor = 21;
		break;
	case TILE_S:
		x_cor = 4;
		y_cor = 21;
		break;
	case TILE_Z:
		x_cor = 3;
		y_cor = 21;
		break;
	case TILE_T:
		x_cor = 3;
		y_cor = 21;
		break;
	}
	/*New tetromino has 0 rotation*/
	current_rot = ROTATE_0;
	tetromino_Rotate();
}
/**
* @brief  Getter for tile color
* @param 	tile: tile to check color
* @retval color: tile color
*/
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

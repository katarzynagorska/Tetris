/*For current tetromino layout*/
uint16_t tetromino[4][2];
/*Current tile*/
TileType_t tile;
/*Coordinates of tetromino origin points*/
uint16_t x_cor, y_cor;
/*Current rotation*/
Rotate_t current_rot;

void tetromino_Rotate(){
	unsigned char i;
	/*Erasing old tetromino position*/
	DrawTetrominoOnBoard(x_cor, y_cor, tetromino, ILI9341_COLOR_WHITE);

	/*Initializing tetromino points depending on tile type and current roatation*/
	switch (tile){
	case TILE_I:
		if ((current_rot == ROTATE_0) || (current_rot == ROTATE_180))
		{
			//	I_hor = [{0,1},{1,1},{2,1},{3,1}];	
			for (i = 0; i < 4; i++){
				tetromino[i][0] = 0;
				tetromino[i][1] = i;
			}
		}
		else
		{
			/*Preventing rotation when to close to the wall*/
			if (x_cor>6)
				return;
			//	I_hor = [{1,0},{1,1},{1,2},{1,3}];
			for (i = 0; i < 4; i++){
				tetromino[i][0] = i;
				tetromino[i][1] = 0;
			}
		}
		break;

	case TILE_J:
		if (current_rot == ROTATE_0)
		{
			//	J_0 = {{0,0}{1,0}{1,1}{1,2}}
			tetromino[0][0] = 0;
			tetromino[0][1] = 0;

			for (i = 1; i < 4; i++){
				tetromino[i][0] = 1;
				tetromino[i][1] = i - 1;
			}
		}
		else if (current_rot == ROTATE_90)
		{
			if (x_cor>7)
				return;
			//	J_90 = {{0,1}{0,0}{1,0}{2,0}}
			tetromino[0][0] = 0;
			tetromino[0][1] = 1;

			for (i = 1; i < 4; i++){
				tetromino[i][0] = i - 1;
				tetromino[i][1] = 0;
			}
		}
		else if (current_rot == ROTATE_180)
		{
			//	J_180 = {{0,0}{0,1}{0,2}{1,2}}
			for (i = 0; i < 3; i++){
				tetromino[i][0] = 0;
				tetromino[i][1] = i;
			}
			tetromino[3][0] = 1;
			tetromino[3][1] = 2;
		}
		else{
			/*Preventing rotation when to close to the wall*/
			if (x_cor>7)
				return;
			//	J_270 = {{0,1}{1,1}{2,1}{2,0}}
			for (i = 0; i < 3; i++){
				tetromino[i][0] = i;
				tetromino[i][1] = 1;
			}
			tetromino[3][0] = 2;
			tetromino[3][1] = 0;
		}
		break;

	case TILE_L:
		if (current_rot == ROTATE_0)
		{
			//	L_0 = {{0,0}{0,1}{0,2}{1,0}}
			for (i = 0; i < 3; i++){
				tetromino[i][0] = 0;
				tetromino[i][1] = i;
			}
			tetromino[3][0] = 1;
			tetromino[3][1] = 0;
		}
		else if (current_rot == ROTATE_90)
		{
			/*Preventing rotation when to close to the wall*/
			if (x_cor>7)
				return;
			//	L_90 = {{0,1}{1,1}{1,2}{0,0}}
			for (i = 0; i < 3; i++){
				tetromino[i][0] = i;
				tetromino[i][1] = 1;
			}
			tetromino[3][0] = 0;
			tetromino[3][1] = 0;
		}
		else if (current_rot == ROTATE_180)
		{
			//	L_180 = {{0,0}{0,1}{0,2}{1,2}}
			for (i = 0; i < 3; i++){
				tetromino[i][0] = 1;
				tetromino[i][1] = i;
			}
			tetromino[3][0] = 0;
			tetromino[3][1] = 2;
		}
		else{
			/*Preventing rotation when to close to the wall*/
			if (x_cor>7)
				return;
			//	L_270 = {{0,0}{1,0}{2,0}{2,1}}
			for (i = 0; i < 3; i++){
				tetromino[i][0] = i;
				tetromino[i][1] = 0;
			}
			tetromino[3][0] = 2;
			tetromino[3][1] = 1;
		}
		break;
	case TILE_O:
		// O = {{0,0},{0,1},{1,0},{1,1}}
		for (i = 0; i < 2; i++){
			tetromino[i][0] = 0;
			tetromino[i + 2][0] = 1;
		}
		for (i = 0; i < 4; i++)
			tetromino[i][1] = i % 2;
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
					tetromino[i][0] = i;
					tetromino[i][1] = 0;
				}
				else
				{
					tetromino[i][0] = i - 1;
					tetromino[i][1] = 1;
				}
			}
		}
		else
		{
			//S_hor = {{0,1}{0,2}{1,0}{1,1}}
			for (i = 0; i < 4; i++){
				if (i<2)
				{
					tetromino[i][0] = 0;
					tetromino[i][1] = i + 1;
				}
				else
				{
					tetromino[i][0] = 1;
					tetromino[i][1] = i - 2;
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
					tetromino[i][0] = i;
					tetromino[i][1] = 1;
				}
				else
				{
					tetromino[i][0] = i - 1;
					tetromino[i][1] = 0;
				}
			}
		}
		else
		{
			//Z_hor = {{0,0}{0,1}{1,1}{1,2}}
			for (i = 0; i < 4; i++){
				if (i<2)
				{
					tetromino[i][0] = 0;
					tetromino[i][1] = i;
				}
				else
				{
					tetromino[i][0] = 1;
					tetromino[i][1] = i - 1;
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
				tetromino[i][0] = i;
				tetromino[i][1] = 1;
			}
			tetromino[3][0] = 1;
			tetromino[3][1] = 0;
		}
		else if (current_rot == ROTATE_90)
		{
				//	T_90 = {{1,0}{1,1}{1,2}{0,1}}
			for (i = 0; i < 3; i++){
				tetromino[i][0] = 1;
				tetromino[i][1] = i;
			}
			tetromino[3][0] = 0;
			tetromino[3][1] = 1;
		}
		else if (current_rot == ROTATE_180)
		{
			/*Preventing rotation when to close to the wall*/
			if (x_cor>7)
				return;
			//	T_180 = {{0,1}{1,1}{2,1}{1,2}}
			for (i = 0; i < 3; i++){
				tetromino[i][0] = i;
				tetromino[i][1] = 1;
			}
			tetromino[3][0] = 1;
			tetromino[3][1] = 2;
		}
		else{
			//	T_270 = {{0,0}{0,1}{0,2}{1,1}}
			for (i = 0; i < 3; i++){
				tetromino[i][0] = 0;
				tetromino[i][1] = i;
			}
			tetromino[3][0] = 1;
			tetromino[3][1] = 1;
		}
		break;

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



void tetromino_Init(TileType_t tile){
	/*New tetromino has 0 rotation*/
	current_rot = ROTATE_0;
	tetromino_Rotate();
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
		y_cor = 19;
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
}

#include <stdio.h>
#include <stdlib.h>

#define SIDE 5
#define ERROR1 "Invalid move: unexpected row and column value"
#define ERROR2 "Invalid move: occupied row and column value"
#define SUCCESS1 "Valid move: switching turn"

const char player[] = {'O', 'X'};

void initBoard(char board[SIDE][SIDE]){
	for(int row=0; row<SIDE ; row++){
		for(int column=0 ; column<SIDE ; column++){
			board[row][column] = '.';
		}
	}
}

void drawBoard(char board[SIDE][SIDE]){
	printf("  ");
	for(int i=1 ; i<=SIDE ; i++){
		printf(" %d ", i);
	}
	printf("\n");
	for(int row=0 ; row<SIDE ; row++){
		printf(" %d", row+1);
		for(int column=0 ; column<SIDE ; column++){
			printf(" %c ", board[row][column]);
		}
		printf("\n");
	}
	printf("\n\n");
}

int isValidMove(char board[SIDE][SIDE], int row, int column, int turn){
	row--;
	column--;
	if(column<0 || row<0 || row>=SIDE || column>=SIDE){
		return 1;
	}
	else if( board[row][column] != '.' ){
		return 2;
	}else{
		board[row][column] = player[turn%2];
		return 3;
	}
}

int isGameOver(char board[SIDE][SIDE], int turn){
	int occurence = 0;
	char curr, prev;

	//vertical
	for(int column=0 ; column<SIDE ;  column++){
		for(int row=0 ; row<SIDE ; row++){
			
			if( row == 0 && column == 0 ){
				prev = curr = board[row][column];
				continue;
			}
			curr = board[row][column];
//			printf("V: %d %d %c-%c %d\n", row, column, prev, curr, occurence);
			if( prev == curr && prev != '.' ){
				occurence++;
				if( occurence == 2 ){
					return 1;
				}
			}
			else{
				prev = curr;
				occurence = 0;
			}			
		}
	}
	
//	horizontal
	occurence = 0;
	for(int row=0 ; row<SIDE ;  row++){
		for(int column=0 ; column<SIDE ; column++){
			if( row == 0 && column == 0 ){
				prev = curr = board[row][column];
				continue;
			}
			curr = board[row][column];
//			printf("H: %d %d %c-%c %d\n", row, column, prev, curr, occurence);
			if( prev == curr && prev != '.' ){
				occurence++;
				if( occurence == 2 ){
					return 1;
				}
			}
			else{
				prev = curr;
				occurence = 0;
			}
		}
	}
	
	return 0;
}

int main(){
	
	char board[SIDE][SIDE] = {0};
//	char board[SIDE][SIDE] =  {
//		{'X', 'O', 'X', 'O', 'X'},
//		{'O', 'X', 'O', 'X', 'O'},
//		{'X', 'O', 'X', 'O', 'X'},
//		{'O', 'X', 'O', 'X', 'O'},
//		{'X', 'O', 'X', 'O', '.'}
//	};

	int row, column;
	int flag = 0;
	int turn = 1;
	int inputRow, inputColumn;
	int validMove;
	int gameOverFlag;
	
	initBoard(board);
		
	do{
		system("cls");
		printf(" Player - %c's turn (%2d/25)\n", player[turn%2], turn);
		printf(" =========================\n\n");
		drawBoard(board);
		
		validMove = 0;
		gameOverFlag = 0;
		printf(" Input [row column]: ");
		scanf("%d %d", &inputRow, &inputColumn);
		fflush(stdin);
		
		validMove = isValidMove(board, inputRow, inputColumn, turn);
		switch(validMove){
			case 1:
				printf(" %s", ERROR1);
				getchar();
				break;
			
			case 2:
				printf(" %s", ERROR2);
				getchar();			
				break;
				
			case 3:
				system("cls");
				printf(" Player - %c's turn (%d/25)\n", player[turn%2], turn);
				printf(" =========================\n\n");
				drawBoard(board);
				gameOverFlag = isGameOver(board, turn);
				if( gameOverFlag == 1){
					printf(" Congratulations, Player %c win!!\n\n", player[turn%2]);
					getchar();
				}	
				turn++;
				break;		
		}

		if( turn > 25 ){
			printf(" Tie game!!");
			getchar();
			break;
		}
		
		

	}while( gameOverFlag == 0 );

	return 0;
}

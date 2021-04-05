#include <stdio.h>

#define Board_rows 7
#define Board_cols 9
#define WALL -1
#define SPACE 0


void CreateBoard(int board[Board_rows][Board_cols]);
void PrintGameBoard(int board[Board_rows][Board_cols]);
void MakeMove(int board[Board_rows][Board_cols], int col, char player);
int GameOver(int board[Board_rows][Board_cols], char player);
int getMove(int board[Board_rows][Board_cols]);
int Connect4Check(int board[Board_rows][Board_cols], int row,int col,int piece);
int boardFull(int board[Board_rows][Board_cols]);
char PlayAgain(void);
void ClearScreen(void);
int columnFull(int board[Board_rows][Board_cols], int col);

int main(void){
    int board[Board_rows][Board_cols];
    int gameOver1=0;
    int gameOver2=0;
    int board_full=0;
    char player1 = 'X';
    char player2 = 'O';
    char play_again;
    int score2 = 0;
    int score1 = 0;

    ClearScreen();

    GameSequence: 
       CreateBoard(board);
       while(!gameOver1 && !gameOver2 || !board_full){

       printf("==============\n");
       printf("Player 1 = '%c'\n",player1);
       printf("Player 2 = '%c'\n",player2);
       printf("==============\n");
       printf("CONNECT 4 GAME\n");
       printf("==============\n");    
       PrintGameBoard(board); 
       printf("Player 1 - ");
       int move1 = getMove(board);
       MakeMove(board,move1,player1);
       gameOver1 = GameOver(board,player1);
       board_full = boardFull(board);
       
       if (gameOver1){
           score1++;
           ClearScreen();
           printf("==============\n");
           printf(" CONNECT FOUR! \n");
           printf("==============\n");
           PrintGameBoard(board); 
           printf("=================================\n");
           printf("Congratulations Player 1! You win\n");
           printf("=================================\n");
           break;
       }
       if (board_full){
           ClearScreen();
           printf("======================\n");
           printf("Game tied! Well Played\n");
           printf("======================\n");
           break;
       }

       ClearScreen();
      
       printf("==============\n");
       printf("Player 1 = '%c'\n",player1);
       printf("Player 2 = '%c'\n",player2);
       printf("==============\n");
       printf("CONNECT 4 GAME\n");
       printf("==============\n"); 
       PrintGameBoard(board);
       printf("Player 2 - ");
       int move2 = getMove(board);
       MakeMove(board,move2,player2);
       gameOver2 = GameOver(board,player2);
       board_full = boardFull(board);

       if (gameOver2){
           score2++;
           ClearScreen();
           printf("==============\n");
           printf(" CONNECT FOUR! \n");
           printf("==============\n"); 
           PrintGameBoard(board); 
           printf("=================================\n");
           printf("Congratulations Player 2! You win\n");
           printf("=================================\n");
           break;
       }
       if (board_full){
           ClearScreen();
           printf("======================\n");
           printf("Game Tied! Well played\n");
           printf("======================\n");
           break;
       }

       ClearScreen();
   }
    
   play_again = PlayAgain();

   if (play_again == 'Y'){
       board_full=0;
       gameOver1=0;
       gameOver2=0;
       ClearScreen();
       goto GameSequence;
   } else if (play_again == 'N'){
       ClearScreen();
       printf("\n    FINAL SCORES     \n");
       printf("=====================\n");
       printf("Player1: %d Player2: %d",score1,score2);
       printf("\n=====================\n");
       printf("   EXITING GAME...\n");
       printf("=====================\n");
   }

    return 0;

}


void CreateBoard(int board[Board_rows][Board_cols]){
    int i,j;

    for (i=0;i<Board_rows;i++){
        for (j=0;j<Board_cols;j++){
            if (i==Board_rows-1){
                board[i][j] = WALL;
            } else if ( j==0 || j == Board_cols-1){
                board[i][j] = WALL;
            } else {
                board[i][j] = SPACE;
            }
        }
    }
}

int boardFull(int board[Board_rows][Board_cols]){
    int count=0;
    int i,j;
    
    for(i=0;i<Board_rows-1;i++){
        for (j=1;j<Board_cols-1;j++){
            if (board[i][j]!=SPACE){
                count++;
            }
        }
    }

    if ((count / ((Board_rows-1)*(Board_cols-2))) == 1){
        return 1;
    } else {
        return 0;
    }
}

void PrintGameBoard(int board[Board_rows][Board_cols]){
    int i,j;
    for (i=0;i<Board_rows;i++){
        for (j=0;j<Board_cols;j++){
            if (board[i][j] == WALL){
                printf("- ");
            } else if (board[i][j]==SPACE){
                printf("  ");
            } else {
                printf("%c ",board[i][j]);
            }
        }
        printf("\n");
    }
    printf("  ");
    for (int col=1;col<=Board_cols-2;col++){
    printf("%d ",col);
    }
    printf("\n\n");
}

void MakeMove(int board[Board_rows][Board_cols], int col, char player){
    int i;
    int gamePiece = player;
    if (player == 'X' || player == 'O'){
        if (col>0 && col<Board_cols-1){ // making sure column to add piece is within board
            for (i=Board_rows-1;i>=0;i--){
                if (board[i][col] == SPACE){
                    board[i][col] = gamePiece;
                    return;
                }
            }
        }
    }
}

int GameOver(int board[Board_rows][Board_cols], char player ){
    int gamePiece = player;
    int i,j;

    for (i=0;i<Board_rows-1;i++){
        for (j=0;j<Board_cols;j++){
            if (board[i][j] == gamePiece){
                int connect4 = Connect4Check(board,i,j,gamePiece);
                if (connect4){
                    return 1;
                }
            }
        }
    }

    return 0;

}

int Connect4Check(int board[Board_rows][Board_cols], int row,int col,int piece){
    int count = 0;
    int i=1;
    int j=1;
    
            if (board[row+i][col] == piece && (row+3<Board_rows)){ // vertical connect4 check
                 while (board[row+i][col] == piece && i<4 && j<4){
                    count++;
                    i++;
                }
                if (count >= 3){
                    return 1;
                } else {
                    count = 0;
                    i=1;
                    j=1;
                }
            }
            if (board[row+i][col+j] == piece && (col+3<Board_cols-1) && (row+3<Board_rows)){ // diagonal connect4 check (\ direction)
                while (board[row+i][col+j] == piece && i<4 && j<4){
                    count++;
                    i++;
                    j++;
                }
                if (count >= 3){
                    return 1;
                } else {
                    count = 0;
                    i=1;
                    j=1;
                }
            }
            if (board[row+i][col-j]==piece && (col-3>0) && (row+3<Board_rows)){ // diagonal connect4 check (/ direction)
                while (board[row+i][col-j] == piece && i<4 && j<4){
                    count++;
                    i++;
                    j++;
                }
                if (count >= 3){
                    return 1;
                } else {
                    count = 0;
                    i=1;
                    j=1;
                }
            }
            if (board[row][col+j]==piece && (col+3 < Board_cols-1)){ // horizontal connect4 check 
                while (board[row][col+j] == piece && j<4){
                    count++;
                    j++;
                }
                if (count >= 3){
                    return 1;
                } else {
                    count = 0;
                    i=1;
                    j=1;
                }
            }
            return 0;
     }
    
int getMove(int board[Board_rows][Board_cols]){
    int col;
    
    printf("Enter column to add piece: ");
    scanf("%d",&col);
   
    while (col<1 || col>Board_cols-2){
        printf("Please enter valid column (between %d and %d): ",1,Board_cols-2);
        scanf("%d",&col);
    }

    while (columnFull(board,col)){
        printf("Column is full, please select a valid column: ");
        scanf("%d",&col);
    }

    return col;
    printf("\n");
}

char PlayAgain(void)
{
	char move;
    printf("\n======================================\n");
	printf("Would you like to play again? ('Y' or 'N'): ");
    scanf("%c", &move);
	// Ignore non-capital letter inputs
	while ((move != 'Y') && (move != 'N')) {
		scanf("%c", &move);
	}
	return move;
}

void ClearScreen(void){
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}


int columnFull(int board[Board_rows][Board_cols], int col){
    int numberOfFreeRows = 0;
    int i;

    for (i=0;i<Board_rows-1;i++){
        if (board[i][col]==SPACE){
            numberOfFreeRows++; // found a free row
        }
    }

    if (numberOfFreeRows>0){
        return 0; // column is not full
    } else {
        return 1; // column is full
    }

}
    






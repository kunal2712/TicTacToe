#include<iostream>
using namespace std;

#define COMPUTER 1
#define HUMAN 2

#define SIDE 3

#define COMPUTERMOVE 'O'
#define HUMANMOVE 'X'

string user_name;

// A function to show the current board status
void showBoard(char board[][SIDE])
{
    for(int i=0; i<SIDE; i++){
        cout<<"\t\t\t";
        for(int j=0; j<SIDE; j++){
            cout<<" ";
            if(board[i][j] == ' '){
                int pos = (i*3)+(j+1);
                cout<<pos;
            }else cout<<board[i][j];
            if(j < SIDE-1) cout<<" |";
        }
        cout<<"\n";
        if(i < SIDE-1) cout<<"\t\t\t-----------\n";
    }
}

void initialise(char board[][SIDE])
{
	// Initially the board is empty
	for (int i=0; i<SIDE; i++)
	{
		for (int j=0; j<SIDE; j++)
			board[i][j] = ' ';
	}
}

// A function to declare the winner of the game
void declareWinner(int whoseTurn, char board[][SIDE])
{
    system("color A");
    system("cls");
	if (whoseTurn == COMPUTER)
		cout<<"COMPUTER won the Match\n";
	else
		cout<<user_name<<" won the Match\n";
    showBoard(board);
}

// A function that returns true if any of the row
// is crossed with the same player's move
bool rowCrossed(char board[][SIDE])
{
	for (int i=0; i<SIDE; i++)
	{
		if (board[i][0] == board[i][1] &&
			board[i][1] == board[i][2] &&
			board[i][0] != ' ')
			return (true);
	}
	return(false);
}

// A function that returns true if any of the column
// is crossed with the same player's move
bool columnCrossed(char board[][SIDE])
{
	for (int i=0; i<SIDE; i++)
	{
		if (board[0][i] == board[1][i] &&
			board[1][i] == board[2][i] &&
			board[0][i] != ' ')
			return (true);
	}
	return(false);
}

// A function that returns true if any of the diagonal
// is crossed with the same player's move
bool diagonalCrossed(char board[][SIDE])
{
	if (board[0][0] == board[1][1] &&
		board[1][1] == board[2][2] &&
		board[0][0] != ' ')
		return(true);

	if (board[0][2] == board[1][1] &&
		board[1][1] == board[2][0] &&
		board[0][2] != ' ')
		return(true);

	return(false);
}

// A function that returns true if the game is over
// else it returns a false
bool gameOver(char board[][SIDE])
{
	return(rowCrossed(board) || columnCrossed(board) || diagonalCrossed(board) );
}

// Function to calculate best score
int minimax(char board[][SIDE], int depth, bool isAI)
{
	int score = 0;
	int bestScore = 0;
	if (gameOver(board) == true)
	{
		if (isAI == true)
			return -10;
		if (isAI == false)
			return +10;
	}
	else
	{
		if(depth < 9)
		{
			if(isAI == true)
			{
				bestScore = -999;
				for(int i=0; i<SIDE; i++)
				{
					for(int j=0; j<SIDE; j++)
					{
						if (board[i][j] == ' ')
						{
							board[i][j] = COMPUTERMOVE;
							score = minimax(board, depth + 1, false);
							board[i][j] = ' '; //BackTrack
							if(score > bestScore)
							{
								bestScore = score;
							}
						}
					}
				}
				return bestScore;
			}
			else
			{
				bestScore = 999;
				for (int i = 0; i < SIDE; i++)
				{
					for (int j = 0; j < SIDE; j++)
					{
						if (board[i][j] == ' ')
						{
							board[i][j] = HUMANMOVE;
							score = minimax(board, depth + 1, true);
							board[i][j] = ' '; //BackTrack
							if (score < bestScore)
							{
								bestScore = score;
							}
						}
					}
				}
				return bestScore;
			}
		}
		else
		{
			return 0; //Draw Case
		}
	}
	return 0;
}

// Function to calculate best move
int bestMove(char board[][SIDE], int moveIndex)
{
	int x = -1, y = -1;
	int score = 0, bestScore = -999;
	for (int i = 0; i < SIDE; i++)
	{
		for (int j = 0; j < SIDE; j++)
		{
			if (board[i][j] == ' ')
			{
				board[i][j] = COMPUTERMOVE;
				score = minimax(board, moveIndex+1, false);
				board[i][j] = ' '; //BackTrack
				if(score > bestScore)
				{
					bestScore = score;
					x = i;
					y = j;
				}
			}
		}
	}
	return x*3+y;
}

// A function to play Tic-Tac-Toe
void playTicTacToe(int whoseTurn)
{
	char board[SIDE][SIDE];
	int moveIndex = 0, x = 0, y = 0;

	initialise(board);
	cout<<endl;
	showBoard(board);

	// Keep playing till the game is over or it is a draw
	while (gameOver(board) == false && moveIndex != SIDE*SIDE)
	{
		int n;
		if (whoseTurn == COMPUTER)
		{
			n = bestMove(board, moveIndex);
			x = n / SIDE;
			y = n % SIDE;
			board[x][y] = COMPUTERMOVE;
			printf("COMPUTER has put a %c in cell %d\n\n", COMPUTERMOVE, n+1);
			showBoard(board);
			moveIndex ++;
			whoseTurn = HUMAN;
		}

		else if (whoseTurn == HUMAN)
		{
			printf("\n\nEnter the position = ");
			string input;
			cin>>input;
			if(input.size()>1) {
				printf("Invalid position\n");
				continue;
			}
			else if(input[0]<'0' || input[0]>'9')
			{
				printf("Invalid position\n");
				continue;
			}
			else
			{
				n=(input[0]-'0');
			}
			n--;
			x = n / SIDE;
			y = n % SIDE;
			if(board[x][y] == ' ' && n<9 && n>=0)
			{
			    system("cls");
				board[x][y] = HUMANMOVE;
				cout<<user_name;
				printf (" has put a %c in cell %d\n\n", HUMANMOVE, n+1);
				showBoard(board);
				moveIndex ++;
				whoseTurn = COMPUTER;
			}
			else if(board[x][y] != ' ' && n<9 && n>=0)
			{
				printf("\nPosition is occupied, select any one place from the available places\n\n");
			}
			else if(n<0 || n>8)
			{
				printf("Invalid position\n");
			}
		}
	}

	// If the game has drawn
	if (gameOver(board) == false && moveIndex == SIDE * SIDE){
        system("color A");
        system("cls");
		cout<<"It's a DRAW\n";
        showBoard(board);
	}
	else
	{
		// Toggling the user to declare the actual winner
		if (whoseTurn == COMPUTER)
			whoseTurn = HUMAN;
		else if (whoseTurn == HUMAN)
			whoseTurn = COMPUTER;

		declareWinner(whoseTurn, board);
	}
}

int main()
{
    system("color B");
	printf("\n-------------------------------------------------------------------\n\n");
	printf("\t\t\t Tic-Tac-Toe\n");
	printf("\n-------------------------------------------------------------------\n\n");
	char cont='y';
	do {
		char choice;
		printf("What is your Name : ");
		cin>>user_name;
	 	printf("Do you want to start first?(y/n) : ");
	 	scanf(" %c", &choice);

		if(choice=='n')
			playTicTacToe(COMPUTER);
		else if(choice=='y')
			playTicTacToe(HUMAN);
		else
			printf("Invalid choice\n");

		printf("\nDo you want to quit(y/n) : ");
       		scanf(" %c", &cont);
	} while(cont=='n');
	return (0);
}
    
#include<iostream>
#include<string>
#include<cmath>				  // Provides Mathematical function
#include<cstdlib>		 	 // Provides random number generater function
#include<ctime>				// Provides add time function
#include<iomanip>
#include<fstream>			// For file handling
using namespace std;

// Structure
struct Player {
	string name;
	char player;
	int score;
};

//Global Variables
char currentPlayer;
int totalgames;
int games;
int draw=0;
Player player[2];
string winner;

// Players Data
void playerData();
void displayData();
void fileHandling();

// First turn
void firstturn();

// NO. of Games
void no_ofgames();

// Game Setup and Input
void initializeBoard(char board[3][3]);
void displayBoard(const char board[3][3]);
bool isValidMove(const char board[3][3], int row, int col);

// Game Logic and Rules
bool checkWin(const char board[3][3], char player);
bool isDraw(const char board[3][3]);
void switchPlayer(char &currentPlayer);

// Main Game Flow
void playGame();

int main() {
	char playagain;
	cout<<"Welcome to Tic-Tac-Toe Game\n";
	do{
	firstturn();
	
    playGame();  // Starts the game
    
    displayData();
    fileHandling();
    cout<<"\nWould you like to play again? (Y/N)";
    cin>>playagain;
}
	while(playagain=='Y' || playagain=='y');
    return 0;
}

// Function Definations:

// Function to determine first turn
void firstturn() {
	int random=0 ;
	int x , y;
	int user1,user2;
	char choice;
	playerData();
	cout<<"\nFirst, We will determine who will get the first turn\n";
	cout<<player[0].name<<", Guess a number from 1 to 100: ";
	cin>>user1;
	while(user1>100 || user1<1){           			 //Error Handling
		cout<<"Invlaid Number\n";
		cout<<"Enter a number from 1 to 100!: ";
		cin>>user1;
	}
		cout<<player[1].name<<", Guess a number from 1 to 100: ";
		cin>>user2;
		while(user2>100 || user2<1 || user2==user1){           //Error Handling
			if(user2==user1){
				cout<<"Can't enter same number as "<<player[0].name<<endl;
				cout << player[1].name <<", Enter a Different number: ";
				cin>>user2;
			}
			else{
			cout<<"Invalid Number\n";
			cout<<"Enter a number from 1 to 100!: ";
			cin>>user2;
		}
		}
	
	int min = 1 , max=100;
	
	srand(time(0));							//Generates Random Number each time the code executes
	random=(rand() % max) + min;        
	
		x=random - user1;
		y=random - user2;
		if(x<0 || y<0){
			x=abs(x);					//Getting the absolute value of x and y
			y=abs(y);
		}
		if(x>y)
		{
			cout  << player[1].name <<" got the first turn\n";
			winner=player[1].name;
		}
		else 
		{
			cout  << player[0].name   <<" got the first turn\n";
				winner=player[0].name;
		}
		cout<<"Choose X or O: ";
			cin>>choice;
			while(1){
			
		if(choice=='X' || choice=='O' || choice=='x' || choice=='o')
		{
			if(choice=='x'){
				choice='X';
			}
			if(choice=='o'){
				choice='O';
			}
			currentPlayer=choice;
			break;
		}
		else{
		cout<<"Invalid Input\n";				//Error Handling
		cout<<"Choose X or O: ";
			cin>>choice;
	   	    }
		}
			if(winner==player[1].name) {
			player[1].player=choice;
			player[0].player=((choice=='X')? 'O' : 'X');
		}
		else if(winner==player[0].name) {
			player[0].player=choice;
			player[1].player=((choice=='X')? 'O' : 'X');
		}
	
}
void playerData() {
	
	cout<<"Players enter your Moniker\n";
	cout<<"Player 1: ";
	cin>>player[0].name;
	cout<<"Player 2: ";
	cin>>player[1].name;
}


void displayData() {
	cout<<"Scoreboard:"<<endl;
	cout << left;     //Aligns text to the left
	cout<<setw(20)<<"Name" <<setw(20) <<"Player" << setw(20) <<"Score" <<endl;
	for(int i=0; i<2; i++){
		cout<<setw(20)<<player[i].name << setw(20);
		cout<<player[i].player << setw(20);
		cout<<player[i].score<<endl;
	}
	cout<< "Draw: "<<draw;
}
void fileHandling() {
	fstream scoreBoard;
	scoreBoard.open("Score_board.txt", ios::out | ios::app);
	if(!scoreBoard){
		cout<<"Error Creating File";
	}
	else{
	scoreBoard<<"Scoreboard:"<<endl;
	scoreBoard << left;     
	scoreBoard<<setw(20)<<"Name" <<setw(20) <<"Player" << setw(20) <<"Score" <<endl;	
	for(int i=0; i<2; i++){	
		scoreBoard<<setw(20)<<player[i].name << setw(20);
		scoreBoard<<player[i].player << setw(20);
		scoreBoard<<player[i].score<<endl;
		
	}
	scoreBoard<< "Draw: "<<draw;
	scoreBoard.close();
}
	
}

void no_ofgames() {
	cout<<"How many games would you like to play?\n";
	cout<<"Best of (1-7): ";
	cin>>games;
	while(games>7 || games<1) {
		cout<<"Invalid games. Enter valid nmuber of games: ";
		cin>>games;
	}
	totalgames=2*games-1;
}

// Initializing the board
void initializeBoard(char board[3][3]) {
    char value = '1';
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            board[i][j] = value++;    // Assigning the value
        }
    }
}
// Diplays the board
void displayBoard(const char board[3][3]) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cout << "   " << board[i][j];
            if (j < 2) cout << "   |  ";
        }
        cout << endl;
        if (i < 2) cout << "-------|---------|--------" << endl;
    }
}
// Error Handling
bool isValidMove(const char board[3][3], int row, int col) {
    return (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] != 'X' && board[row][col] != 'O');
}

bool checkWin(const char board[3][3], char player) {
    // Check rows and columns
    for (int i = 0; i < 3; ++i) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) || 
            (board[0][i] == player && board[1][i] == player && board[2][i] == player)) {
            return true;
        }
	}

    // Check diagonals
    return ((board[0][0] == player && board[1][1] == player && board[2][2] == player) || 
            (board[0][2] == player && board[1][1] == player && board[2][0] == player)); 

}
// Checking if the board has emoty cells
bool isDraw(const char board[3][3]) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                return false; // Empty cell found
            }
        }
    }
    return true; // No empty cells
}
// Switching Players
void switchPlayer(char &currentPlayer) {
    currentPlayer = (currentPlayer == 'X' ) ? 'O' : 'X';
}
// Main flow of game
void playGame() {
		no_ofgames();
		cout<<"Let's begin the games\n\n";
	for(int i=1; i<=totalgames; i++){
		cout<<"Game"<<i<<" of "<<totalgames<<endl;
    char board[3][3];
    bool gameWon = false;

    initializeBoard(board);
    
    while (!gameWon && !isDraw(board)) {
        displayBoard(board);

        // Player input
        int position;
        cout << "Player " << currentPlayer << ", enter your move (1-9): ";
        cin >> position;
        cout<<endl;
        //Determining rows and coloumns
        int row = (position - 1) / 3;		
        int col = (position - 1) % 3;

        if (isValidMove(board, row, col)) {
            board[row][col] = currentPlayer;
            if (checkWin(board, currentPlayer)) {
                gameWon = true;
            } else {
                switchPlayer(currentPlayer);
            }
        } else {
            cout << "Invalid move. Try again.\n";
        }
    }

    displayBoard(board);

    if (gameWon) {
        cout << "Player " << currentPlayer << " wins!\n" <<endl;
        
	if(currentPlayer==player[0].player){
		player[0].score++;
	}
	else{
		player[1].score++;
	}
	if(player[0].score==games || player[1].score==games){
		return;
	}

    } else {
        cout << "It's a draw\n"<<endl;
        draw++;
    
    	}
	}
}


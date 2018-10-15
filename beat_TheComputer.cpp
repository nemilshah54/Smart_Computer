

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
*     Description: This is the program in which computer makes prediction of user input( only 0 or1). If the computer prediction is correct, then computer gets a point
*				   and if it's prediction is wrong the human gets a point. After the couple of moves, the last three moves are updated, computer tracks those moves by creating history table
*				   and then forecast it accordingly. By making most random moves, the computer should win !!!.
* System: Visual Studio 2017 on Windows 10
* Author: Nemil Shah
*---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/


#include<iostream>
#include<string> 
using namespace std;

// Display ID info
void displayIDInfo()
{
	cout << "Author:  Nemil Shah" << endl;
	cout << "Program: 0/1 Guessing" << endl;
	cout << endl;
}//end displayIDInfo()

 // Display Instructions
void displayInstructions()
{
	cout << "Welcome to the 0/1 Guessing Game									" << endl
		<< "                                                                    " << endl
		<< "Enter 0 or 1, trying to outsmart the computer, which is going to    " << endl
		<< "attempt to forecast your guesses.  On each move the score indicator " << endl
		<< "moves to the right if the computer guesses correctly, and moves		" << endl
		<< "to the left if the computer does not.								" << endl
		<< "	Enter 't' to toggle displaying the data table.					" << endl
		<< "	Enter 'r' to reset the board.                                   " << endl
		<< "	Enter 'x' to exit.                                              " << endl
		<< "Good luck, you'll need it!                                          " << endl << endl;
}//end displayInstructions()

 // Function for displaying the score table.
void scoreBoard(char board[], int boardSize, int &pointIndicater) //add perameters, computer wins or computer looses each time
{
	board[pointIndicater] = '^';
	cout << "Computer             Human" << endl;
	cout << "   x---------x+++++++++x" << endl;
	cout << "   ";
	for (int i = 0; i < boardSize; i++)
	{
		cout << board[i];
	}
	cout << endl;
}//END scoreBoard()

 // Display the history table.
void historyTable(int moveHistory[8][2], int lastThreeMoves[3], int computerForcast)
{
	string binColumn[8] = { "000" };
	cout << "     " << " 0   1" << endl;
	cout << "   " << " --- ---" << endl;
	for (int row = 0; row < 8; row++)
	{
		if (row == 0) { binColumn[row] = "000"; }
		else if (row == 1) { binColumn[row] = "001"; }
		else if (row == 2) { binColumn[row] = "010"; }
		else if (row == 3) { binColumn[row] = "011"; }
		else if (row == 4) { binColumn[row] = "100"; }
		else if (row == 5) { binColumn[row] = "101"; }
		else if (row == 6) { binColumn[row] = "110"; }
		else if (row == 7) { binColumn[row] = "111"; }

		cout << binColumn[row]; // Error 
		for (int column = 0; column < 2; column++)
		{
			cout << "   " << moveHistory[row][column];
		}
		cout << endl;
	}
	cout << "Previous three: " << lastThreeMoves[0] << lastThreeMoves[1] << lastThreeMoves[2] << ".     " << "Forcast: " << computerForcast << endl << endl;
}

// Function that compares computer forcast and userinput.
void compreAndUpdateScore(int decUserInput, int computerForcast, int &pointIndicater, char board[], int boardSize)
{
	if (decUserInput == computerForcast)
	{
		board[pointIndicater] = ' ';
		pointIndicater--;
		cout << "Computer gets a point." << endl;
		if (pointIndicater == 5)
		{
			cout << ">>> Computers are about to win <<<" << endl << endl;
		}
		if (pointIndicater == 0)
		{
			cout << "Computer Won!!" << endl << endl;
			scoreBoard(board, boardSize, pointIndicater);
			exit(0);
		}
	}
	else
	{
		board[pointIndicater] = ' ';
		pointIndicater++;
		cout << "Human gets a point." << endl;
		if (pointIndicater == 15)
		{
			cout << ">>> Computers are about to lose <<<" << endl << endl;
		}
		if (pointIndicater == 20)
		{
			cout << "Human Won!!" << endl << endl;

			scoreBoard(board, boardSize, pointIndicater);
			exit(0);
		}
	}
}

// Function that will return the computer forcast.
int getForcast(int lastThreeMoves[], int moveCount, int moveHistory[8][2], int &index)
{
	if (moveCount == 1)
	{
		return 1;
	}
	else if ((moveCount == 2) || (moveCount == 3))
	{
		if (lastThreeMoves[2] == 0)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else if (moveCount > 3)
	{
		if (moveHistory[index][0] == moveHistory[index][1])
		{
			if (lastThreeMoves[2] == 0)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		else
		{
			if (moveHistory[index][0] > moveHistory[index][1])
			{
				return 0;
			}
			else
			{
				return 1;
			}
		}
	}
}// End int getForcast(int lastThreeMoves[],....

 // // Function that will return the computer forcast during the reset command.
int resetGetForcast(int lastThreeMoves[], int moveHistory[8][2], int &index)
{
	if (moveHistory[index][0] == moveHistory[index][1])
	{
		if (lastThreeMoves[2] == 0)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		if (moveHistory[index][0] > moveHistory[index][1])
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
}

// Function to convert binary to decimal.
void convertbinaryToDecimal(int lastThreeMoves[], int &index)
{
	int temp1 = 0, temp2 = 0, temp3 = 0;
	if (lastThreeMoves[0] == 1)
	{
		temp1 = 4;
	}
	if (lastThreeMoves[1] == 1)
	{
		temp2 = 2;
	}
	if (lastThreeMoves[2] == 1)
	{
		temp3 = 1;
	}
	index = temp1 + temp2 + temp3;
}

// Function to update the history table.
void updateHistoryTable(int decUserInput, int moveHistory[8][2], int &index)
{
	moveHistory[index][decUserInput]++;
}

// Function to update the last three moves.
void updateLastThreeMoves(int lastThreeMoves[], int decUserInput, int moveCount)
{
	if (moveCount == 1)
	{
		lastThreeMoves[2] = decUserInput;
	}
	else if (moveCount == 2)
	{
		lastThreeMoves[1] = lastThreeMoves[2];
		lastThreeMoves[2] = decUserInput;

	}
	else
	{
		lastThreeMoves[0] = lastThreeMoves[1];
		lastThreeMoves[1] = lastThreeMoves[2];
		lastThreeMoves[2] = decUserInput;
	}
}

// Function to update the last three moves. ( Function overloading).
void updateLastThreeMoves(int lastThreeMoves[], int decUserInput)
{

	lastThreeMoves[0] = lastThreeMoves[1];
	lastThreeMoves[1] = lastThreeMoves[2];
	lastThreeMoves[2] = decUserInput;

}

// Function to reset the history table when reset command is given.
void resetHistoryTable(int moveHistory[8][2], int lastThreeMoves[3])
{
	cout << endl << "Enter 16 single-digit numbers separated by spaces: ";
	for (int i = 0; i < 3; i++)
	{
		lastThreeMoves[i] = 0;
	}
	for (int row = 0; row < 8; row++)
	{
		for (int column = 0; column < 2; column++)
		{
			cin >> moveHistory[row][column];
		}
	}
}

int main()
{
	int moveCount = 1;      // Variable to count the number of moves.
	const int boardSize = 21;      // Declaring the board size for score table.
	char board[boardSize] = { ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ' };
	int pointIndicater = 10;    // Variable to indicate the score in score table.
	int moveHistory[8][2] = { 0 };  // Array to store the 0 and 1 table for all possiblity
	int computerForcast = 0;    // Stores the computer forcast return from the function.
	char userInput = ' ';
	int decUserInput = 0;       // Converts the char userinput to int userinput.
	int index = 0;              //  Stores binary to decimal.
	int lastThreeMoves[3] = { 0,0,0 };    // Array to show last three moves.
	bool toggleDisp = false;          // Turns off and on the history table.
	bool resetForcast = false;        // Turns off and on the resetforcast function.

	displayIDInfo();		// Display ID information
	displayInstructions();		// Display Instructions

	scoreBoard(board, boardSize, pointIndicater);		// Initially displays the scoretable.
	while (true)
	{
		if (resetForcast == true)		// Get computerforecast with reseting.
		{
			computerForcast = resetGetForcast(lastThreeMoves, moveHistory, index);
		}
		else if (resetForcast == false)		// Get computerforecast without reseting.
		{
			computerForcast = getForcast(lastThreeMoves, moveCount, moveHistory, index);
		}
		if (toggleDisp)		// Displays the history table when the switch of toggle is on.
		{
			historyTable(moveHistory, lastThreeMoves, computerForcast);
		}

		cout << moveCount << ". Your input: ";
		cin >> userInput;

		// Mutiple if conditions to check the datatype of userinput.
		if (isalpha(userInput))
		{
			userInput = toupper(userInput);
			if (userInput == 'X')		// Exit the program.     
			{
				cout << "Thank You for playing" << endl;
				break;
			}
		}
		if (isalpha(userInput))
		{
			userInput = toupper(userInput);
			if (userInput == 'T')		// Toggle the display table.
			{
				if (toggleDisp == false)
				{
					toggleDisp = true;
				}
				else if (toggleDisp == true)
				{
					toggleDisp = false;
				}
				moveCount--;
			}
		}
		if (isalpha(userInput))
		{
			userInput = toupper(userInput);
			if (userInput == 'R')		// Reset the move history table.
			{
				resetForcast = true;

				resetHistoryTable(moveHistory, lastThreeMoves);		// Reset the history table.
				moveCount = 0;

				updateHistoryTable(decUserInput, moveHistory, index);

				convertbinaryToDecimal(lastThreeMoves, index);

				board[pointIndicater] = ' ';
				pointIndicater = 10;		// Reseting the point indicator.
			}
		}
		else
		{
			decUserInput = userInput;		// Converts the char userinput to int userinput.
			if (decUserInput == 48 || decUserInput == 49)
			{
				decUserInput = decUserInput - 48;
			}

			if (moveCount > 3 && resetForcast == false)		// Updates history table without reset command.
			{
				updateHistoryTable(decUserInput, moveHistory, index);
			}
			else if (resetForcast == true)		// Update history table and last three moves by reset command given.
			{
				updateLastThreeMoves(lastThreeMoves, decUserInput);

				updateHistoryTable(decUserInput, moveHistory, index);
			}
			if (resetForcast == false)		// Updates the last three moves without reset command.
			{
				updateLastThreeMoves(lastThreeMoves, decUserInput, moveCount);
			}
			convertbinaryToDecimal(lastThreeMoves, index);		// Converts binary to decimal.
			compreAndUpdateScore(decUserInput, computerForcast, pointIndicater, board, boardSize);      // Compare and update the scores in scoret able
			scoreBoard(board, boardSize, pointIndicater);		// Updated score board.
		}
		moveCount++;
	}
	return 0;
}// END int main()








// RPSgame_Ivan_Echavarria_101092562.cpp : Defines the entry point for the console application.
// Based on chapter 7 RPS
/*
Student Name: Ivan Echavarria
Student Number: 101092562
*/

#include "stdafx.h"
#include <iostream>
#include <cmath>
#include <string>
#include <time.h>
#include <fstream>
#include <iomanip>


using namespace std;
// Function prototypes

string getName(); 
void displayMenu(); 
bool computerChoice(); 
char computerSelection;
void retreiveRanks();
void fillDatabase();
struct playerInfo { int rank; string name; int wins; };
void endGame(); 
enum objectType { ROCK, PAPER, SCISSORS };
void displayRules();
objectType retrievePlay(char selection);
bool validSelection(char selection);
void convertEnum(objectType object);
objectType winningObject(objectType play1, objectType computer);
void gameResult(objectType play1, objectType computer, int& winner);
void displayResults(int gCount, int wCount1, int wCount2);
void updateFile(string name,int winCount1, int winCount2);
playerInfo dataBase[5]; // Database stores 5 ranks.
bool inGame = false;
string name;


int main()
{
	//fill database
	fillDatabase();
	// Get Player name;
	 name = getName();

	int gameCount; //variable to store the number of
				   //games played
	int winCount1; //variable to store the number of games
				   //won by player 1
	int winCount2; //variable to store the number of games
				   //won by computer
	int gamewinner = -1;

	char selection1;//Player selection character

	objectType play1; //player1's selection
	objectType computer; //computer selection
						
	gameCount = 0;
	winCount1 = 0;
	winCount2 = 0;

	// Display player name
	cout << "Current Player Name: " << name << endl;
	cout << endl;

	//Call menu function display, menu.
	displayMenu();

	//Game logic and input gathering.
	while (inGame)
	{
		cout << "Player enter your choice: ";
		cin >> selection1;
		cout << endl << endl;

		if (validSelection(selection1) && computerChoice())
		{
			play1 = retrievePlay(selection1);
			computer = retrievePlay(computerSelection);
			gameCount++;
			gameResult(play1, computer, gamewinner);
			if (gamewinner == 1)
				winCount1++;
			else if (gamewinner == 2)
				winCount2++;
		}
		
		cout << "Do you want to play again? Enter Y/y, anything else ends the game."<< endl; 
		endGame();
		cout << endl;
	}
	
	//updates the text file that contains the ranks
	updateFile(name,winCount1,winCount2);

	//Display results of the game
	displayResults(gameCount, winCount1, winCount2); 
	cout << endl << "Thanks for playing";


	return 0;
}

string getName()
{
	string input;
	cout << "Please enter your name: ";
	cin >> input;
	cout << endl;

	if (input.length() < 1)
	{
		cout << "The string is empty";
	}

	return input;
}

void displayMenu()
{
	cout << "1. Start Game" << endl;
	cout << "2. Change Player name" << endl;
	cout << "3. Show highest scores" << endl;
	cout << "4. Exit" << endl << endl;

	cout << "Enter your choice : " << endl;

	char input;
	cin >> input;

	switch (input)
	{
	case '1':
		displayRules();
		inGame = true;
		break;
	case '2':
		name = getName();
		displayMenu();
		break;
	case '3':
		retreiveRanks();
		cout << endl;
		displayMenu();
		break;
	case '4':
		inGame = false;
		break;
	default:
		displayMenu();
		break;
	}

}

bool computerChoice()
{
	srand((unsigned)time(NULL));
	int selection = rand()%3; // random selection to choose RPS

	switch (selection)
	{
	case 0:
		computerSelection = 'R';
		break;
	case 1:
		computerSelection = 'S';
		break;
	case 2:
		computerSelection = 'P';
		break;
	}
	return true; 
}

void endGame()
{
	char newGame;
	cin >> newGame;

	switch (newGame)
	{
	case 'y':
	case 'Y':
		inGame = true;
		break;
	default:
		inGame = false;
	}

}

void displayRules()
{
	cout << " Welcome to the game of Rock, Paper, "
		<< "and Scissors." << endl;
	cout << " This is a game for two players. For each "
		<< "game, each" << endl;
	cout << " player selects one of the objects, Rock, "
		<< "Paper or Scissors." << endl;
	cout << " The rules for winning the game are: " << endl;
	cout << "1. If both players selects the same object, it "
		<< "is a tie." << endl;
	cout << "2. Rock breaks Scissors: So player who selects "
		<< "Rock wins." << endl;
	cout << "3. Paper covers Rock: So player who selects "
		<< "Paper wins." << endl;
	cout << "4. Scissors cuts Paper: So player who selects "
		<< "Scissors wins." << endl << endl;
	cout << "Enter R or r to select Rock, P or p to select "
		<< "Paper, and S or s to select Scissors." << endl << endl;
}

bool validSelection(char selection)
{
	switch (selection)
	{
	case 'R':
	case 'r':
	case 'P':
	case 'p':
	case 'S':
	case 's':
		return true;
	default:
		return false;
	}
}

objectType retrievePlay(char selection)
{
	objectType object;
	switch (selection)
	{
	case 'R':
	case 'r':
		object = ROCK;
		break;
	case 'P':
	case 'p':
		object = PAPER;
		break;
	case 'S':
	case 's':
		object = SCISSORS;
	}
	return object;
}

void convertEnum(objectType object)
{
	switch (object)
	{
	case ROCK:
		cout << "Rock";
		break;
	case PAPER:
		cout << "Paper";
		break;
	case SCISSORS:
		cout << "Scissors";
	}
}
objectType winningObject(objectType play1, objectType computer)
{
	if ((play1 == ROCK && computer == SCISSORS) || (computer == ROCK && play1 == SCISSORS))
		return ROCK;
	else if ((play1 == ROCK && computer == PAPER) || (computer == ROCK && play1 == PAPER))
		return PAPER;
	else
		return SCISSORS;
}
void gameResult(objectType play1, objectType computer, int& winner)
{
	objectType winnerObject;

	if (play1 == computer)
	{
		winner = 0;
		cout << "Both players selected ";
		convertEnum(play1);
		cout << ". This game is a tie." << endl<< endl;
	}
	else
	{
		winnerObject = winningObject(play1, computer);
		//Output each player's choice
		cout << "Player 1 selected ";
		convertEnum(play1);
		cout << " Computer selected ";
		convertEnum(computer);
		cout << ". ";

		//Decide the winner
		if (play1 == winnerObject)
		{
			winner = 1;
		}
		else if (computer == winnerObject)
			winner = 2;
		//Output the winner
		cout << "Player " << winner << " wins this game."<< endl << endl;
	}
}

void fillDatabase()
{
	ifstream inFile;
	ofstream outFile;
	int dataBaseLen = sizeof(dataBase) / sizeof(dataBase[0]);

	inFile.open("ranks.txt");
	if (!inFile)
	{
		cout << "Cant open file" << endl;
		cout << "Creating file" << endl;
		outFile.open("ranks.txt");

		//if file is empty fill it with dummy data
		for (int j = 0; j < dataBaseLen; j++)
		{
			dataBase[j].rank = -1;
			dataBase[j].name = "dummy";
			dataBase[j].wins = -1;
		}
		outFile.close();
	}
	else
	{
		for (int i = 0; i < dataBaseLen; i++)
		{
			inFile >> dataBase[i].rank >> dataBase[i].name >> dataBase[i].wins;
		}
	}

	inFile.close();
}

void retreiveRanks()
{
	int dataBaseLen = sizeof(dataBase) / sizeof(dataBase[0]);
    cout << setw(27)<<"Players' rank" << endl;
	cout << setw(5) << "Rank" << setw(20) <<"Player Name" << setw(15) << "No Wins " << endl;
	cout << "-----------------------------------------------" << endl;

	for (int i = 0; i < dataBaseLen; i++)
	{
		cout << setw(5) <<dataBase[i].rank << setw(17) << dataBase[i].name << setw(12) << dataBase[i].wins << endl;
	}
	
}

void updateFile(string name, int winCount1, int winCount2)
{
	//file writer	
	ofstream outFile;
	playerInfo tempDataBase[2];
	int len = sizeof(tempDataBase) / sizeof(tempDataBase[0]);
	int dataBaseLen = sizeof(dataBase) / sizeof(dataBase[0]);

	tempDataBase[0].name = name;
	tempDataBase[0].rank = 0;
	tempDataBase[0].wins = winCount1;

	tempDataBase[1].name = "computer";
	tempDataBase[1].rank = 0;
	tempDataBase[1].wins = winCount2;

	for (int j = 0; j < len; j++)
	{	
		for (int i = 0; i < dataBaseLen; i++)
		{
			if (tempDataBase[j].wins >= dataBase[i].wins)
			{
				playerInfo tempRank = dataBase[i];
				dataBase[i] = tempDataBase[j];
				tempDataBase[j] = tempRank;
			}
			dataBase[i].rank = i + 1;
		}
	}
	
	outFile.open("ranks.txt");
	for (int i = 0; i < dataBaseLen; i++)
	{
		outFile << dataBase[i].rank << " " << dataBase[i].name << " " << dataBase[i].wins << "\n";
	}
	outFile.close();

}

void displayResults(int gCount, int wCount1, int wCount2)
{
	cout << "The total number of plays: " << gCount << endl;
	cout << "The number of plays won by player 1: " << wCount1 << endl;
	cout << "The number of plays won by computer: " << wCount2 << endl;
}



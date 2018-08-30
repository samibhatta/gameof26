/* -----------------------------------------------------------------------------

FILE:              cardgame.h

DESCRIPTION:       This is a header file for cardgame.cpp

COMPILER:          visual studio 2013

MODIFICATION HISTORY:

Author                   Date                Version
---------------          ----------          --------------
Samikchhya Bhatta        2015-03-08          Version Number 11

----------------------------------------------------------------------------- */
# include<iostream>
# include<string>
# include<conio.h>
#include <time.h>
#include <fstream>
#include <sstream>
#include "player.h"
using namespace std;

class Cardgame{

public:
	/* ****************************************** methods **************************************** */
	Cardgame();
	//void showOptions();
	void showPlayerOptions();
	//void initGameSetting();
	//void run();
	void resetCards();
	void printCards();
	void printPlayersCards(Player player);
	void playAgainstHuman();
	void playAgainstComputer();
	void setPlayer(int howMany);
	int selectRandomCards();
	int countRemainingCards();
	int getTotalSumOfCards(int card[5]);
	void initPlayers();
	void startGame();
	void resumeGame();
	bool showCards();
	bool discardCards();
	void saveGame();
	int decideWinner();
	void replaceRandomCards(int cardcount);
	string* splitMyString(string mystring, string delimeter);
	void readFromFile(string filename);
	void saveToFile(string filename);



	/* ***************************************** variables *************************************** */
	//Rounds of game
	int HANDS;
	//Margin in the left side of screen
	string PADDING;
	//option, start a new game or resume old game
	int option;
	//mode single player or multipleyer
	bool MULTIPLAYER;
	//current round
	int CURRENT_ROUND;
	//current player
	Player CURRENT_PLAYER;
	//DECIDING value
	int DECIDING_VALUE;
	//computers anme
	string COMPUTERS_NAME;
	int cards[4][13];
	Player player1;
	Player player2;
	//flag to mark the card as already used 
	int CARDTAKEN;
};
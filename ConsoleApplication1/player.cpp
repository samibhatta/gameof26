/* -----------------------------------------------------------------------------

FILE:              player.cpp

DESCRIPTION:       It consists of functions for player.h 

COMPILER:          visual studio 2013

MODIFICATION HISTORY:

Author                   Date                Version
---------------          ----------          --------------
Samikchhya Bhatta        2015-03-08          Version Number 11

----------------------------------------------------------------------------- */
#include "player.h"
/* -----------------------------------------------------------------------------
FUNCTION:           Player()
DESCRIPTION:        constructor
----------------------------------------------------------------------------- */
Player::Player(){
	this->wincount = 0;
}

/* -----------------------------------------------------------------------------
FUNCTION:           setName(string name)
DESCRIPTION:        sets player name
----------------------------------------------------------------------------- */

void Player::setName(string name){
	this->name = name;
}

/* -----------------------------------------------------------------------------
FUNCTION:           setWinCount(int wincount)
DESCRIPTION:        sets player point
----------------------------------------------------------------------------- */
void Player::setWinCount(int wincount){
	this->wincount = wincount;
}
/* -----------------------------------------------------------------------------
FUNCTION:           setCards(int cards5[5])
DESCRIPTION:        sets player cards
----------------------------------------------------------------------------- */
void Player::setCards(int cards5[5]){
	for (int i = 0; i<5; i++){
		this->currentCards[i] = cards5[i];
	}
}
/* -----------------------------------------------------------------------------
FUNCTION:           getName()
DESCRIPTION:        gets player name
----------------------------------------------------------------------------- */
string Player::getName(){
	return this->name;
}
/* -----------------------------------------------------------------------------
FUNCTION:           getWinCount()
DESCRIPTION:        gets player point
----------------------------------------------------------------------------- */
int Player::getWinCount(){
	return this->wincount;
}
/* -----------------------------------------------------------------------------
FUNCTION:           getCards()
DESCRIPTION:        gets player cards
----------------------------------------------------------------------------- */
int* Player::getCards(){
	int* temp_card = new int[5];
	for (int i = 0; i<5; i++){
		temp_card[i] = this->currentCards[i];
	}
	return temp_card;
}
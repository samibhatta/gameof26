/* -----------------------------------------------------------------------------

FILE:              player.h

DESCRIPTION:        This is the header file 

COMPILER:          visual studio 2013

MODIFICATION HISTORY:

Author                   Date                Version
---------------          ----------          --------------
Samikchhya Bhatta        2015-05-15          Version Number 11

----------------------------------------------------------------------------- */
#include <string>
using namespace std;
class Player{
private:
	string name;//player name
	int wincount;//increment points if player wins
	int currentCards[5];//5 cards in hand

public:
	Player();
	void setName(string name);
	void setWinCount(int wincount);
	void setCards(int cards5[5]);
	string getName();
	int getWinCount();
	int* getCards();
};
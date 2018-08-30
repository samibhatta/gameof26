/* -----------------------------------------------------------------------------

FILE:              maingame.h

DESCRIPTION:        This is the header file for maingame.cpp

COMPILER:          visual studio 2013

MODIFICATION HISTORY:

Author                   Date                Version
---------------          ----------          --------------
Samikchhya Bhatta        2015-05-15          Version Number 11

----------------------------------------------------------------------------- */
# include "cardgame.h"
#include<conio.h>

/*************************************** We run everything here ************************************/
class Maingame :public Cardgame{
public:
	Maingame();
	void run();
	void showOptions();
	void initGameSetting();
	void play();
private:
};
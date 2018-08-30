/* -----------------------------------------------------------------------------

FILE:              maingame.cpp

DESCRIPTION:        This is a driver

COMPILER:          visual studio 2013

MODIFICATION HISTORY:

Author                   Date                Version
---------------          ----------          --------------
Samikchhya Bhatta        2015-03-08          Version Number 11

----------------------------------------------------------------------------- */
#include "maingame.h"
using namespace std;

/* -----------------------------------------------------------------------------
FUNCTION:           Maingame()
DESCRIPTION:        constructor
----------------------------------------------------------------------------- */
Maingame::Maingame(){
}


int main(){
	//cout<<"in entrypoint"<<endl;
	//getch();
	Maingame mg;
	mg.run();
	//mg.play();

	return 1;
}
/* -----------------------------------------------------------------------------
FUNCTION:           run()
DESCRIPTION:        calls showOptions();
					initGameSetting();
	----------------------------------------------------------------------------- */
void Maingame::run(){
	//cout<<CURRENT_ROUND<<endl<<COMPUTERS_NAME<<endl;
	showOptions();
	initGameSetting();
}

/* -----------------------------------------------------------------------------
FUNCTION:           showoptions()
DESCRIPTION:        display menu
----------------------------------------------------------------------------- */
void Maingame::showOptions(){
	cout << PADDING << "WELCOME TO THE GAME OF 26" << endl;
	cout << PADDING << "=========================" << endl << endl;
	cout << PADDING << "1. New game" << endl;
	cout << PADDING << "2. Resume" << endl;
	cout << PADDING << "Do you want to start a new game or resume the suspended game? : ";
	cin >> option;
}
/* -----------------------------------------------------------------------------
FUNCTION:           initGameSetting()
DESCRIPTION:        reset cards, shows player menu option,asks user to enter the name of the game file to save 
the game
----------------------------------------------------------------------------- */

void Maingame::initGameSetting(){
	string filename;
	int playagain = 1;
	switch (option){
	case 1:
		//Start a new game
		this->resetCards();
		this->showPlayerOptions();
		play();
		cout << " DO YOU WANT PLAY AGAIN ?" << endl;
		cout << "1. YES" << endl;
		cout << "2. NO" << endl;
		cout << "Enter your choice : ";
		cin >> playagain;
		if (playagain == 1){
			this->run();
		}
		break;
	case 2:
		//Resume an old game 
		cout << PADDING << "Enter game file name : ";
		cin >> filename;
		readFromFile(filename);
		//getch();
		//cout<<"current round="<<CURRENT_ROUND<<endl;
		play();
		cout << " DO YOU WANT PLAY AGAIN ?" << endl;
		cout << "1. YES" << endl;
		cout << "2. NO" << endl;
		cout << "Enter your choice : ";
		cin >> playagain;
		if (playagain == 1){
			this->run();
		}

		break;
	default:
		system("CLS");
		cout << PADDING << "Invalid Input. Please try again.." << endl << endl;
		this->showOptions();
		this->initGameSetting();
	}

}
/* -----------------------------------------------------------------------------
FUNCTION:           play()
DESCRIPTION:       creates turn for player one and two,saves the game
----------------------------------------------------------------------------- */
void Maingame::play(){
	//cout<<CURRENT_ROUND<<endl;
	for (int roundCounter = CURRENT_ROUND; roundCounter <= HANDS; roundCounter++){
		CURRENT_ROUND = roundCounter;
		cout << PADDING << "ROUND " << roundCounter << endl;
		cout << PADDING << "***********************************" << endl << endl;
		cout << PADDING << "NOW PLAYING : " << CURRENT_PLAYER.getName() << endl;
		bool continue_playing = true;
		do{
			bool inputNotValid = false;
			printPlayersCards(CURRENT_PLAYER);
			int discardedCard_count = 0;//ask the user number of cards to discard,initially 0
			int playing_option = 1;

			do{
				bool computer_is_playing = false;
				if (MULTIPLAYER == false){
					if (!CURRENT_PLAYER.getName().compare(COMPUTERS_NAME)) {//check if the current player is computer
						srand(time(NULL));
						playing_option = rand() % 2; // generate random number 1 and two for the option menu
						playing_option = playing_option + 1;//(0+1 because no 0 option
						string todo_what;//allows us to know what computer wants to do show or discard
						if (playing_option == 1){ todo_what = "show"; }
						else{ todo_what = "discard"; }//assign whether comuter wants to discard or show
						cout << PADDING << "Computer wants to " << todo_what << PADDING << " Please wait.." << endl;
						computer_is_playing = true;
					}
				}

				if (!computer_is_playing){// human player

					cout << endl;
					cout << PADDING << "1. Show cards" << endl;
					cout << PADDING << "2. Discard cards" << endl;
					cout << PADDING << "3. Quit game" << endl;
					cout << PADDING << "Enter your choice : ";
					cin >> playing_option;

				}
				switch (playing_option){ //option from menu
				case 1:
					inputNotValid = false;//if input is valid
					continue_playing = showCards();
					int card5_player1[5], card5_player2[5];//five cards to players
					for (int i = 0; i<5; i++){
						card5_player1[i] = selectRandomCards();
						card5_player2[i] = selectRandomCards();
					}

					this->player1.setCards(card5_player1);
					this->player2.setCards(card5_player2);
					cout << PADDING << "| Score board : " << player1.getName() << ":" << player1.getWinCount() << " and " << player2.getName() << ":" << player2.getWinCount() << endl;
					cout << PADDING << "+--------------------------------------------------------------" << endl << endl;
					break;
				case 2:
					inputNotValid = false;
					continue_playing = discardCards();
					break;
				case 3:
					inputNotValid = false;
					continue_playing = false;
					saveGame();
					break;
				default:
					cout << endl << PADDING << "Woah!, your input is invalid. Please try again" << endl;
					inputNotValid = true;
					break;
				}

			} while (inputNotValid);


		} while (continue_playing == true);

	}
}



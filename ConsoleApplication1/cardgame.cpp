/* -----------------------------------------------------------------------------

FILE:              cardgame.cpp

DESCRIPTION:        It consists of card game functions implementation

COMPILER:          visual studio 2013

MODIFICATION HISTORY:

Author                   Date                Version
---------------          ----------          --------------
Samikchhya Bhatta        2015-03-08          Version Number 11

----------------------------------------------------------------------------- */
#include "maingame.h"

/* -----------------------------------------------------------------------------
FUNCTION:           Cardgame()
DESCRIPTION:        constructor ,initializes value
----------------------------------------------------------------------------- */
Cardgame::Cardgame(){
	this->HANDS = 7;
	this->PADDING = "   ";
	this->CARDTAKEN = -1;
	this->DECIDING_VALUE = 26;
	this->CURRENT_ROUND = 1;
	this->COMPUTERS_NAME = "COMPUTER";
}

/* -----------------------------------------------------------------------------
FUNCTION:          showPlayerOptions()
DESCRIPTION:        displays menu option, shows whether single player is playing with computer, or two playrs
					and starts the game
----------------------------------------------------------------------------- */

void Cardgame::showPlayerOptions(){
	system("CLS");
	int playerOption;
	cout << PADDING << "PLEASE SELECT A MODE" << endl;
	cout << PADDING << "=========================" << endl << endl;
	cout << PADDING << "1. Play against human" << endl;
	cout << PADDING << "2. Play against computer" << endl;
	cout << PADDING << "Do you want to play with a friend or play against computer ? : ";
	cin >> playerOption;

	switch (playerOption){
	case 1:
		this->MULTIPLAYER = true;
		initPlayers();
		startGame();
		break;
	case 2:
		this->MULTIPLAYER = false;
		initPlayers();
		startGame();
		break;
	default:
		this->showPlayerOptions();
		break;
	}
}

void Cardgame::initPlayers(){
	system("CLS");
	string player1name;
	string player2name;
	int card5_player1[5], card5_player2[5];
	if (this->MULTIPLAYER == true){
		cout << PADDING << "TWO PLAYER MODE " << endl << endl;
		cout << PADDING << "Player 1 : ";
		cin >> player1name;
		cout << PADDING << "Player 2 : ";
		cin >> player2name;
	}
	else{
		cout << PADDING << "SINGLE PLAYER MODE " << endl << endl;
		cout << PADDING << "Enter your name : ";
		cin >> player1name;
		player2name = COMPUTERS_NAME;
	}

	/* initially each player has 5 cards*/
	for (int i = 0; i<5; i++){
		card5_player1[i] = selectRandomCards();
		card5_player2[i] = selectRandomCards();
	}

	this->player1.setName(player1name);
	this->player2.setName(player2name);
	this->player1.setCards(card5_player1);
	this->player2.setCards(card5_player2);
}


void Cardgame::startGame(){
	this->CURRENT_ROUND = 1;
	this->CURRENT_PLAYER = player1;
}

void Cardgame::resumeGame(){

}


bool Cardgame::showCards(){
	int winner = decideWinner();
	//change the player
	if (!CURRENT_PLAYER.getName().compare(player1.getName())) { CURRENT_PLAYER = player2; }
	else{ CURRENT_PLAYER = player1; }//compares points

	switch (winner){
	case 0:
		cout << endl << PADDING << "There is a tie" << endl;
		cout << PADDING << "NOW PLAYING : " << CURRENT_PLAYER.getName() << endl;
		return true;//continue_playing = true;
		break;
	case 1:
		cout << PADDING << "| " << player1.getName() << " Wins" << endl;
		return false;//continue_playing = false;
		break;
	case 2:
		cout << PADDING << "| " << player2.getName() << " Wins" << endl;
		return false;//continue_playing = false;
		break;
	default:
		cout << endl << PADDING << "oops somethings wrong while deciding winner !" << endl;
		cout << PADDING << "press any key to exit";
		getch();
		exit(1);
	}

}

bool Cardgame::discardCards(){
	int cardcount;
	if (MULTIPLAYER == false){
		if (!CURRENT_PLAYER.getName().compare(COMPUTERS_NAME)) {
			//computer is playingint how_many;
			do{
				srand(time(NULL));
				cardcount = rand() % 5;
			} while (cardcount < 0 || cardcount == 1 || cardcount >= 5);
			replaceRandomCards(cardcount);
			return true;
		}
	}

	bool validinput = true;
	do{
		cout << endl << PADDING << "Discard how many cards (0,2,3,4)? : ";
		cin >> cardcount;
		if (cardcount <0 || cardcount == 1 || cardcount >= 5){//1 is invalid
			validinput = false;
			cout << endl << PADDING << "Invalid input. Enter again : ";
		}
		else{
			validinput = true;
			replaceRandomCards(cardcount);
			//printPlayersCards(CURRENT_PLAYER);
		}
	} while (validinput = false);

	//change the player
	if (!CURRENT_PLAYER.getName().compare(player1.getName())) { CURRENT_PLAYER = player2; }
	else{ CURRENT_PLAYER = player1; }

	cout << PADDING << "NOW PLAYING : " << CURRENT_PLAYER.getName() << endl;

	return true;//continue_playing = true;
}

void Cardgame::replaceRandomCards(int cardcount){
	/* --- discarding cards ---*/
	int count = 0;
	int *card5_player = CURRENT_PLAYER.getCards();

	do{
		srand(time(NULL));
		int index = rand() % 5;//generate randon cards
		if (card5_player[index] != CARDTAKEN){
			card5_player[index] = CARDTAKEN;
			count++;
		}
	} while (count <= cardcount);
	/* ---- resetting discarded cards ---- */
	int resetCards[5];
	for (int i = 0; i<5; i++){
		if (card5_player[i] == CARDTAKEN){
			resetCards[i] = selectRandomCards();
		}
		else{
			resetCards[i] = card5_player[i];
		}
	}
	CURRENT_PLAYER.setCards(resetCards);
	cout << endl << PADDING << "Card discarded" << endl << PADDING << "------------------------------" << endl;
}

void Cardgame::saveGame(){
	string filename;
	cout << PADDING << "Enter game file name : ";
	cin >> filename;
	saveToFile(filename);
	cout << endl << PADDING << "GAME SAVED IN " << filename << ". Press any key to EXIT";
	getch();
	exit(1);
}


int Cardgame::decideWinner(){
	int sumtotal_player1 = getTotalSumOfCards(player1.getCards());//adds total of player 1
	int sumtotal_player2 = getTotalSumOfCards(player2.getCards());// adds total of player 1

	cout << PADDING << "+--------------------------------------------------------------" << endl;
	cout << PADDING << "| sum of 5 cards : " << player1.getName() << " = " << sumtotal_player1 << " and " << player2.getName() << " = " << sumtotal_player2 << endl;
	int difference1 = DECIDING_VALUE - sumtotal_player1;//deciding value =26
	difference1 = difference1<0 ? difference1*(-1) : difference1;//if difference 1 is less than 0 return difference 1*-1

	int difference2 = DECIDING_VALUE - sumtotal_player2;
	difference2 = difference2<0 ? difference2*(-1) : difference2;

	if (difference1 == difference2){
		//there is a tie
		return 0;
	}
	else{
		if (difference1<difference2){
			//player 1 is the winner
			player1.setWinCount(player1.getWinCount() + 1);
			return 1;
		}
		else{
			//player 2 is the winner
			player2.setWinCount(player2.getWinCount() + 1);
			return 2;
		}
	}
}
/* -----------------------------------------------------------------------------
FUNCTION:          resetCards()
DESCRIPTION:        displays array of cards
----------------------------------------------------------------------------- */
void Cardgame::resetCards()
{

	/* CLUB */
	this->cards[0][0] = 1;
	this->cards[0][1] = 2;
	this->cards[0][2] = 3;
	this->cards[0][3] = 4;
	this->cards[0][4] = 5;
	this->cards[0][5] = 6;
	this->cards[0][6] = 7;
	this->cards[0][7] = 8;
	this->cards[0][8] = 9;
	this->cards[0][9] = 10;
	this->cards[0][10] = 10;
	this->cards[0][11] = 10;
	this->cards[0][12] = 10;

	/* DIAMOND */
	this->cards[1][0] = 1;
	this->cards[1][1] = 2;
	this->cards[1][2] = 3;
	this->cards[1][3] = 4;
	this->cards[1][4] = 5;
	this->cards[1][5] = 6;
	this->cards[1][6] = 7;
	this->cards[1][7] = 8;
	this->cards[1][8] = 9;
	this->cards[1][9] = 10;
	this->cards[1][10] = 10;
	this->cards[1][11] = 10;
	this->cards[1][12] = 10;

	/* HEART */
	this->cards[2][0] = 1;
	this->cards[2][1] = 2;
	this->cards[2][2] = 3;
	this->cards[2][3] = 4;
	this->cards[2][4] = 5;
	this->cards[2][5] = 6;
	this->cards[2][6] = 7;
	this->cards[2][7] = 8;
	this->cards[2][8] = 9;
	this->cards[2][9] = 10;
	this->cards[2][10] = 10;
	this->cards[2][11] = 10;
	this->cards[2][12] = 10;

	/* SPADE */
	this->cards[3][0] = 1;
	this->cards[3][1] = 2;
	this->cards[3][2] = 3;
	this->cards[3][3] = 4;
	this->cards[3][4] = 5;
	this->cards[3][5] = 6;
	this->cards[3][6] = 7;
	this->cards[3][7] = 8;
	this->cards[3][8] = 9;
	this->cards[3][9] = 10;
	this->cards[3][10] = 10;
	this->cards[3][11] = 10;
	this->cards[3][12] = 10;

	/* NOTE */
	/*
	X-index 0 = Clubs
	X-index 1 = Diamond
	X-index 2 = Hearts
	X-index 3 = Spades

	Y-index 0 = "Ace"
	Y-index 1 = "2"
	Y-index 2 = "3"
	Y-index 3 = "4"
	Y-index 4 = "5"
	Y-index 5 = "6"
	Y-index 6 = "7"
	Y-index 7 = "8"
	Y-index 8 = "9"
	Y-index 9 = "10"
	Y-index 10 = "Jack"
	Y-index 11 = "Queen"
	Y-index 12 = "King"
	*/
}



int Cardgame::selectRandomCards(){
	srand(time(NULL));//randonly generate number
	int i, j, temp;
	do{
		i = rand() % 4;
		j = rand() % 13;
		temp = this->cards[i][j];
	} while (temp == CARDTAKEN);
	this->cards[i][j] = CARDTAKEN;

	/*now check if we have less than 20 cards. if yes, reset the cards */
	if (this->countRemainingCards() <= 20){
		cout << "| card is less than 20. resetting the deck now" << endl;
		this->resetCards();
	}

	//return selected card
	return temp;
}


int Cardgame::countRemainingCards(){
	int remaining_card_count = 0;
	for (int i = 0; i<4; i++){
		for (int j = 0; j<13; j++){
			if (this->cards[i][j] != CARDTAKEN){
				remaining_card_count++;
			}
		}
	}

	return remaining_card_count;
}

void Cardgame::printPlayersCards(Player player){
	int *currentCards = player.getCards();
	cout << endl << PADDING << "Cards" << endl << endl;
	cout << PADDING;
	for (int i = 0; i<4; i++){
		cout << currentCards[i] << " | ";
	}
	cout << currentCards[4];
	cout << PADDING << PADDING << "Sum = " << this->getTotalSumOfCards(currentCards);
	cout << endl;
}

int Cardgame::getTotalSumOfCards(int card[5]){
	int sum = 0;
	for (int i = 0; i<5; i++){
		sum += card[i];
	}

	return sum;
}

void Cardgame::printCards(){
	for (int i = 0; i<4; i++){
		for (int j = 0; j<13; j++){
			cout << "cards[" << i << "][" << j << "]=" << this->cards[i][j] << endl;
		}
	}
	getch();
}

string* Cardgame::splitMyString(string mystring, string delimeter){
	string* temp_string_array = new string[55];
	std::string s = mystring;
	std::string delimiter = delimeter;

	size_t pos = 0;
	std::string token;
	int i = 0;
	while ((pos = s.find(delimiter)) != std::string::npos) {
		token = s.substr(0, pos);
		temp_string_array[i++] = token;
		//std::cout << token << std::endl;
		s.erase(0, pos + delimiter.length());
	}
	temp_string_array[i] = s;
	return temp_string_array;
	//std::cout << s << std::endl;
}
/* -----------------------------------------------------------------------------
FUNCTION:          readFromFile(string filename)
DESCRIPTION:        reads from file
----------------------------------------------------------------------------- */
void Cardgame::readFromFile(string filename){
	//loop will run 10 times
	int counter = 1;
	string *cards_;

	string *cardsection;
	string *keyvalue;
	string *playercard;
	int p1wincount;
	int p2wincount;
	ifstream myReadFile;
	myReadFile.open(filename);
	char output[500];
	int card5_player1[5];
	int card5_player2[5];
	if (myReadFile.is_open()) {
		while (!myReadFile.eof()) {// reads file line by line
			myReadFile >> output;
			switch (counter){
			case 1:
				//player1
				player1.setName(output);
				break;
			case 2:
				//player 2
				player2.setName(output);
				break;
			case 3:
				//score of player 1
				p1wincount = std::stoi(output); //convert string to integer
				player1.setWinCount(p1wincount);
				break;
			case 4:
				//score of player 2
				p2wincount = std::stoi(output); //convert string to integer
				player2.setWinCount(p2wincount);
				break;
			case 5:
				//current round
				this->CURRENT_ROUND = std::stoi(output); //convert string to integer
				break;
			case 6:
				//play against human
				this->MULTIPLAYER = std::stoi(output) == 0 ? false : true;
				break;
			case 7:
				//all cards
				cards_ = splitMyString(output, ",");
				for (int n = 0; n<52; n++){
					cardsection = splitMyString(cards_[n], "=");
					int value = std::stoi(cardsection[1]);
					keyvalue = splitMyString(cardsection[0], "_");
					int i = std::stoi(keyvalue[0]);
					int j = std::stoi(keyvalue[1]);
					cards[i][j] = value;
				}
				break;
			case 8:
				//player one's card

				playercard = splitMyString(output, "_");

				card5_player1[0] = std::stoi(playercard[0]);
				card5_player1[1] = std::stoi(playercard[1]);
				card5_player1[2] = std::stoi(playercard[2]);
				card5_player1[3] = std::stoi(playercard[3]);
				card5_player1[4] = std::stoi(playercard[4]);
				player1.setCards(card5_player1);
				break;
			case 9:
				//player two's card
				playercard = splitMyString(output, "_");

				card5_player2[0] = std::stoi(playercard[0]);
				card5_player2[1] = std::stoi(playercard[1]);
				card5_player2[2] = std::stoi(playercard[2]);
				card5_player2[3] = std::stoi(playercard[3]);
				card5_player2[4] = std::stoi(playercard[4]);
				player2.setCards(card5_player2);
				break;
			case 10:
				//current player
				if (!player1.getName().compare(output)) { this->CURRENT_PLAYER = player1; }
				else{ this->CURRENT_PLAYER = player2; }
				break;
			}
			counter++;

		}
	}
	myReadFile.close();
	/*
	cout<<"PLAYER1"<<endl;
	cout<<"name="<<player1.getName()<<endl;
	cout<<"wincount="<<player1.getWinCount()<<endl;
	cout<<"cards"<<endl<<"---------------------------"<<endl;
	int* temp = player1.getCards();
	for(int h=0;h<5;h++){
	cout<<temp[h]<<endl;
	}

	cout<<"PLAYER2"<<endl<<player2.getName()<<endl;
	cout<<player2.getWinCount()<<endl;
	int* temp1 = player2.getCards();
	cout<<"cards"<<endl<<"---------------------------"<<endl;
	for(int h=0;h<5;h++){
	cout<<temp1[h]<<endl;
	}

	*/
	cout << "LOADING GAME......" << endl << endl;
}
/* -----------------------------------------------------------------------------
FUNCTION:         saveToFile(string filename)
DESCRIPTION:        saves game to file
----------------------------------------------------------------------------- */
void Cardgame::saveToFile(string filename){
	/*
	std::stringstream ss;
	ss << "card_"<<time(NULL)<<".txtT
	std::string filename = ss.str();
	*/
	;
	ofstream gameFile;
	gameFile.open(filename);
	gameFile << player1.getName() << "\n"; //<< "PLAYER1:"
	gameFile << player2.getName() << "\n"; //<< "PLAYER2:"
	gameFile << player1.getWinCount() << "\n"; //<< "SCORE_PLAYER1:"
	gameFile << player2.getWinCount() << "\n"; //<< "SCORE_PLAYER2:"
	gameFile << CURRENT_ROUND << "\n"; //<< "CURRENT_ROUND:"
	gameFile << MULTIPLAYER << "\n"; //<< "PLAY_AGAINST_HUMAN:"

	string _cards = "";
	std::string result;
	for (int i = 0; i<4; i++){
		for (int j = 0; j<13; j++){
			std::stringstream sstm;
			sstm << i << "_" << j << "=" << cards[i][j] << ",";
			result = sstm.str();
			_cards = _cards + result;
		}
	}

	string _player1card = "";
	int* card5_player1 = player1.getCards();
	int* card5_player2 = player2.getCards();

	for (int i = 0; i<5; i++){
		std::stringstream sstm;
		sstm << card5_player1[i] << "_";
		result = sstm.str();
		_player1card = _player1card + result;
	}

	string _player2card = "";
	for (int i = 0; i<5; i++){
		std::stringstream sstm;
		sstm << card5_player2[i] << "_";
		result = sstm.str();
		_player2card = _player2card + result;
	}

	gameFile << _cards << "\n"; //<< "CARDS:"
	gameFile << _player1card << "\n"; //<< "PLAYER1_CARDS:"
	gameFile << _player2card << "\n";//<< "PLAYER2_CARDS:"
	gameFile << CURRENT_PLAYER.getName() << "\n"; //<< "CURRENT_PLAYER:"
	gameFile.close();
}

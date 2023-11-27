
#define DECK_SIZE 108


#include <iostream> // std:: cout
#include <cstdlib> // std::rand, std::srand
using namespace std;
#ifndef _CARD_H_
#define _CARD_H_

#include <ostream>


enum COLOR { wild, red, green, blue, yellow };
/**
 * Represents a card in a deck
 */
class card
{
public:
	int number; // 0-9 numbers, +2, skip, reverse, all color, +4 (all color) 
	COLOR color; // 5 colors: red, green, blue, yellow, and no color 

	/**
	 * Equality operator.
	 * @param other Other card to check equality with. (can be put as next card)
	 */
	bool operator==(card const& other) const;

	/**
	 * Inequality operator.
	 * @param other Other card to check inequality with.
	 */
	bool operator!=(card const& other) const;


	card();

	card(int num, COLOR col);
};

/**
 * Stream operator that allows a card to be written to standard streams
 * (like cout).
 *
 * @param out Stream to write to.
 * @param temp_card to write to the stream.
 */
std::ostream& operator<<(std::ostream& out, card const& temp_card);


#endif // _CARD_H_



card::card() : number(0), color(wild)
{

}

card::card(int num, COLOR col) : number(num), color(col)
{

}

bool card::operator==(card const& other) const
{
	return number == other.number || color == other.color || color == wild || other.color == wild;

}


bool card::operator!=(card const& other) const
{
	return !(*this == other);
}


std::ostream& operator<<(std::ostream& out, card const& temp_card)
{
	out << "Number:";
	// << (int) temp_card.number << " Color: "; 
	switch (temp_card.number)
	{
	case 10: out << "DRAW-2"; break;
	case 11: out << "SKIP"; break;
	case 12: out << "REVERSE"; break;
	case 13: out << "WILD"; break;
	case 14: out << "DRAW-4-WILD"; break;
	default: out << (int)temp_card.number; break;
	}

	out << "   Color:";
	switch (temp_card.color)
	{
	case wild: out << "wild";  break;
	case red: out << "red";  break;
	case green: out << "green";  break;
	case blue: out << "blue";  break;
	case yellow: out << "yellow";  break;
	default: out << "N/A"; break;
	}
	return out;
}






 /*
 deck will contain class cards

 public members will include
 shuffle of cards
 drawing of cards (+1, +2, +4)
 - will use queue to pop out
 - check if deck has run out
 - if ran out ( reshuffle entire deck)

 private members :
  the deck of cards
  a queue

 */

 /* Game UNO - wikipedia
 deck consists of 108 cards
	 25 of each color ( red, green, blue, and yellow)
	 each color having two of each rank except zero
	 zero to nine
	 "Skip"
	 "Draw Two"
	 "Reverse "
	 "Wild "
	 "Wild Draw Four"

 */


 /*
 zero - 4 cards (RGBY)
 one till nine - 4 cards (RGBY) & 4 cards (RGBY)
 "Skip" -  4 cards (RGBY) & 4 cards (RGBY)
 "Draw Two" -  4 cards (RGBY) & 4 cards (RGBY)
 "Reverse " -  4 cards (RGBY) & 4 cards (RGBY)
 "Wild " -  4 cards (RGBY)
 "Wild Draw Four" -  4 cards (RGBY)

 */


#ifndef DECK_H
#define DECK_H

#include "card.h"
class deck : public card {
public:
	deck();
	deck(const deck& other);
	const deck& operator= (const deck& other);
	~deck();
	void shuffle();
	card draw();
	void create();
	int add_card(card temp_card);
	void quick_shuffle();
	void print_deck();
	int get_size();

private:
	card* ptr_deck;
	int size;
	void clear();
	void copy(const deck& other);
};

/**
 * Stream operator that allows a deck to be written to standard streams
 * (like cout).
 *
 * @param out Stream to write to.
 * @param temp_deck to write to the stream.
 */
std::ostream& operator<<(std::ostream& out, deck const& temp_deck);

#endif 




 /* Game UNO - wikipedia
 deck consists of 108 cards
	 25 of each color ( red, green, blue, and yellow)
	 each color having two of each rank except zero
	 zero to nine
	 "Skip"
	 "Draw Two"
	 "Reverse "
	 "Wild "
	 "Wild Draw Four"

 */


 /*
 zero - 4 cards (RGBY)
 one till nine - 4 cards (RGBY) & 4 cards (RGBY)
 ten "Skip" -  4 cards (RGBY) & 4 cards (RGBY)
 eleven "Draw Two" -  4 cards (RGBY) & 4 cards (RGBY)
 twelve "Reverse " -  4 cards (RGBY) & 4 cards (RGBY)
 thirteen "Wild " -  4 cards (RGBY)
 fourteen "Wild Draw Four" -  4 cards (RGBY)


 01234 =  wild + RGBY
 zero = wild
 one = red
 two = green
 three = blue
 four = yellow

 */




deck::deck()
{
	ptr_deck = new card[DECK_SIZE];
	size = 0;


}

void deck::create()
{
	int num = 0;


	// card rank 0
	for (int col = 1; col <= 4; col++)
	{
		ptr_deck[size].number = num;
		ptr_deck[size].color = static_cast<COLOR>(col);
		size++;
	}

	// card rank 1 till 9 , "draw-two", "skip", "reverse"
	for (num = 1; num <= 12; num++)
	{
		for (int x = 0; x < 2; x++)
		{
			for (int col = 1; col <= 4; col++)
			{
				ptr_deck[size].number = num;
				ptr_deck[size].color = static_cast<COLOR>(col);
				size++;
			}
		}

	}

	// card "wild", "wild-draw-four"
	for (num = 13; num <= 14; num++)
	{
		for (int x = 0; x < 4; x++)
		{
			ptr_deck[size].number = num;
			ptr_deck[size].color = wild;
			size++;
		}
	}


}

deck::deck(const deck& other)
{
	copy(other);
}


const deck& deck::operator= (const deck& other)
{
	if (this != &other)
	{
		clear();
		copy(other);
	}
	return *this;
}



deck::~deck()
{
	clear();
}




void deck::shuffle()
{
	/* Own method */
	/* rand whether to swap or not  ( greater than 50% swap)*/
	/* rand on which position to swap (rand from 0 to 107 inclusive)*/

	/*Researched method = GeeksforGeeks.org */
	/* O(n^2) shuffle : simple method */
	/* create temp array which is a copy of original */
	/* copy randomly selected element in temp to arr[0] */
	/* repeat the process */
	/* time complexity of this solution will be O(n^2)  */


	// create a temp deck 
	card* temp_deck = new card[size];
	for (int i = 0; i < size; i++)
	{
		temp_deck[i] = ptr_deck[i];
	}


	int temp_size = size;
	int temp_pos;
	int pos;
	for (int i = 0; i < size; i++)
	{
		// randomly find a position in temp_deck
		srand(time(NULL)); // change the seed , so randomized number is different each time
		pos = rand() % temp_size;
		//assign random element to deck[i]
		ptr_deck[i] = temp_deck[pos];

		// removing element from temp_deck (O(n) to shift) 
		temp_size--;
		for (temp_pos = pos; temp_pos < temp_size; temp_pos++)
		{
			temp_deck[temp_pos] = temp_deck[temp_pos + 1];
		}
	}

	delete[] temp_deck;



}
card deck::draw()
{
	if (size <= 0)
	{
		// do this inside gameplay
		//recreate 
		//must take into account cards in player's hands 
		return card();
	}
	card temp_card = ptr_deck[size - 1];
	size--;
	return temp_card;
}


int deck::add_card(card temp_card)
{
	// O(1) insert 
	if (size < DECK_SIZE)
	{
		ptr_deck[size] = temp_card;
		size++;
		return 0;
	}
	else
		return -1;
}


void deck::quick_shuffle()
{
	/* O(n) shuffle : fisher -yates shuffle algorithm (GeeksforGreeks.org)
		given rand() generates a random number in O(1)
		start from last element
		swap it with randomly selected from whole array including last
		now consider array from 0 to n-2(size reduced by 1 )
		repeat the process until we hit first element
	*/
	int pos;
	int temp_size = size - 1;
	card temp_card;
	while (temp_size > 0)
	{
		//generate random
		srand(time(NULL)); // change the seed , so randomized number is different each time
		pos = rand() % temp_size;
		// swap elements 
		temp_card = ptr_deck[temp_size];
		ptr_deck[temp_size] = ptr_deck[pos];
		ptr_deck[pos] = temp_card;
		// reduce size by 1 
		temp_size--;
	}

}



void deck::print_deck()
{
	for (int i = 0; i < size; i++)
	{
		cout << i << ": " << ptr_deck[i] << endl;
	}
}

void deck::copy(const deck& other)
{
	size = other.size;
	ptr_deck = new card[size];
	for (int i = 0; i < size; i++)
	{
		ptr_deck[i] = other.ptr_deck[i];
	}
}


void deck::clear()
{
	delete[]ptr_deck;
	ptr_deck = NULL;
	size = 0;
}


int deck::get_size()
{
	return size;
}



 /* class player

 public :
	 play cards to center
	 draw card
	 pass turn

	 show amount of cards left
	 show cards in hand (for playing to center)


 private:
	 cards on the hand ( limit to the half the deck of cards)
	 an array

 */
#ifndef PLAYER_H
#define PLAYER_H

#include "card.h"
class player
{
public:
	player();
	player(const player& other);
	const player& operator= (const player& other);
	~player();
	void hand_add(card temp);
	card hand_remove(int pos);
	void uno();
	void print() const;
	int get_size() const;
	card peek(int pos) const;
private:
	class card_elem
	{
	public:
		card_elem()
		{
			next = NULL;
		}
		card data;
		card_elem* next;
	};


	card_elem* head;
	int size;
	void copy(const player& other);
	void clear();


};

#endif 




player::player()
{
	head = NULL;
	size = 0;
}


player::player(const player& other)
{
	copy(other);
}


const player& player::operator= (const player& other)
{
	if (this != &other)
	{
		clear();
		copy(other);
	}

	return *this;

}


player::~player()
{
	clear();
}


void player::hand_add(card temp_card)
{
	//insert at the front of the linked list

	//create new code and assign data to it 
	card_elem* temp_ptr;
	temp_ptr = new card_elem();
	temp_ptr->data = temp_card;
	//link the node to the original list
	temp_ptr->next = head;
	//change the head to point to new element
	head = temp_ptr;
	//increment size
	size++;

}

card player::hand_remove(int pos)
{
	// error checking 
	if (pos < 0 || pos >= size)
	{
		return card();
	}

	//O(n) remove (b/c of O(n) to find

	card_elem* prev_ptr = head;
	card_elem* target = prev_ptr->next;
	card temp_card;
	int temp_pos = pos;

	// delete at front (case without previous ) 
	if (pos == 0)
	{
		//save data to return
		temp_card = head->data;
		// move head to the next one over
		head = head->next;
		// delete target element
		delete prev_ptr;
		//decrement size
		size--;
		return temp_card;
	}
	//find previous element 
	while (temp_pos > 1)
	{
		prev_ptr = prev_ptr->next;
		target = prev_ptr->next;
		temp_pos--;

	}
	//connect previous element to next element 
	prev_ptr->next = target->next;
	//save data into temp_card
	temp_card = target->data;
	//delete the target element 
	delete target;
	//decrement size
	size--;
	// return the target element 
	return temp_card;

}



void player::uno()
{

}

void player::print() const
{
	int temp_size = size;

	int i = 0;
	card_elem* temp_ptr = head;
	while (temp_size > 0)
	{
		cout << i << ":  " << temp_ptr->data << endl;
		temp_ptr = temp_ptr->next;
		i++;
		temp_size--;
	}

}



void player::copy(const player& other)
{
	size = other.size;

	//create the head of target player   
	if (size > 0)
	{
		head = new card_elem();
		//fill head with data	
		head->data = other.head->data;
	}
	else
	{
		head = NULL;
		return;
	}

	//other_ptr to traverse the other list
	card_elem* other_ptr = other.head->next;
	//create a temp_ptr to create the rest of linked list
	card_elem* temp_ptr;
	//create a previous ptr to point next to correct one
	card_elem* prev_ptr = head;
	for (int i = 1; i < size; i++)
	{
		// create new elem
		temp_ptr = new card_elem();
		//link the previous to current
		prev_ptr->next = temp_ptr;
		// fill it with data
		temp_ptr->data = other_ptr->data;
		// move to next one in the list
		prev_ptr = temp_ptr;
		temp_ptr = NULL;
		other_ptr = other_ptr->next;
	}

}

void player::clear()
{
	card_elem* temp_ptr = head;
	card_elem* next_ptr;
	while (size > 0)
	{
		next_ptr = temp_ptr->next;
		delete temp_ptr;
		temp_ptr = next_ptr;
		size--;
	}
	head = NULL;
}

int player::get_size() const
{
	return size;
}


//could have fast run time if returned a card and position in list
// position in list can be used be hand_remove to remove the element
card player::peek(int pos) const
{
	int temp_pos = pos;
	card_elem* temp_elem = head;
	while (temp_pos > 0)
	{
		temp_elem = temp_elem->next;
		temp_pos--;
	}

	return temp_elem->data;

}





card chooseBotCard(player& bot, card& played_card) {
	// Get the bot's hand size
	int size = bot.get_size();

	// Prioritize playing cards that match the current color over matching numbers
	for (int i = 0; i < size; ++i) {
		card temp = bot.peek(i);
		if (temp.color == played_card.color && temp.number != played_card.number) {
			return bot.hand_remove(i);
		}
	}

	// Always play special cards first
	for (int i = 0; i < size; ++i) {
		card temp = bot.peek(i);
		if (temp.number >= 10) {
			return bot.hand_remove(i);
		}
	}

	// If no match found, play any card that matches the color
	for (int i = 0; i < size; ++i) {
		card temp = bot.peek(i);
		if (temp.color == played_card.color) {
			return bot.hand_remove(i);
		}
	}

	// If no match found, play any card
	return bot.hand_remove(0);
}


bool canPlayCard(player& curr_player, card& played_card) {
	int size = curr_player.get_size();

	for (int i = 0; i < size; ++i) {
		card temp = curr_player.peek(i);
		if (temp == played_card) {
			return true;
		}
	}

	return false;
}

// Function to handle Draw 1 and Skip rule
void drawOneAndSkip(player& curr_player, deck& main_deck, card& played_card, bool& force_draw_bool, deck& temp_deck) {
	card draw_temp = main_deck.draw();
	cout << "DRAWN CARD: " << draw_temp << endl;

	if (draw_temp == played_card && draw_temp.color != wild) {
		int play_draw_flag = 0;
		while (play_draw_flag == 0) {
			string temp_play;
			cout << "Do you want to play the drawn card [y/n] : ";
			cin >> temp_play;
			if (temp_play == "y") {
				/*played_card = draw_temp;
				temp_deck.add_card(draw_temp);
				if (played_card.number >= 10 && played_card.number <= 14) {
					force_draw_bool = true;
				}
				play_draw_flag = 1;*/
				undoLastMove(played_card);
				play_draw_flag = 1;
			}
			if (temp_play == "n") {
				curr_player.hand_add(draw_temp);
				play_draw_flag = 1;
			}
		}
	}
	else {
		curr_player.hand_add(draw_temp);
	}
}

struct GameStateSnapshot {
	card played_card;
	// Add other members to represent the state of the game
	// For example, vector<player>, deck, etc.
};

vector<GameStateSnapshot> gameSnapshots;

void logGameEvent(const card& played_card) {
	GameStateSnapshot snapshot;
	snapshot.played_card = played_card;
	gameSnapshots.push_back(snapshot);
}

void undoLastMove(card& played_card) {
	if (!gameSnapshots.empty()) {
		GameStateSnapshot previousSnapshot = gameSnapshots.back();
		played_card = previousSnapshot.played_card;
		gameSnapshots.pop_back();
	}
}

void reviewPastMoves() {
	for (size_t i = 0; i < gameSnapshots.size(); ++i) {
		const auto& snapshot = gameSnapshots[i];
		cout << "Move " << i + 1 << ": Played Card - " << snapshot.played_card << endl;
	}
}

class PlayerProfile {
private:
	string playerName;
	int gamesWon;

public:
	// Constructor
	PlayerProfile(const string& name) : playerName(name), gamesWon(0) {}

	// Accessors
	string getName() const { return playerName; }
	int getGamesWon() const { return gamesWon; }

	// Increment games won
	void winGame() { gamesWon++; }

	// Save profile to a file
	void saveProfile() {
		ofstream outFile(playerName + "_profile.txt");
		outFile << playerName << " " << gamesWon;
		outFile.close();
	}

	// Load profile from a file
	void loadProfile() {
		ifstream inFile(playerName + "_profile.txt");
		if (inFile.is_open()) {
			inFile >> playerName >> gamesWon;
			inFile.close();
		}
	}
};


class Scoreboard {
private:
	vector<PlayerProfile> playerProfiles;

public:
	// Add a player to the scoreboard
	void addPlayer(const string& playerName) {
		PlayerProfile newPlayer(playerName);
		newPlayer.loadProfile();  // Load existing profile if available
		playerProfiles.push_back(newPlayer);
	}

	// Update scoreboard after a game is won
	void updateScoreboard(const string& playerName) {
		for (auto& profile : playerProfiles) {
			if (profile.getName() == playerName) {
				profile.winGame();
				profile.saveProfile();
				break;
			}
		}
	}

	// Display the scoreboard
	void displayScoreboard() const {
		cout << "Scoreboard:\n";
		for (const auto& profile : playerProfiles) {
			cout << profile.getName() << " - Games Won: " << profile.getGamesWon() << endl;
		}
	}
};

void display_intro(string filename)
{
	string line;
	fstream myfile;
	myfile.open(filename.c_str());
	/*c_str() is to fix the problem of C++ type mismatch of
	‘std::string {aka std::basic_string<char>}’ and ‘const char*’
	http://stackoverflow.com/questions/17750699/c-displaying-a-text-file-echo-a-text-file
	*/
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			cout << line << endl;
		}
		myfile.close();
	}
	else
	{
		cout << "error unable to open file " << endl;
	}

}

void confirm_turn(int x)
{
	/* http://www.cplusplus.com/forum/articles/7312/ */
	cout << "Confirm Player " << x << " by typing '" << x << "' and pressing enter: ";
	int temp = -1;  // Initialize temp to a default value
	while (temp != x)
	{
		cin >> temp;
	}
}


/* http://stackoverflow.com/questions/5938052/assigning-values-to-enumerated-types*/
COLOR FromString(const string& str)
{
	if (str == "red")
		return red;
	else if (str == "green")
		return green;
	else if (str == "blue")
		return blue;
	else if (str == "yellow")
		return yellow;
	else
		return wild;
}
// logging
void logGameEvent(const card& played_card) {
	GameStateSnapshot snapshot;
	snapshot.played_card = played_card;
	gameSnapshots.push_back(snapshot);
}

// undo last move
void undoLastMove(card& played_card) {
	if (!gameSnapshots.empty()) {
		GameStateSnapshot previousSnapshot = gameSnapshots.back();
		played_card = previousSnapshot.played_card;
		gameSnapshots.pop_back();
	}
}

void profile()
{
	Scoreboard scoreboard;

	// Get the number of players from the user
	int amount_players;
	int flag = 0;
	while (flag == 0)
	{
		cout << "Please enter the number of players: ";
		cin >> amount_players;
		if (amount_players >= 2 && amount_players <= 5)
		{
			cout << amount_players << " players entering the game.... " << endl;
			flag = 1;
			break;
		}
		else
		{
			cout << "Invalid number of players" << endl;
		}
	}

	// Create player profiles and add players to the scoreboard
	vector<PlayerProfile> playerProfiles;
	for (int i = 1; i <= amount_players; ++i)
	{
		string playerName;
		cout << "Enter the name of Player " << i << ": ";
		cin >> playerName;
		playerProfiles.push_back(PlayerProfile(playerName));
		scoreboard.addPlayer(playerName);
	}

}


/* this cpp file will be the main function for the game
   -asking players to play cards into the a middle temp field
   -ask player for a color if wild card is played
   -distributing cards
   -show the amount of cards left for each player

*/

// NOTE : must clear screen before next player plays their cards

/* will create the game by asking
    - amount of players
    - amount of AI players
*/


// NOTE
//In a two-player game, the Reverse has the same effect as a Skip, allowing the player who discards it to take another turn

/* turns
 (turn++)%amount_players
on player zero's turn reset back to zero

*/

/* ACTION CARDS
Draw-2 : next player draws 2 and loses a turn
SKIP: next player loses turn (+2 instead of plus one)
REVERSE: switch the direction (from ++ to -- ) , in two player same as skip
WILD: choose a color
Draw-3 WILD: choose a color, next player draws 4 and loses a turn
*/

#include "card.h"
#include "deck.h"
#include "player.h"
#include <iostream>
#include <fstream> // for opening and closing files
#include <string> 
#include <cstdlib> // std::system() ; std::rand()
#include <limits> // std::numeric_limits
#include <algorithm>  // for std::find
#include <vector>
#include <windows.h>
#include <ctime>    // for time

using namespace std;

#define TEXTFILE "intro.txt"
#define PRINT_ALL_PLAYERS 0
#define TEMP_DECK 1
#define TURN 2
#define TEST -1

/* function from http://www.cplusplus.com/doc/tutorial/files/ */

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





int main()
{
    // clear screen
    system("cls"); // for Windows

    // Create a scoreboard
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

    // Other game components
    deck main_deck;
    main_deck.create();
    main_deck.quick_shuffle();

    player* play_array;
    play_array = new player[amount_players];


    for (int i = 0; i < amount_players; i++)
    {
        for (int k = 0; k < 7; k++)
        {
            card temp_card;
            temp_card = main_deck.draw();
            play_array[i].hand_add(temp_card);
        }
    }

    deck temp_deck;
    card played_card;
    card temp_card;
    int card_flag = 0;

    while (card_flag == 0)
    {
        temp_card = main_deck.draw();
        if (temp_card.color != wild)
        {
            card_flag = 1;
            played_card = temp_card;
        }
        else
        {
            temp_deck.add_card(temp_card);
        }
    }

    // Randomize who starts first
    srand(time(NULL));
    int turn = rand() % amount_players;
    cout << "Player " << playerProfiles[turn].getName() << " is randomly selected to play first" << endl;
    confirm_turn(turn);

    bool force_draw_bool = false;
    int turn_flag = 1;
    int win = 0;

    // Game logging
    vector<GameStateSnapshot> gameSnapshots;

    while (win == 0)
    {
        system("cls"); // for Windows
        player* curr_player = &play_array[turn % amount_players];

        cout << "Player " << playerProfiles[turn % amount_players].getName() << endl;

        if (force_draw_bool)
        {
            drawOneAndSkip(*curr_player, main_deck, played_card, force_draw_bool, temp_deck);
        }

        cout << "Cards remaining for each player: " << endl;
        for (int i = 0; i < amount_players; i++)
        {
            cout << "Player " << playerProfiles[i].getName() << ": " << play_array[i].get_size() << "   ";
        }
        cout << endl;

        cout << "Played Card: " << played_card << endl;
        cout << "Player " << playerProfiles[turn % amount_players].getName() << endl;

        curr_player->print();
        reviewPastMoves(); // Display past moves


        int check_flag = 0;
        int index;
        int size = curr_player->get_size();

        while (check_flag == 0)
        {
            cout << "Which card do you want to play? " << endl;
            cout << "If you want to draw a card, please enter '-1' " << endl;
            cout << "Type the index of the card and press enter: ";
            cin >> index;

            if (index == -1)
            {
                drawOneAndSkip(*curr_player, main_deck, played_card, force_draw_bool, temp_deck);
                check_flag = 1;
            }
            else if (index >= 0 && index < size)
            {
                card temp = curr_player->peek(index);
                if (temp == played_card)
                {
                    curr_player->hand_remove(index);
                    temp_deck.add_card(temp);
                    played_card = temp;

                    if (played_card.color == wild)
                    {
                        cout << "Choose a color for the wild card (red, green, blue, yellow): ";
                        string chosen_color;
                        cin >> chosen_color;
                        played_card.color = FromString(chosen_color);
                        force_draw_bool = true;
                    }

                    check_flag = 1;
                }
                else
                {

                    cout << "Card cannot be played." << endl;
                }
            }
            else
            {
                cout << "Invalid index." << endl;
            }
            logGameEvent(played_card);

        }

        if (curr_player->get_size() == 0)
        {
            win = 1;
            cout << "Player " << playerProfiles[turn % amount_players].getName() << " has won the game." << endl;
            scoreboard.updateScoreboard(playerProfiles[turn % amount_players].getName());
            break;
        }
        // Display the scoreboard after each move

        if (played_card.number == 11 && force_draw_bool == true)
        {
            turn += (turn_flag == 1) ? 2 : -2;
        }
        else if (played_card.number == 12 && force_draw_bool == true)
        {
            if (amount_players == 2)
            {
                turn += 2;
            }
            else
            {
                turn_flag = -turn_flag;
                turn += turn_flag;
            }
        }
        else
        {
            turn += turn_flag;
        }

        system("cls"); // for Windows

        cout << "Cards remaining for each player: " << endl;
        for (int i = 0; i < amount_players; i++)
        {
            cout << "Player " << playerProfiles[i].getName() << ": " << play_array[i].get_size() << "   ";
        }
        cout << endl;

        cout << "Played Card: " << played_card << endl;
        confirm_turn(turn % amount_players);

        if (main_deck.get_size() < 10)
        {
            while (main_deck.get_size() > 0)
            {
                temp_deck.add_card(main_deck.draw());
            }

            main_deck = temp_deck;
            main_deck.quick_shuffle();

            temp_deck = deck();
        }

    }

    // Display the final scoreboard
    scoreboard.displayScoreboard();

    delete[] play_array; // free the allocated memory for the player array

    return 0;
}


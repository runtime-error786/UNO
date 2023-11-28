#define CATCH_CONFIG_MAIN
#include "catch.hpp"
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
TEST_CASE("Card Equality", "[card]") {
    // Test card equality
    card card1(5,red);
    card card2(5,red);
    REQUIRE(card1 == card2);

    // Add more card-related tests
}

TEST_CASE("Deck Operations", "[deck]") {
    // Test deck creation and shuffling
    deck testDeck;
    testDeck.create();
    REQUIRE(testDeck.get_size() == 108);
    testDeck.quick_shuffle();
    // Add more deck-related tests
}

TEST_CASE("String to Color Conversion", "[utility]") {
    // Test converting strings to color enumeration
    REQUIRE(FromString("red") == red);
    REQUIRE(FromString("green") == green);
    // Add more utility tests
}


TEST_CASE("Player Initialization", "[player]") {
    // Test the initialization of player
    player testPlayer;

    // Check that the player starts with an empty hand
    REQUIRE(testPlayer.get_size() == 0);
}

TEST_CASE("Player Add Card", "[player]") {
    // Test adding a card to the player's hand
    player testPlayer;
    card testCard(5, red);

    // Add a card to the player's hand
    testPlayer.hand_add(testCard);

    // Check that the player's hand size is now 1
    REQUIRE(testPlayer.get_size() == 1);

    // Check that the player's hand contains the added card
    REQUIRE(testPlayer.peek(0) == testCard);
}

TEST_CASE("Player Remove Card", "[player]") {
    // Test removing a card from the player's hand
    player testPlayer;
    card testCard(5, red);

    // Add a card to the player's hand
    testPlayer.hand_add(testCard);

    // Remove the card from the player's hand
    card removedCard = testPlayer.hand_remove(0);

    // Check that the removed card is the same as the added card
    REQUIRE(removedCard == testCard);

    // Check that the player's hand is now empty
    REQUIRE(testPlayer.get_size() == 0);
}

TEST_CASE("Player UNO", "[player]") {
    // Test the UNO function of the player
    player testPlayer;
    card testCard(5, red);

    // Add multiple cards to the player's hand
    for (int i = 0; i < 5; ++i) {
        testPlayer.hand_add(testCard);
    }

    // Check that the player's hand size is 1 or less after calling UNO
    REQUIRE(testPlayer.get_size() == 5);
}


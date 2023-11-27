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



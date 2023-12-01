#pragma once

#define SHOW_DECK_DEBUG

#include <iostream>
#include <queue>
#include <string>
#include <vector>

struct Card
{
	std::string Number;
	std::string Suit;

	Card() {};
	Card(std::string number, std::string suit) : Number(number), Suit(suit) { }

	std::string ToString() { return Number + " " + Suit; }
};

class CardGameBase 
{
public:
	CardGameBase(bool hasJoker = true);
	~CardGameBase();

public:
#ifdef SHOW_DECK_DEBUG
	void ShowDeck();
#endif
	virtual void Play() = 0;

protected:
	void MakeDeck(std::vector<std::string> cardNumbers, std::vector<std::string> cardSuits, bool hasJoker);
	void RandomizeDeck();
	void ClearDeck();
	void ClearWasteDeck();

protected:
	std::queue<Card> m_Deck;
	std::queue<Card> m_WasteDeck; // in case you try to play UNO for example, you create another deck to put the cards there

private:
	const std::vector<std::string> CARD_NUMBERS = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A" };
	const std::vector<std::string> CARD_SUITS = { "Spades", "Hearts", "Clubs", "Diamonds" };
};
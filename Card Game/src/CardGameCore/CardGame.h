#pragma once

#define DEBUG_MODE

#include <iostream>
#include <stack>
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

class CardGame 
{
public:
	CardGame(bool shuffle);
	~CardGame();

public:
#ifdef DEBUG_MODE
	void ShowDeck();
	void ShowCard(int index);
#endif
	virtual void Play() = 0;

protected:
	void MakeDeck(std::vector<std::string> cardNumbers, std::vector<std::string> cardSuits);
	void ShuffleDeck();
	void ClearDeck();
	void ClearWasteDeck();
	std::vector<Card> DealHand(std::stack<Card>& deck, std::size_t handSize);
	Card DrawCard(std::stack<Card>& deck);

protected:
	std::stack<Card> m_Deck;

	// in case you try to play UNO for example, you create another deck to put the cards here
	std::stack<Card> m_WasteDeck;

private:
	const std::vector<std::string> CARD_NUMBERS = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A" };
	const std::vector<std::string> CARD_SUITS = { "Spades", "Hearts", "Clubs", "Diamonds" };
};
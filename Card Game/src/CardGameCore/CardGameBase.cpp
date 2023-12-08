#include "CardGameBase.h"

using std::string;
using std::queue;
using std::vector;
using std::cout;

CardGameBase::CardGameBase(bool hasJoker)
{
	MakeDeck(CARD_NUMBERS, CARD_SUITS, hasJoker);
	RandomizeDeck();
}

CardGameBase::~CardGameBase() 
{
	ClearDeck();
	ClearWasteDeck();
}

void CardGameBase::MakeDeck(vector<string> cardNumbers, vector<string> cardSuits, bool hasJoker)
{
	while (!m_Deck.empty()) 
	{
		m_Deck.pop();
	}

	for (int i = 0; i < cardSuits.size(); i++)
	{
		for (int j = 0; j < cardNumbers.size(); j++)
		{
			Card card(cardNumbers[j], cardSuits[i]);
			m_Deck.push(card);
		}
	}

	if (hasJoker)
	{
		Card joker("Joker", "");
		m_Deck.push(joker);
		m_Deck.push(joker);
	}
}

void CardGameBase::ShowDeck() 
{
	queue<Card> deck = m_Deck;
	while (!deck.empty())
	{
		cout << deck.front().ToString() << "\n";
		deck.pop();
	}
}

void CardGameBase::RandomizeDeck() 
{
	size_t size = m_Deck.size();
	vector<Card> random(size);

	for (int i = 0; i < size; i++)
	{
		random[i] = m_Deck.front();
		m_Deck.pop();
	}

	while (!random.empty())
	{
		srand(time(0));
		int index = rand() % random.size();
		m_Deck.push(random[index]);
		random.erase(random.begin() + index);
	}
}

void CardGameBase::ClearDeck() 
{
	while(!m_Deck.empty()) m_Deck.pop();
}

void CardGameBase::ClearWasteDeck() 
{
	while (!m_WasteDeck.empty()) m_WasteDeck.pop();
}

vector<Card> CardGameBase::DealHand(queue<Card>& deck, size_t handSize)
{
	vector<Card> hand(handSize);

	for (int i = 0; i < handSize; i++)
	{
		hand[i] = deck.front();
		deck.pop();
	}

	return hand;
}

Card CardGameBase::DrawCard(queue<Card>& deck)
{
	return DealHand(deck, 1)[0];
}
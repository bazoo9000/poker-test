#include "CardGame.h"

using std::string;
using std::stack;
using std::vector;
using std::cout;

CardGame::CardGame(bool shuffle = false)
{
	MakeDeck(CARD_NUMBERS, CARD_SUITS);
	if(shuffle) ShuffleDeck();
}

CardGame::~CardGame() 
{
	ClearDeck();
	ClearWasteDeck();
}

void CardGame::MakeDeck(vector<string> cardNumbers, vector<string> cardSuits)
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
}

void CardGame::ShowDeck() 
{
	stack<Card> deck = m_Deck;
	while (!deck.empty())
	{
		cout << deck.top().ToString() << "\n";
		deck.pop();
	}
}

void CardGame::ShowCard(int index)
{
	stack<Card> deck = m_Deck;

	int cnt = 0;
	while (cnt < index && !deck.empty())
	{
		deck.pop();
		++cnt;
	}

	if (deck.empty())
	{
		cout << "Didn't find card\n";
		return;
	}

	cout << deck.top().ToString() << "\n";
}

void CardGame::ShuffleDeck() 
{
	size_t size = m_Deck.size();
	vector<Card> random(size);

	for (int i = 0; i < size; i++)
	{
		random[i] = m_Deck.top();
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

void CardGame::ClearDeck() 
{
	while(!m_Deck.empty()) m_Deck.pop();
}

void CardGame::ClearWasteDeck() 
{
	while (!m_WasteDeck.empty()) m_WasteDeck.pop();
}

vector<Card> CardGame::DealHand(stack<Card>& deck, size_t handSize)
{
	vector<Card> hand(handSize);

	for (int i = 0; i < handSize; i++)
	{
		hand[i] = deck.top();
		deck.pop();
	}

	return hand;
}

Card CardGame::DrawCard(stack<Card>& deck)
{
	return DealHand(deck, 1)[0];
}
#include "PokerGameBase.h"
#include <conio.h> 

using std::map;
using std::string;
using std::queue;
using std::vector;
using std::cout;

PokerGameBase::PokerGameBase() : CardGameBase(false)
{
	// nimic
}

PokerGameBase::~PokerGameBase()
{
	// nimic
}

void PokerGameBase::Play()
{
	// Begining
	cout << "Hello and welcome to Poker! Would you like to play?\n";
	cout << "1 for yes\n";
	cout << "0 for no\n";
	bool wantStart;
	std::cin >> wantStart;
	if (!wantStart)
	{
		system("cls");
		cout << "Goodbye!\n";
		return;
	}

	system("cls");

	while (true)
	{
		// Game starts here
		m_Hand = DealHand(m_Deck, 5);
		ShowHand();
		for (int i = 0; i < 5; i++)
		{
			bool wantChange;
			std::cin >> wantChange;
			if (wantChange)
			{
				m_Hand[i] = DrawCard(m_Deck);
			}
		}

		system("cls");
		ShowHand();

		WhatWinningHandIs(HandCheck());

		// Endgame
		cout << "\n\nGame is Over! Would you like to continue?\n";
		cout << "1 for yes\n";
		cout << "0 for no\n";
		bool wantRestart;
		std::cin >> wantRestart;
		if (!wantRestart)
		{
			system("cls");
			cout << "Goodbye!\n";
			return;
		}

		// Clear console
		system("cls");
	}
}

void PokerGameBase::ShowHand() 
{
	for (int i = 0; i < m_Hand.size(); i++)
	{
		cout << m_Hand[i].ToString() << "\n";
	}
}

PokerGameBase::PokerHand PokerGameBase::HandCheck()
{
	SortHand();

	// Pairs/Repeats Check
	short pairCount = 0;
	bool isTriple = false;
	short counter;
	for (int i = 0; i < m_Hand.size() - 1; i++)
	{
		counter = 1;
		for (int j = i + 1; j < m_Hand.size(); j++)
		{
			if (m_Hand[i].Number == m_Hand[j].Number) //(hand[i].c_str()[0] == hand[j].c_str()[0])
			{
				counter++;
				if (counter == 4)
				{
					// Justification: it's impossible to get any other hand if you get a Four of a kind and 
					//				  it's ranked high wich means it stops the function here so it doesnt
					//				  check the rest
					return PokerHand::FourOfKind;
				}
				else if (counter == 3)
				{
					isTriple = true;
				}
			}
		}

		if (counter == 2)
		{
			pairCount++;
		}
	}

	bool isStraight = IsStraight(m_Hand);
	bool isFlush = IsFlush(m_Hand);
	bool isRoyal = IsRoyal(m_Hand, isStraight, isFlush);

	if (isStraight && isFlush)
	{
		if (isRoyal)
		{
			return PokerHand::RoyalFlush;
		}
		return PokerHand::StraightFlush;
	}
	// Four of a kind is handled in the first for loop
	if (isTriple && pairCount == 1)
	{
		return PokerHand::FullHouse;
	}
	if (isFlush)
	{
		return PokerHand::Flush;
	}
	if (isStraight)
	{
		return PokerHand::Straight;
	}
	if (isTriple)
	{
		return PokerHand::ThreeOfKind;
	}
	if (pairCount == 2)
	{
		return PokerHand::TwoPair;
	}
	if (pairCount == 1)
	{
		return PokerHand::OnePair;
	}

	return PokerHand::HighCard;
}

void PokerGameBase::WhatWinningHandIs(PokerHand pokerHand) 
{
	switch (pokerHand)
	{
	case PokerHand::HighCard:		cout << "High Card";		break;
	case PokerHand::OnePair:		cout << "Pair";				break;
	case PokerHand::TwoPair:		cout << "Two Pair";			break;
	case PokerHand::ThreeOfKind:	cout << "Three Of a Kind";	break;
	case PokerHand::Straight:		cout << "Straight";			break;
	case PokerHand::Flush:			cout << "Flush";			break;
	case PokerHand::FullHouse:		cout << "Full House";		break;
	case PokerHand::FourOfKind:		cout << "Four Of a Kind";	break;
	case PokerHand::StraightFlush:	cout << "Straight Flush";	break;
	case PokerHand::RoyalFlush:		cout << "Royal Flush";		break;
	}
}

int PokerGameBase::CardNumberToInt(string cardNumber)
{
	if (cardNumber == "A")
	{
		return 14;
	}

	if (cardNumber == "K")
	{
		return 13;
	}

	if (cardNumber == "Q")
	{
		return 12;
	}

	if (cardNumber == "J")
	{
		return 11;
	}

	return std::stoi(cardNumber);
}
bool PokerGameBase::IsStraight(vector<Card> hand)
{
	Card c1 = hand[0];
	for (int i = 1; i < hand.size(); i++)
	{
		Card c2 = hand[i];
		if (CardNumberToInt(c2.Number) - CardNumberToInt(c1.Number) != 1)
		{
			return false;
		}
	}

	return true;
}
bool PokerGameBase::IsFlush(vector<Card> hand)
{
	Card c1 = hand[0];
	for (int i = 1; i < hand.size(); i++)
	{
		Card c2 = hand[i];
		if (c1.Suit != c2.Suit)
		{
			return false;
		}
	}

	return true;
}
bool PokerGameBase::IsRoyal(vector<Card> hand, bool isStraight, bool isFlush)
{
	if (!(isStraight && isFlush))
	{
		return false;
	}

	bool hasTen = false;
	bool hasAce = false;
	for (int i = 1; i < hand.size() && !(hasTen && hasAce); i++)
	{
		if (hand[i].Number == "10")
		{
			hasTen = true;
		}
		if (hand[i].Number == "A")
		{
			hasAce = true;
		}
	}

	return (hasTen && hasAce);
}

void PokerGameBase::SortHand() 
{
	map<int, vector<Card>> sorter;

	for (int i = 0; i < m_Hand.size(); i++)
	{
		int i_val = CardNumberToInt(m_Hand[i].Number);

		if (sorter.count(i_val) > 0)
		{
			sorter[i_val].push_back(m_Hand[i]);
		}
		else
		{
			sorter[i_val] = vector<Card>({ m_Hand[i] });
		}
	}

	int i = 0;
	for (map<int, vector<Card>>::iterator it = sorter.begin(); it != sorter.end(); it++)
	{
		for (auto card : it->second)
		{
			m_Hand[i] = card;
			i++;
		}
	}
}
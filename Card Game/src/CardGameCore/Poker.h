#pragma once

#include "CardGame.h"
#include <map>

class Poker : public CardGame
{
public:
	enum class PokerHand
	{
		HighCard = 0,							// Tier 0
		OnePair, TwoPair, ThreeOfKind,			// Tier 1
		Straight, Flush, FullHouse,				// Tier 2
		FourOfKind, StraightFlush, RoyalFlush	// Tier 3
	};

	Poker();
	Poker(bool shuffle);
	~Poker();

public:
	virtual void Play() override;

#ifdef DEBUG_MODE
public:
#else
private:
#endif
	void ShowHand();
	PokerHand HandCheck();
	void WhatWinningHandIs(PokerHand pokerHand);

private: // for HandCheck()
	int CardNumberToInt(std::string cardNumber);
	void SortHand();
	bool IsStraight(std::vector<Card> hand);
	bool IsFlush(std::vector<Card> hand);
	bool IsRoyal(std::vector<Card> hand, bool isStraight, bool isFlush);

private:
	std::vector<Card> m_Hand;
};
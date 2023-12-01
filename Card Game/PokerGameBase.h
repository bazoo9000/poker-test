#pragma once

#include "CardGameBase.h"
#include <map>

enum class PokerHand
{
	HighCard = 0,							// Tier 0
	OnePair, TwoPair, ThreeOfKind,			// Tier 1
	Straight, Flush, FullHouse,				// Tier 2
	FourOfKind, StraightFlush, RoyalFlush	// Tier 3
};

class PokerGameBase : public CardGameBase
{
public:
	PokerGameBase();
	~PokerGameBase();

public:
	virtual void Play() override;

private:
	std::vector<Card> DealHand(std::queue<Card>& deck, size_t handSize = 5);
	Card DrawCard(std::queue<Card>& deck);
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
#pragma once

#include "IScoreHandler.h"

class PokerScoreHandler : public IScoreHandler
{
public:
	virtual float GetTotalScore() override 
	{
		return m_TotalScore;
	}

private:
	float m_TotalScore = 0.0f;
};
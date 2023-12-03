#include "CardGameCore/PokerGameBase.h"

int main()
{
	PokerGameBase* game = new PokerGameBase();

	game->Play();

	delete game;

	return 0;
}
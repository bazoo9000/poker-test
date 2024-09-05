#include "CardGameCore/Poker.h"

int main()
{
	CardGame* game = new Poker(false);

	game->ShowCard(0);

	delete game;

	return 0;
}
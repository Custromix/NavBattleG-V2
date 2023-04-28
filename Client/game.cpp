#include "Framework.h"


Game::Game() :USER(0), COMPUTER(1), STARTED(1)
{
	state = 0;
	secondHitPlayed = false;
}

//Sur le client
bool Game::check(Board& board)
{
	if (board.getBoatInfo() == 13)
	{
		board.messageBox("LE JEU PEUT COMMENCER PRET ?");
		return true;
	}
	else if (board.getBoatInfo() > 13)
	{
		board.messageBox("PLACE CORRECTEMENT LE BATEAU");
	}
	else { board.messageBox("PLACE CHAQUE BATEAU SUR LA GRILLE"); }

	return false;
}

//Sur le serveur
void Game::start(sf::RenderWindow& win, Board& board, Boat& boat, computerBoard& cb)
{
	if (cb.getBoatInfo()) { board.messageBox(" DEFAITE DE L'ORDINATEUR"); }
	else if (!board.checkBoatOnGrid()) { board.messageBox("TU AS PERDU. VICTOIRE DE L'ORDINATEUR"); }

	else if (!cb.getBoatInfo() || board.checkBoatOnGrid()) {
		// USER PLAY ON COMPUTER GRID
		if (state == USER) {
			board.messageBox("TU PEUX ATTAQUER UN BATEAU");
			if (cb.gridEvent(win)) {
				// IF THE GAME IS STARTED SET STATUS TO FALSE AND BLOCK BOAT POSITION
				boat.setStatus(false);
				if (cb.returnHitInformation() && !secondHitPlayed) { state = USER; secondHitPlayed = true; }
				else { state = COMPUTER; secondHitPlayed = false; }
			}
		}
		else {
			// COMPUTER PLAY ON THE USER GRID
			if (cb.play(board)) { state = USER; }
			else {
				board.messageBox("L'ORDINATEUR A GAGNE IL REJOUE !"); cb.play(board);
				state = USER;
			}
			board.messageBox("L'ORDINATEUR JOUE");
		}
	}
}


#include "Framework.h"


Game::Game() :USER(0), COMPUTER(1), STARTED(1)
{
	state = 0;
	secondHitPlayed = false;
}

bool Game::check(Board& board)
{
	if (board.getBoatInfo() == 13)
	{
		board.messageBox("OK   THE   GAME    CAN    START.    READY    ???");
		return true;
	}
	else if (board.getBoatInfo() > 13)
	{
		board.messageBox("SET    THE    CORRECT    PLACE    OF    THE    BOAT");
	}
	else { board.messageBox("PLACE    EACH    BOATS    ON    THE    GRID"); }

	return false;
}


void Game::start(sf::RenderWindow& win, Board& board, Boat& boat, computerBoard& cb)
{
	if (cb.getBoatInfo()) { board.messageBox(" COMPUTER    LOOSE"); }
	else if (!board.checkBoatOnGrid()) { board.messageBox("YOU    LOOSE.    COMPUTER    WIN"); }

	else if (!cb.getBoatInfo() || board.checkBoatOnGrid()) {
		// USER PLAY ON COMPUTER GRID
		if (state == USER) {
			board.messageBox("YOU    CAN    PLAY    ON    THE    COMPUTER    GRID");
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
				board.messageBox("COMPUTER    WIN.    IT    PLAYS    AGAIN"); cb.play(board);
				state = USER;
			}
			board.messageBox("COMPUTER PLAYS");
		}
	}
}


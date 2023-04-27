
class Boat;
class computerBoard;

class Game
{
private:
	const int USER;
	const int COMPUTER;
	const int STARTED;
	char* status;
	int state;
	bool secondHitPlayed;
public:
	Game();
	bool check(Board&);
	void start(sf::RenderWindow&, Board&, Boat&, computerBoard&);
	const char* getStatus();
};


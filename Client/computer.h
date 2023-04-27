
class Boat;
class Board;

class computerBoard
{
private:
	const int TILESIZE;
	const int EMPTY;
	const int MISSED;
	const int FILLED;
	const int BUSY;
	const int HORIZONTAL;
	const int VERTICAL;
	const int SMALL_BOAT_SIZE;
	const int MEDIUM_BOAT_SIZE;
	const int BIG_BOAT_SIZE;
	const int COMPUTERGRID_OFFSET_X;
	const int COMPUTERGRID_OFFSET_Y;
	const int MAX_CASE;
	const int MAX_ROTATION;
	const int SENSOR_SIZE;
	int boat;
	int computerBoatOrientation;
	int computerStartPosition;
	int positionX;
	int positionY;
	int computerSquarePositionX;
	int computerSquarePositionY;
	int l;
	int r;
	int cx;
	int cy;
	int choiceX;
	int choiceY;
	bool touched;
	bool isPressed;
	std::vector<sf::FloatRect> computerGridSquare;
	std::array<std::array<int, 10>, 10> computerGridArray;
public:
	computerBoard();
	void setComputerGrid();
	void spawn();
	void spawnSmallBoats();
	void spawnMediumBoats();
	void spawnBigBoats();
	void readGridInfo(sf::RenderWindow&, Boat&);
	bool checkCase(const int&, const int&, const int&);
	void checkBoatLength(const int&, const int&, const int&);
	void fillGrid(const int&, const int&, const int&, const int&);
	void addSensorsToGrid();
	void addBoxToSquare(sf::RenderWindow&);
	bool gridEvent(sf::RenderWindow&);
	bool hitBoat(int&, const int&);
	bool returnHitInformation();
	bool getBoatInfo();
	void spawnChoice();
	bool play(Board&);
	void drawPlayedCase(sf::RenderWindow&, const int&, const int&);
};


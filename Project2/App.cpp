#include "Framework.h"

App::App()
{
	m_sysTime = timeGetTime();
}

App::~App()
{
}

void App::Init()
{
    //m_window = new RenderWindow(VideoMode(900, 600), "Bataille navale");
	win.create(sf::VideoMode(1024,610),"SFML GameDev");
	m_state = PLAY;
	CreateScene();
}

void App::PrintDebug(String textDebug)
{
    m_debugText.setFont(m_font);
    m_debugText.setString(textDebug);
    m_debugText.setPosition(800, 0);
    m_debugText.setCharacterSize(20);
    m_debugText.setFillColor(Color::White);
}

void App::DrawDebug()
{
   // m_window->draw(m_debugText);
}

void App::CreateScene()
{
    m_scene = new Scene(&win);
	m_scene->SetPlaying(true);
}

bool App::UpdateTime()
{
    DWORD newSysTime = timeGetTime();
    DWORD elapsedSysTime = newSysTime - m_sysTime;
    if (elapsedSysTime < 5)
        return false;
    m_sysTime = newSysTime;
    if (elapsedSysTime > 40)
        elapsedSysTime = 40;

    m_elapsedTime = elapsedSysTime / 1000.0f;
    m_time += m_elapsedTime;
    return true;
}

float App::GetTime()
{
    return m_time;
}

float App::GetElapsedTime()
{
    return m_elapsedTime;
}

Scene* App::GetScene()
{
    return m_scene;
}

void App::Start()
{
	std::srand(time(NULL));
	Board board;
	computerBoard computer;
	board.init();

	Boat boat;
	boat.initialize();

	Game game;

	board.addSensorsToGrid();
	computer.addSensorsToGrid();

	while (win.isOpen()) {
		sf::Event event;
		while (win.pollEvent(event))
		{
			if (event.type == event.KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
					win.close();
			}

			if (event.type == sf::Event::Closed)
				win.close();
		}

		win.clear(sf::Color::White);
		board.draw(win);
		board.updateEvent(win, event, boat);
		if (game.check(board)) { game.start(win, board, boat, computer); }
		board.detectBoatOnGrid(boat);
		// computer.addBoxToSquare(win);
		// board.addBoxToSquare(win);
		computer.readGridInfo(win, boat);
		boat.draw(win);
		board.readUserGridInfo(win, boat);
		board.drawText(win);
		win.display();
	}
}

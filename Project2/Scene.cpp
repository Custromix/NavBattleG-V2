#include "Framework.h"
enum class GridType
{
	Empty,
	Ship,
	Hit,
	Miss
};

enum class ShipType
{
	PorteAvion,
	Croiseur,
	ContreTorpileur,
	SousMarin,
	Torpilleur
};

struct Grid
{
	GridType type = GridType::Empty;
	sf::RectangleShape rect;
};

struct Ship
{
	int size;
	std::vector<Grid*> cells;
};

Scene::Scene()
{
}

Scene::Scene(sf::RenderWindow* window)
{
	m_window = window;
	Ship ship;
	ship.size = 5;
}

Scene::~Scene()
{
}



void Scene::Start()
{
	m_isPlaying = true;
}

void Scene::Update()
{

}

void Scene::DrawScene()
{

}

void Scene::Render()
{
	m_window->clear();
	DrawScene();
	//GetApp()->DrawDebug();
	m_window->display();
}

bool Scene::IsPlaying()
{
	return m_isPlaying;
}

void Scene::SetPlaying(bool flag)
{
	m_isPlaying = flag;
}


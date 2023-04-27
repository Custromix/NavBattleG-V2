#include "Framework.h"

Scene::Scene()
{
}

Scene::Scene(sf::RenderWindow* window)
{
	m_window = window;
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


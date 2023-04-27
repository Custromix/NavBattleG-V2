#pragma once
class Scene
{
public:
	Scene();
	Scene(sf::RenderWindow* window);
	~Scene();

public:
	bool IsPlaying();
	void SetPlaying(bool flag);
	void Start();
	void Update();
	void DrawScene();
	void Render();

private:
	sf::RenderWindow* m_window;
	bool m_isPlaying;
};


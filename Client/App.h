#pragma once
class App
{
public:
	App();
	~App();

public:
	void Init();
	void PrintDebug(String textDebug);
	void DrawDebug();
	void CreateScene();
	bool UpdateTime();

	float GetTime();
	float GetElapsedTime();

	Scene* GetScene();

	void Start();

	enum
	{
		MENU,
		PLAY,
	};

private:
	Scene* m_scene;
	sf::RenderWindow win;
	DWORD m_sysTime;
	Text m_debugText;
	Font m_font;
	float m_elapsedTime;
	float m_time;
	int m_state;
};


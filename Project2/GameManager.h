#pragma once
class GameManager
{
private:
	int cx;
	int cy;
	std::array<std::array<int, 10>, 10> userGridArray;
public : 
	GameManager();
	void parserSetup(std::string gridValue);
	void parserAttack(std::string coordAttack);
};


#include "Sframework.h"

GameManager::GameManager()
{
	cx = 0;
	cy = 0;
}

void GameManager::parserSetup(std::string gridValue)
{
	//std::ostringstream ss(gridValue);
	//std::string tokenLine;
	//std::string tokenvalue;
	//std::vector<int> values(10);
	//std::vector<std::vector<int>> gridValues(10, std::vector<int>(10));

	//while (std::getline(ss, tokenLine, ';'))
	//{
	//	std::stringstream ss(tokenLine);

	//	while (std::getline(ss, tokenLine, ','))
	//	{
	//		values.push_back(std::stoi(tokenvalue));
	//	}
	//	gridValues.push_back(values);
	//}

	//for (int i = 0; i < gridValues.size(); i++)
	//{
	//	for (int j = 0; j < gridValues.size(); j++)
	//	{
	//		gridValues[tokenvalue[i]][tokenLine[j]] = userGridArray[i][j];
	//	}
	//}
}

void GameManager::parserAttack(std::string coordAttack)
{
	//std::ostringstream ss(coordAttack);
	//std::string tokenCoord;
	//while (std::getline(ss, tokenCoord, ','))
	//{
	//	tokenCoord[0] = cx;
	//	tokenCoord[1] = cy;
	//}
}

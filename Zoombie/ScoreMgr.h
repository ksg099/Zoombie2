#pragma once
#include "TextGo.h"
class ScoreMgr : public TextGo
{
protected:
	std::string Score = "Score : ";
	std::string HiScore = "Hi Score : ";
	std::string Wave = "Wave : ";
	std::string Zombies = "zombies : ";

	int score = 0;
	int hiscore = 0;
	int wave = 0;
	int zombies = 0;

public:

	virtual ~ScoreMgr();
	ScoreMgr(const std::string& name = "");

	SetScoreMgr(int)
	void Reset()
	void Draw(sf::RenderWindow& window) override;
};


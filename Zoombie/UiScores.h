#pragma once
#include "TextGo.h"
class UiScores :public TextGo
{

protected:
	std::string textscore = "HI SCORE : ";
	std::string textwave = "WAVE : ";
	std::string textzombies = "ZOMBIES : ";


	int score = 0;
	int wave = 0;
	int zombies = 0;

public:
	UiScores(const std::string& name = "");
	~UiScores() override = default;

	void Reset() override;

	void SetScore(int score);
	void SetWave(int wave);
	void SetZombies(int zombies);

	int GetScore() const { return score; }
	int GetWave() const { return wave; }
	int GetZombies() const { return zombies; }

	void AddScore(int score);
};


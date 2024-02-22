#include "pch.h"
#include "UiScores.h"

UiScores::UiScores(const std::string& name) : TextGo(name)
{
}

void UiScores::Reset()
{
	SetScore(0);
}

void UiScores::SetScore(int score)
{
	this->score += score;
	text.setString(textscore + std::to_string(score));
}

void UiScores::AddScore(int score)
{
	this->score -= score;
	text.setString(textscore + std::to_string(score));

}

void UiScores::SetWave(int wave)
{
	this->wave += wave;
	text.setString(textwave + std::to_string(wave));

}

void UiScores::SetZombies(int zombies)
{
	this->zombies += zombies;
	text.setString(textzombies + std::to_string(zombies));

}


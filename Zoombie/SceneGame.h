#pragma once
#include "Scene.h"
#include "UiScores.h"

class Player;
class ZombieSpawner;
class Item;
class UiScore;

class SceneGame : public Scene
{
protected:
	Player* player = nullptr; //����ϰ� ����ҰŶ� �����ͷ� �̸� ����
	UiScore* uiscores = nullptr;
	Item* item = nullptr;

	std::vector< ZombieSpawner*> spawners;


public:

	SceneGame(SceneIds id);
	~SceneGame() override = default;

	void Init() override;
	void Release() override;

	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};


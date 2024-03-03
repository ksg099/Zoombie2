#pragma once
#include "Scene.h"
#include "ScoreMgr.h"
#include "ItemMgr.h"

class Player;
class ZombieSpawner;
class ItemMgr;
class ScoreMgr;

class SceneGame : public Scene
{
protected:
	Player* player = nullptr; //����ϰ� ����ҰŶ� �����ͷ� �̸� ����
	ScoreMgr* scoremgr = nullptr;
	ItemMgr* itemmgr = nullptr;

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


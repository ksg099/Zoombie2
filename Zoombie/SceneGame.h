#pragma once
#include "Scene.h"

class Player;

class SceneGame : public Scene
{
protected:
	Player* player = nullptr; //빈번하게 사용할거라서 포인터로 미리 선언

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


#pragma once
#include "GameObject.h"
#include "Player.h"
#include "Zombie.h"
class Bullet : public GameObject
{
protected:
	bool isActive;

public:
	Player* player;
	Zombie* zombie;

	void Update(float dt);
	void Draw(sf::RenderWindow& window) override;

};


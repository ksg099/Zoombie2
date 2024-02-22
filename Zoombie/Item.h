#pragma once
#include "GameObject.h"
class Item : public GameObject
{
protected:
	sf::Sprite Healtem;
	sf::Sprite BulletItem;
public:
	

	void Init();
	void Update(float dt);
	void Draw(sf::RenderWindow& window);
};


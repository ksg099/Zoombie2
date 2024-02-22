#pragma once
#include "SpriteGo.h"
class Item : public SpriteGo
{
protected:
	sf::Sprite Healtem;
	sf::Sprite BulletItem;
public:
	

	void Init();
	void Update(float dt);
	void Draw(sf::RenderWindow& window);
};


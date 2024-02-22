#include "pch.h"
#include "Item.h"
#include "Utils.h"

void Item::Init()
{
	GameObject::Init();
	Healtem.setTexture("graphics/health_pickup")

		RandomPosition = Utils::RandomOnUnitCircle() * Utils::
	Healtem.setPosition(RandomPosition);
	Healtem.setOrigin();

	BulletItem.setTexture("graphics/ammo_pickup")
	BulletItem.setPosition(RandomPosition);
	BulletItem.setOrigin();
}

void Item::Update(float dt)
{
}

void Item::Draw(sf::RenderWindow& window)
{
	window.draw(Healtem);
	window.draw(BulletItem);

}

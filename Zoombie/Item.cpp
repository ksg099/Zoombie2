#include "pch.h"
#include "Item.h"
#include "Utils.h"

void Item::Init()
{
	GameObject::Init();

	Healtem = new UiScores("uiscores");
	item->Set(GetTex.Get("fonts/zombiecontrol.ttf"), "uiscores", 50, sf::Color::White);
	item->SetOrigin(Origins::TL);
	item->SetPosition({ 0,0 });
}

void Item::Update(float dt)
{
}

void Item::Draw(sf::RenderWindow& window)
{

}

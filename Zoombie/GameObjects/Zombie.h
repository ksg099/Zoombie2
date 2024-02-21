#pragma once
#include "SpriteGo.h"
#include "Player.h"

class Zombie : public SpriteGo
{
public:
	enum class Types
	{
		Bloater,
		Chase,
		Crawler,
	};
	static const int TotalTypes = 3;

protected:
	Types type;

	int maxHp;
	float speed = 300;


	int hp;
	sf::Vector2f Zombielook = { 0.f, 0.f };
	Player* player;

public:

	static Zombie* Create(Types zombieType);
	Zombie(const std::string& name = "");
	~Zombie() override = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

};


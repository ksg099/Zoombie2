#pragma once
#include "SpriteGo.h"
class Player : public SpriteGo
{
protected:
	sf::Vector2f direction = { 0.f, 0.f };
	sf::Vector2f look = { 0.f, 0.f }; //바라보는 곳의 단위 벡터

	float speed = 800.f;

public:

	Player(const std::string& name = "");
	~Player() = default;

	void Init() override;
	void Release() override;
	void Reset() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

};


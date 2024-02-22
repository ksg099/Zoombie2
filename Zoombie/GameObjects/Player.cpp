#include "pch.h"
#include "Player.h"
#include "Zombie.h"

Player::Player(const std::string& name) : SpriteGo(name)
{
}

void Player::Init()
{
	SpriteGo::Init();
	SetTexture("graphics/player.png");
	SetOrigin(Origins::MC);
}

void Player::Release()
{
	SpriteGo::Release();
}

void Player::Reset()
{
	SpriteGo::Reset();
}

void Player::Update(float dt)
{
	SpriteGo::Update(dt);
	sf::Vector2i mousePos = (sf::Vector2i)InputMgr::GetMousePos(); //���콺 ��ġ ����
	sf::Vector2f mouseWorldPos = SCENE_MGR.GetCurrentScene()->ScreenToWorld(mousePos); //������ǥ�� ����
	look = mouseWorldPos - position;
	Utils::Normalize(look); //look���Ϳ� ���缭 ȸ��


	SetRotation(Utils::Angle(look));
	float angle = Utils::Angle(look);
	
	sprite.setRotation(angle);

	direction.x = InputMgr::GetAxis(Axis::Horizontal);
	direction.y = InputMgr::GetAxis(Axis::Vertical);
	

	if (Utils::Magnitude(direction) > 1.f)
	{
		Utils::Normalize(direction);
	}
	Translate(direction * speed * dt);

	//if (InputMgr::GetKey(sf::Keyboard::W ))
	//{
	//	sprite.setPosition(pos);
	//}

	////if (InputMgr::GetKeyDown(sf::Keyboard::A))

	//if (InputMgr::GetKey(sf::Keyboard::A))
	//{
	//	sprite.setPosition(pos);

	//}
	//if (InputMgr::GetKey(sf::Keyboard::S))
	//{
	//	sprite.setPosition(pos);

	//}
	//if (InputMgr::GetKey(sf::Keyboard::D))
	//{
	//	sprite.setPosition(pos);
	//}

}

void Player::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

#include "pch.h"
#include "SceneGame.h"
#include "Player.h"
#include "TileMap.h"
#include "Zombie.h"

SceneGame::SceneGame(SceneIds id) : Scene(id)
{
}

void SceneGame::Init()
{
	AddGo(new TileMap("Background"));

	player = new Player("Player");
	AddGo(player);

	Scene::Init();
}

void SceneGame::Release()
{
	Scene::Release();
}

void SceneGame::Enter()
{
	Scene::Enter();

	sf::Vector2f windowSize = (sf::Vector2f)FRAMEWORK.GetWindowSize();
	sf::Vector2f centerPos = windowSize * 0.5f;
	worldView.setSize(windowSize);
	worldView.setCenter({0.f, 0.f});
	uiView.setSize(windowSize);
	uiView.setSize(centerPos);


	//sf::Vector2f centerPos = (sf::Vector2f)FRAMEWORK.GetWindowSize() * 0.5f;

	TileMap* tileMap = dynamic_cast<TileMap*>(FindGo("Background")); //다운캐스팅
	tileMap->SetPosition({ 0.f, 0.f });
	tileMap->SetOrigin(Origins::MC);
	//tileMap->SetScale({ 2.f, 2.f });
	//tileMap->SetRotation(45);

	player->SetPosition({ 0.f, 0.f });
}

void SceneGame::Exit()
{
	Scene::Exit();
}

void SceneGame::Update(float dt) //없데이크중에 init랑 reset함수를 불러와야함 ㅐ
{
	Scene::Update(dt);

	worldView.setCenter(player->GetPosition());

	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		Zombie::Types zombieTpye = (Zombie::Types)Utils::RandomRange(0, Zombie::TotalTypes);
		Zombie* zombie = Zombie::Create(zombieTpye);
		zombie->Init();
		zombie->Reset();
		zombie->SetPosition(Utils::RandomInUnitCircle() * 500.f);
		AddGo(zombie);
	}
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

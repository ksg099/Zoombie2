#include "pch.h"
#include "SceneGame.h"
#include "Player.h"
#include "TileMap.h"
#include "Zombie.h"
#include "ZombieSpawner.h"

SceneGame::SceneGame(SceneIds id) : Scene(id)
{
}

void SceneGame::Init()
{
	Scene::Init();

	

	AddGo(new TileMap("Background"));

	spawners.push_back(new  ZombieSpawner());
	spawners.push_back(new  ZombieSpawner());

	for (auto s : spawners) //
	{
		s->SetPosition(Utils::RandomOnUnitCircle() * 250.f); //반경위에 
		AddGo(s);
	}

	player = new Player("Player");
	AddGo(player);

	TileMap* tilemap = new TileMap("Background");
	tilemap->sortLayer = -1;
	AddGo(tilemap);


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
	tileMap->SetPosition({ 0.f, 0.f });
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
		TileMap* tileMap = dynamic_cast<TileMap*>(FindGo("BackGround"));
		
		tileMap->sortLayer = 1;
		if (tileMap->sortLayer == 1)
		{
			tileMap->sortLayer = -1;
		}
		else
		{
			tileMap->sortLayer = 11;
		}
		ResortGo(tileMap);

	}
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

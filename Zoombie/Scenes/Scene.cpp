#include "pch.h"
#include "Scene.h"

Scene::Scene(SceneIds id) :
	id(id),
	texResMgr((ResourceMgr<sf::Texture>::Instance())),
	fontResMgr(RES_MGR_FONT),
	soundResMgr(RES_MGR_SOUND_BUFFER)
{
}

sf::Vector2f Scene::ScreenToWorld(sf::Vector2i screenPos)
{
	return 	FRAMEWORK.GetWindow().mapPixelToCoords(screenPos, worldView);
}

sf::Vector2i Scene::WorldToScreen(sf::Vector2f worldPos)
{
	return FRAMEWORK.GetWindow().mapCoordsToPixel(worldPos, worldView);
}

sf::Vector2f Scene::ScreenToUI(sf::Vector2i screenPos)
{
	return 	FRAMEWORK.GetWindow().mapPixelToCoords(screenPos, uiView);

}

sf::Vector2i Scene::UIToScreen(sf::Vector2f uiPos)
{
	return FRAMEWORK.GetWindow().mapCoordsToPixel(uiPos, uiView);

}

void Scene::Init() //
{
	for (auto obj : gameObjects)
	{
		obj->Init();
	}

	for (auto obj : uigameObjects)
	{
		obj->Init();
	}
}

void Scene::Release()
{
	for (auto obj : gameObjects)
	{
		delete obj;
	}
	gameObjects.clear();

	for (auto obj : uigameObjects)
	{
		delete obj;
	}
	uigameObjects.clear();

}

void Scene::Enter()
{
	for (auto obj : gameObjects)
	{
		obj->Reset();
	}

	for (auto obj : uigameObjects)
	{
		obj->Reset();
	}
}

void Scene::Update(float dt)
{
	for (auto obj : gameObjects)
	{
		if (obj->GetActive())
		{
			obj->Update(dt);
		}
	}

	for (auto obj : uigameObjects)
	{
		if (obj->GetActive())
		{
			obj->Update(dt);
		}
	}
	//업데이트에서 업데이트가 끝난후에
	for (auto obj : removeGameObjects) //지울 오브젝트들을 모아둔것을 지운다.
	{
		auto it = std::find(gameObjects.begin(), gameObjects.end(), obj); //이터레이터
		if (it != gameObjects.end())//찾은 상황
		{
			gameObjects.remove(obj);
			AddGo(obj, Layers::World);
			continue;
		}
		it = std::find(uigameObjects.begin(), uigameObjects.end(), obj); //이터레이터
		if (it != uigameObjects.end())//찾은 상황
		{
			uigameObjects.remove(obj);
			AddGo(obj, Layers::Ui);
			continue;
		}
		resortingGameObjects.clear();
	}

	//모든 업데이트가 끝난 후에 새로운 반복문을 만들어서 지운다.
	for (auto obj : removeGameObjects)
	{
		gameObjects.remove(obj);
		uigameObjects.remove(obj);
		delete obj;
	}
	removeGameObjects.clear();
}

void Scene::Draw(sf::RenderWindow& window)
{
	//gameObjects.sort([](auto a, auto b){ //게임오브젝트 포인터 2개를 받아서 머가 큰지 작은지 해서 넘겨줌
	////a < b
	//	if (a->sortLayer != b->sortLayer) //게임오브젝트 안에 리스트를 정렬하고 싶은데 이 방법을 람다식으로 넘김
	//	{
	//		return a->sortLayer < b->sortLayer;
	//	}
	//	return a->sortOrder < b->sortOrder;
	// });
	//uigameObjects.sort([](auto a, auto b) {
	//if (a->sortLayer != b->sortLayer) 
	//{
	//	return a->sortLayer < b->sortLayer;
	//}
	//return a->sortOrder < b->sortOrder;
	//});
		//두줄만 적으면 에러 발생 정렬할 기준이 없기 때문에
	//람다식 이름없는 함수들  게임오브젝트 안에 들어가있는 애들을 정렬하고 싶은데 
	//정렬할 기준이 없어서 sort를 람다식으로 정의해서 정렬해줬다.
	//람다식 정렬을 할 것이다. [](매개변수) {함수 작성}함수 선언

	const sf::View& saveView = window.getView();
	///그전에 세이브된 기본 View
	window.setView(worldView);

	for (auto obj : gameObjects)
	{
		if (obj->GetActive())
		{
			obj->Draw(window);
		}
	}

	window.setView(uiView);

	for (auto obj : resortingGameObjects)
	{
		auto it = std::find(gameObjects.begin(), gameObjects.end(), obj);
		if (it != gameObjects.end())
		{
			gameObjects.remove(obj);
			AddGo(obj, Layers::World);
			continue;
		}
	}


	for (auto obj : uigameObjects)
	{
		if (obj->GetActive())
		{
			obj->Draw(window);
		}
	}
	window.setView(saveView);

}

GameObject* Scene::FindGo(const std::string& name, Layers layer)
{

	if ((layer & Layers::World) == Layers::World)
	{
		for (auto obj : gameObjects)
		{
			if (obj->name == name)
			{
				return obj;
			}
		}
	}

	if ((layer & Layers::Ui) == Layers::Ui)
	{
		for (auto obj : uigameObjects)
		{
			if (obj->name == name)
			{
				return obj;
			}
		}
	}
	return nullptr;
}

int Scene::FindGoAll(const std::string& name, std::list<GameObject*>& list, Layers layer)
{
	list.clear();
	if ((layer & Layers::World) == Layers::World)
	{
		for (auto obj : gameObjects)
		{
			if (obj->name == name)
			{
				list.push_back(obj);
			}
		}
	}

	if ((layer & Layers::Ui) == Layers::Ui)
	{
		for (auto obj : uigameObjects)
		{
			if (obj->name == name)
			{
				list.push_back(obj);
			}
		}
		return list.size();
	}
}


GameObject* Scene::AddGo(GameObject* obj, Layers layer)
{
	if (layer == World)
	{
		}
	//이터레이터 순회
		if (std::find(gameObjects.begin(), gameObjects.end(), obj) == gameObjects.end())
		{
			if (gameObjects.empty())
			{
				gameObjects.push_back(obj);
				return obj;
			}
			auto it = gameObjects.begin();
			while (it != gameObjects.end()) //계속 돌면서 넣을 자리 갱신
			{
				if (GameObject::CompareDrawOrder(obj, *it)) //
				{
					gameObjects.insert(it, obj);
					return obj;
				}
				it++;
		}
		gameObjects.push_back(obj);
		return obj;

	}
	if (layer == Ui)
	{
		if (std::find(uigameObjects.begin(), uigameObjects.end(), obj) == uigameObjects.end())
		{
			auto it = uigameObjects.begin();
			while (it != uigameObjects.end()) // 계속 돌면서 넣을 자리 갱신
			{
				if (GameObject::CompareDrawOrder(obj, *it)) //
				{
					uigameObjects.insert(it, obj);
					return obj;
				}
				it++;
			}
			uigameObjects.push_back(obj);
			return obj;
		}
	}
	return nullptr;
}

void Scene::ResortGo(GameObject* obj)
{
	resortingGameObjects.push_back(obj);
}

void Scene::RemoveGo(GameObject* obj) //
{
	//obj->SetActive(false);
	removeGameObjects.push_back(obj);
	
	/*gameObjects.remove(obj);
uiGameObjects.remove(obj);*/
}

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
	//������Ʈ���� ������Ʈ�� �����Ŀ�
	for (auto obj : removeGameObjects) //���� ������Ʈ���� ��Ƶа��� �����.
	{
		auto it = std::find(gameObjects.begin(), gameObjects.end(), obj); //���ͷ�����
		if (it != gameObjects.end())//ã�� ��Ȳ
		{
			gameObjects.remove(obj);
			AddGo(obj, Layers::World);
			continue;
		}
		it = std::find(uigameObjects.begin(), uigameObjects.end(), obj); //���ͷ�����
		if (it != uigameObjects.end())//ã�� ��Ȳ
		{
			uigameObjects.remove(obj);
			AddGo(obj, Layers::Ui);
			continue;
		}
		resortingGameObjects.clear();
	}

	//��� ������Ʈ�� ���� �Ŀ� ���ο� �ݺ����� ���� �����.
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
	//gameObjects.sort([](auto a, auto b){ //���ӿ�����Ʈ ������ 2���� �޾Ƽ� �Ӱ� ū�� ������ �ؼ� �Ѱ���
	////a < b
	//	if (a->sortLayer != b->sortLayer) //���ӿ�����Ʈ �ȿ� ����Ʈ�� �����ϰ� ������ �� ����� ���ٽ����� �ѱ�
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
		//���ٸ� ������ ���� �߻� ������ ������ ���� ������
	//���ٽ� �̸����� �Լ���  ���ӿ�����Ʈ �ȿ� ���ִ� �ֵ��� �����ϰ� ������ 
	//������ ������ ��� sort�� ���ٽ����� �����ؼ� ���������.
	//���ٽ� ������ �� ���̴�. [](�Ű�����) {�Լ� �ۼ�}�Լ� ����

	const sf::View& saveView = window.getView();
	///������ ���̺�� �⺻ View
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
	//���ͷ����� ��ȸ
		if (std::find(gameObjects.begin(), gameObjects.end(), obj) == gameObjects.end())
		{
			if (gameObjects.empty())
			{
				gameObjects.push_back(obj);
				return obj;
			}
			auto it = gameObjects.begin();
			while (it != gameObjects.end()) //��� ���鼭 ���� �ڸ� ����
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
			while (it != uigameObjects.end()) // ��� ���鼭 ���� �ڸ� ����
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

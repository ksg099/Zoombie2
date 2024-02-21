#pragma once

class GameObject;

class Scene
{
public:
	enum Layers
	{
		None = 0,
		World = 1,
		Ui = 2,
		Everything = 0xFFFFFFFF,
	};

protected:
	SceneIds id;

	//다중 레이어로 해보자
	std::list<GameObject*> gameObjects;
	std::list<GameObject*> uigameObjects;
	sf::View worldView;
	sf::View uiView;

	ResourceMgr<sf::Texture>& texResMgr;
	ResourceMgr<sf::Font>& fontResMgr;
	ResourceMgr<sf::SoundBuffer>& soundResMgr;
public:
	Scene(SceneIds id);

	virtual ~Scene() = default;

	sf::Vector2f ScreenToWorld(sf::Vector2i screenPos); //스크린좌표를 월드로
	sf::Vector2i WorldToScreen(sf::Vector2f worldPos);//월드로 스크린로
	sf::Vector2f ScreenToUI(sf::Vector2i screenPos);//월드로 스크린로
	sf::Vector2i UIToScreen(sf::Vector2f uiPos);//월드로 스크린로



	virtual void Init(); //씬에 배치되어 있는 오브젝트들이 생성될때 마지막에 
	virtual void Release();

	virtual void Enter();
	virtual void Exit() {};

	virtual void Update(float dt);
	virtual void Draw(sf::RenderWindow& window);

	virtual GameObject* FindGo(const std::string& name, Layers layer = Layers::Everything);
	virtual int FindGoAll(const std::string& name, std::list<GameObject*>& list, Layers layer = Layers::Everything);
	virtual GameObject* AddGo(GameObject* obj, Layers layer = Layers::World);
	virtual void RemoveGo(GameObject* obj);

	Scene(const Scene&) = delete;
	Scene(Scene&&) = delete;
	Scene& operator=(const Scene&) = delete;
	Scene& operator=(Scene&&) = delete;
};


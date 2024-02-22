#pragma once

class GameObject;

class Scene
{
public:
	enum Layers
	{
		None = 0,
		World = 1,
		Ui = 1 << 1,
		Everything = 0xFFFFFFFF, //��� ��Ʈ�� 1�̴�.
	};

protected:
	SceneIds id;

	//���� ���̾�� �غ��� //std::vector<std::list<GameObject*>> gameObjects;
	std::list<GameObject*> gameObjects;
	std::list<GameObject*> uigameObjects;

	std::list<GameObject*> removeGameObjects;

	std::list<GameObject*> resortingGameObjects; //��ȸ�� ���ϰ� ���� ������� ��Ƴ��� ����Ʈ
	
	sf::View worldView;
	sf::View uiView;

	ResourceMgr<sf::Texture>& texResMgr;
	ResourceMgr<sf::Font>& fontResMgr;
	ResourceMgr<sf::SoundBuffer>& soundResMgr;
public:
	Scene(SceneIds id);

	virtual ~Scene() = default;

	sf::Vector2f ScreenToWorld(sf::Vector2i screenPos); //��ũ����ǥ�� �����
	sf::Vector2i WorldToScreen(sf::Vector2f worldPos);//����� ��ũ����
	sf::Vector2f ScreenToUI(sf::Vector2i screenPos);//����� ��ũ����
	sf::Vector2i UIToScreen(sf::Vector2f uiPos);//����� ��ũ����



	virtual void Init(); //���� ��ġ�Ǿ� �ִ� ������Ʈ���� �����ɶ� �������� 
	virtual void Release();

	virtual void Enter();
	virtual void Exit() {};

	virtual void Update(float dt);
	virtual void Draw(sf::RenderWindow& window);

	virtual GameObject* FindGo(const std::string& name, Layers layer = Layers::Everything);
	virtual int FindGoAll(const std::string& name, std::list<GameObject*>& list, Layers layer = Layers::Everything);
	virtual GameObject* AddGo(GameObject* obj, Layers layer = Layers::World);
	
	virtual void ResortGo(GameObject* obj);
	virtual void RemoveGo(GameObject* obj); //


	Scene(const Scene&) = delete;
	Scene(Scene&&) = delete;
	Scene& operator=(const Scene&) = delete;
	Scene& operator=(Scene&&) = delete;
};


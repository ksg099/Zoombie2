#pragma once
#include "GameObject.h"
#include "Zombie.h"

class ZombieSpawner : public GameObject
{

protected:

	std::vector<Zombie::Types> zombieTypes;

	float interval = 1.f; //�����ֱ�
	//float intervalMin; //�������� �ٶ� �ּ� �ִ�
	//float intervalMax;

	int spawnCount = 1;
	//int spawnCountMin; //�������� �ٶ� �ּ� �ִ�
	//int spawnCountMax;

	float radius = 200; //�������ʷ� ���� ������ �ݰ�
	
	float timer = 0,f; //�ð� ��� ���� �ֱ��ٶ��

public:
	ZombieSpawner(const std::string& name = "");
	~ZombieSpawner() override = default;

	virtual void Init() override;
	virtual void Release() override;

	virtual void Reset() override; //�ʱⰪ �����ְ� �ϱ�
	virtual void Update(float dt) override;
};


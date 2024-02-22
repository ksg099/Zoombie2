#pragma once
#include "GameObject.h"
#include "Zombie.h"

class ZombieSpawner : public GameObject
{

protected:

	std::vector<Zombie::Types> zombieTypes;

	float interval = 1.f; //생성주기
	//float intervalMin; //랜덤으로 줄때 최소 최대
	//float intervalMax;

	int spawnCount = 1;
	//int spawnCountMin; //랜덤으로 줄때 최소 최대
	//int spawnCountMax;

	float radius = 200; //좀비스포너로 부터 포지션 반경
	
	float timer = 0,f; //시간 대비 생성 주기줄라고

public:
	ZombieSpawner(const std::string& name = "");
	~ZombieSpawner() override = default;

	virtual void Init() override;
	virtual void Release() override;

	virtual void Reset() override; //초기값 돌려주게 하기
	virtual void Update(float dt) override;
};


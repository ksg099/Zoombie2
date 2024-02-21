#pragma once
#include "GameObject.h"
class TileMap : public GameObject
{
protected:
	sf::VertexArray va;
	std::string spriteSheetId;
	sf::Texture* texture; //포인터 ㅐ
	sf::Transform transform; //변환행령에 곱하면 변환된다 변환행렬을 만드는거

	int rows = 10;
	int cols = 10;
	sf::Vector2f cellCount; //Vector2f, float ㅊㅇ 셀 개수
	sf::Vector2f cellSize; //셀하나의 크기



public:

	TileMap(const std::string& name = "");

	void Set(const sf::Vector2f count, const sf::Vector2f size); //가로 세로, 셀 개수 다 불러오게 하는 함수

	void SetSpriteSheetId(const std::string & id);
	void UpdateTransform();

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void SetPosition(const sf::Vector2f& pos) override;
	void Translate(const sf::Vector2f& delta) override;
	void SetRotation(float r) override;

	void SetScale(const sf::Vector2f& scale) override;

	void SetFlipX(bool flip) override;
	void SetFlipY(bool flip) override;

	void Init() override;
	void Release() override;

	void Reset() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};


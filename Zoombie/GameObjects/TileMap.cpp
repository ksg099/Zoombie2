#include "pch.h"
#include "TileMap.h"

TileMap::TileMap(const std::string& name) : GameObject(name)
{
}

void TileMap::Set(const sf::Vector2f count, const sf::Vector2f size)
{
	cellCount = count;
	cellSize = size;

	va.clear();
	va.setPrimitiveType(sf::Quads);
	va.resize(count.x * count.y * 4); //사각형이라서 4개의 정점, 실제 버텍스 어래이의 실제버텍스 사이즈

	sf::Vector2f posOffsets[4] = {
		{0, 0}, //좌상점
		{size.x, 0}, //오른쪽 
		{size.x, size.y}, //좌상점 기준 대각선
		{0, size.x} //좌상점 아래
	};

	sf::Vector2f texCoord0[4] = {
		{0, 0}, //좌상점
		{50.f, 0}, //오른쪽 
		{50.f, 50.f}, //좌상점 기준 대각선
		{0, 50.f} //좌상점 아래
	};


	for (int i = 0; i < count.y; i++) 		//가로, 세로 사이즈만큼 순ㅇ회 행부터
	{
		for (int j = 0; j < count.x; j++)
		{//외곽은 3, 내부는 0,1,3 랜덤으로 그냥 나오게
			int texIndex = Utils::RandomRange(0, 3);
			if (i == 0 || i == count.y - 1 || j == 0 || j == count.x - 1)
			{
				texIndex = 3;
			}
			int quadindex = i * count.x + j; //2차원 배열 2개를 1차원으로 변환

			sf::Vector2f quadpos(size.x * j,size.y * i); //사각형의 좌상점구하기

			for (int k = 0; k < 4; k++) //위에 찍은 텍스처 하나안에서 
			{
				int vertexIndex = (quadindex * 4) + k;
				va[vertexIndex].position = quadpos + posOffsets[k]; //00 50 0 5050 0 50 50 0
				va[vertexIndex].texCoords = texCoord0[k]; //우리가 넘기는 이미지를
				va[vertexIndex].texCoords.y += texIndex * 50.f; //x값은 안달라짐
			}
		}
	}
}

void TileMap::SetSpriteSheetId(const std::string& id)
{
	spriteSheetId = id;
	texture = &RES_MGR_TEXTURE.Get(spriteSheetId);
}

//변환을 시킬때 초기화한 뒤 변환 순서에 따라 호출할떄도 로테이션, 스케일, 트랜스을 세팅 시켜라
void TileMap::UpdateTransform()
{
	transform = sf::Transform::Identity;
	float scaleX = isFlipX ? -scale.x : scale.x;
	float scaleY = isFlipY ? -scale.y : scale.y;
	transform.scale(scaleX, scaleY, position.x, position.y);
	transform.rotate(rotation); //회전
	transform.translate(position - origin);
}

void TileMap::SetOrigin(Origins preset) //Utils
{
	if (preset == Origins::Custom)
		return;

	originPreset = preset;
	sf::FloatRect bound = va.getBounds();
	origin.x = bound.width * ((int)originPreset % 3) * 0.5f; 
	origin.y = bound.height * ((int)originPreset / 3) * 0.5f;
	UpdateTransform();
}

void TileMap::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	UpdateTransform();
}

void TileMap::SetPosition(const sf::Vector2f& pos) //각 정점들을 순회
{
	GameObject::SetPosition(pos);
	UpdateTransform();
}

void TileMap::Translate(const sf::Vector2f& delta)
{
	GameObject::Translate(delta); //포지션이 바뀜
	UpdateTransform();

}

void TileMap::SetRotation(float r)
{
	GameObject::SetRotation(r);
	void UpdateTransform();

}

void TileMap::SetScale(const sf::Vector2f& scale)
{
	GameObject::SetScale(scale);
	UpdateTransform();
}

void TileMap::SetFlipX(bool flip)
{
	GameObject::SetFlipX(flip);
	UpdateTransform();
}

void TileMap::SetFlipY(bool flip)
{
	GameObject::SetFlipY(flip);
	UpdateTransform();
}

void TileMap::Init() //너비 높이 받아서 초기화할 부분 넣기
{
	GameObject::Init(); //부모클래스꺼 미리 선언

	SetSpriteSheetId("graphics/background_sheet.png");
	Set({ 10, 10 }, { 50.f, 50.f });
	SetOrigin(Origins::MC);

	//transform.rotate(45);
}

void TileMap::Release()
{
	GameObject::Release();
}

void TileMap::Reset()
{
	GameObject::Reset();
}

void TileMap::Update(float dt)
{
	GameObject::Update(dt);
}

void TileMap::Draw(sf::RenderWindow& window)
{
	//GameObject::Draw(window);
	sf::RenderStates state;
	state.texture = texture;
	state.transform = transform;

	window.draw(va, state); //va가 그릴 texture를 포인터로
}

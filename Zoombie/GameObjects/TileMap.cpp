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
	va.resize(count.x * count.y * 4); //�簢���̶� 4���� ����, ���� ���ؽ� ����� �������ؽ� ������

	sf::Vector2f posOffsets[4] = {
		{0, 0}, //�»���
		{size.x, 0}, //������ 
		{size.x, size.y}, //�»��� ���� �밢��
		{0, size.x} //�»��� �Ʒ�
	};

	sf::Vector2f texCoord0[4] = {
		{0, 0}, //�»���
		{50.f, 0}, //������ 
		{50.f, 50.f}, //�»��� ���� �밢��
		{0, 50.f} //�»��� �Ʒ�
	};


	for (int i = 0; i < count.y; i++) 		//����, ���� �����ŭ ����ȸ �����
	{
		for (int j = 0; j < count.x; j++)
		{//�ܰ��� 3, ���δ� 0,1,3 �������� �׳� ������
			int texIndex = Utils::RandomRange(0, 3);
			if (i == 0 || i == count.y - 1 || j == 0 || j == count.x - 1)
			{
				texIndex = 3;
			}
			int quadindex = i * count.x + j; //2���� �迭 2���� 1�������� ��ȯ

			sf::Vector2f quadpos(size.x * j,size.y * i); //�簢���� �»������ϱ�

			for (int k = 0; k < 4; k++) //���� ���� �ؽ�ó �ϳ��ȿ��� 
			{
				int vertexIndex = (quadindex * 4) + k;
				va[vertexIndex].position = quadpos + posOffsets[k]; //00 50 0 5050 0 50 50 0
				va[vertexIndex].texCoords = texCoord0[k]; //�츮�� �ѱ�� �̹�����
				va[vertexIndex].texCoords.y += texIndex * 50.f; //x���� �ȴ޶���
			}
		}
	}
}

void TileMap::SetSpriteSheetId(const std::string& id)
{
	spriteSheetId = id;
	texture = &RES_MGR_TEXTURE.Get(spriteSheetId);
}

//��ȯ�� ��ų�� �ʱ�ȭ�� �� ��ȯ ������ ���� ȣ���ҋ��� �����̼�, ������, Ʈ������ ���� ���Ѷ�
void TileMap::UpdateTransform()
{
	transform = sf::Transform::Identity;
	float scaleX = isFlipX ? -scale.x : scale.x;
	float scaleY = isFlipY ? -scale.y : scale.y;
	transform.scale(scaleX, scaleY, position.x, position.y);
	transform.rotate(rotation); //ȸ��
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

void TileMap::SetPosition(const sf::Vector2f& pos) //�� �������� ��ȸ
{
	GameObject::SetPosition(pos);
	UpdateTransform();
}

void TileMap::Translate(const sf::Vector2f& delta)
{
	GameObject::Translate(delta); //�������� �ٲ�
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

void TileMap::Init() //�ʺ� ���� �޾Ƽ� �ʱ�ȭ�� �κ� �ֱ�
{
	GameObject::Init(); //�θ�Ŭ������ �̸� ����

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

	window.draw(va, state); //va�� �׸� texture�� �����ͷ�
}

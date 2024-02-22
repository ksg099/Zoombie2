#include "pch.h"
#include "Utils.h"

float Utils::Clamp(float v, float min, float max)
{
	if (v < min)
		return min;
	if (v > max)
		return max;
	return v;
}

float Utils::RandomValue()
{
	return (float)rand() / RAND_MAX;
}

float Utils::RandomRange(float min, float max)
{
	float value = RandomValue();
	value *= max - min;	
	value += min;
	return value;
}

sf::Vector2f Utils::RandomOnUnitCircle()
{
	sf::Transform rotation;
	rotation.rotate(RandomRange(0.f, 360.f));
	return rotation * sf::Vector2f (1.f, 0.f);
}

sf::Vector2f Utils::RandomInUnitCircle()
{
	return RandomOnUnitCircle() * RandomValue();
}

int Utils::RandomRange(int min, int maxExclude)
{
	int range = maxExclude - min;
	int rand = std::rand() % range;
	rand += min;
	return rand;
}

sf::Vector2f Utils::SetOrigin(sf::Transformable& obj, Origins originPreset, const sf::FloatRect& rect)
{
	// Rect Width, Height
	sf::Vector2f newOrigin(rect.width, rect.height);
	newOrigin.x *= ((int)originPreset % 3) * 0.5f; // 0 1 2 => 0 0.5 1
	newOrigin.y *= ((int)originPreset / 3) * 0.5f; // 0 1 2 => 0 0.5 1
	obj.setOrigin(newOrigin);

	return newOrigin;
}

sf::Vector2f Utils::SetOrigin(sf::Sprite& obj, Origins originPreset)
{
	return SetOrigin(obj, originPreset, obj.getLocalBounds());
}

sf::Vector2f Utils::SetOrigin(sf::Text& obj, Origins originPreset)
{
	return SetOrigin(obj, originPreset, obj.getLocalBounds());
}

sf::Vector2f Utils::SetOrigin(sf::Shape& obj, Origins originPreset)
{
	return SetOrigin(obj, originPreset, obj.getLocalBounds());
}

float Utils::SqrMagnitude(const sf::Vector2f& vec)
{

	return vec.x * vec.x + vec.y * vec.y; //삼각형의 밑변 높이 제곱 = 빗변 제곱
}

float Utils::Magnitude(const sf::Vector2f& vec)
{
	return std::sqrt(vec.x * vec.x + vec.y * vec.y); //빗변에 제곱한 값을루트 씌워서 리턴
}

void Utils::Normalize(sf::Vector2f& vec) //벡터가 매개변수로 넘어오면 할당하면 호출한애를
{
	float mag = Magnitude(vec);
	if (mag != 0.f)
	{
		vec /= mag;
	}
}

float Utils::Distance(const sf::Vector2f& p1, const sf::Vector2f& p2)
{
	return Magnitude(p2 - p1);
}

float Utils::Angle(const sf::Vector2f& vec)
{
	return RadianToDegree(std::atan2f(vec.y, vec.x));
}

float Utils::RadianToDegree(float radian) //그냥 공식임
{
	return radian * (180.0 / M_PI); //M_PI는 3.14말하는거임 
}

float Utils::DegreeToRadian(float degree) //그냥 공식임
{
	return degree * (M_PI / 180.0);
}

sf::Vector2f Utils::GetNormal(const sf::Vector2f& vec) //다시 레퍼런스
{
	float mag = Magnitude(vec);
	if (mag == 0.f)
		return vec;
	return vec / mag;
}

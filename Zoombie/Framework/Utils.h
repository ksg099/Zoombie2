#pragma once

class Utils
{
public:
	static float Clamp(float v, float min, float max);

	// Random
	static float RandomValue(); // 0.0f ~ 1.0f
	static float RandomRange(float min, float max);
	static sf::Vector2f RandomOnUnitCircle();
	static sf::Vector2f RandomInUnitCircle();
	static int RandomRange(int min, int maxExclude);


	// Origin
	static sf::Vector2f SetOrigin(sf::Transformable& obj, Origins originPreset, const sf::FloatRect& rect);
	static sf::Vector2f SetOrigin(sf::Sprite& obj, Origins originPreset);
	static sf::Vector2f SetOrigin(sf::Text& obj, Origins originPreset);
	static sf::Vector2f SetOrigin(sf::Shape& obj, Origins originPreset);

	//Math
	static float SqrMagnitude(const sf::Vector2f& vec); //벡터의 길이의 제곱을 리턴
	static float Magnitude(const sf::Vector2f& vec); //벡터의 길이를 반환
	static sf::Vector2f GetNormal(const sf::Vector2f& vec); //벡터의 길이를 1로 바꾼 벡터로 반환(정규화)

	static void Normalize(sf::Vector2f& vec); //벡터의 길이를 1로 바꾼 벡터로 반환(정규화)
	static float Distance(const sf::Vector2f& p1, const sf::Vector2f& p2);
	static float Angle(const sf::Vector2f& vec); //각도를 float단위로 리턴
	static float RadianToDegree(float radian);
	static float DegreeToRadian(float degree);


};
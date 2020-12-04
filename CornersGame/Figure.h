#pragma once
#include <string>

#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Figure
{
public:
	Figure();
	Figure(const Texture& texture, const IntRect &rectangle, const Vector2f &offset);
	void Draw(RenderWindow &window) const;
	
	void SetPosition(const Vector2f& position);
	Vector2f getPosition() const;

	Sprite GetSprite() const;
private:
	Sprite sprite_;
	Texture texture_;
};


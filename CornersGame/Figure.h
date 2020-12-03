#pragma once
#include <string>

#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Figure
{
public:
	Figure(const Texture& texture, const IntRect &rectangle, const Vector2f &offset);
	void Draw(RenderWindow &window) const;
private:
	Sprite sprite_;
	Texture texture_;
};


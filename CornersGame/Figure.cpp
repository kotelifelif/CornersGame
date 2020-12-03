#include "Figure.h"

Figure::Figure(const Texture& texture, const IntRect& rectangle, const Vector2f& offset) :
	texture(texture),
	sprite(texture, rectangle)
{
	sprite.move(offset);
}

void Figure::Draw(RenderWindow& window) const
{
	window.draw(sprite);
}

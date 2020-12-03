#include "Figure.h"

Figure::Figure(const Texture& texture, const IntRect& rectangle, const Vector2f& offset) :
	texture_(texture),
	sprite_(texture, rectangle)
{
	sprite_.move(offset);
}

void Figure::Draw(RenderWindow& window) const
{
	window.draw(sprite_);
}

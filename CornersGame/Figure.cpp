#include "Figure.h"

Figure::Figure()
{
}

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

void Figure::SetPosition(const Vector2f& position)
{
	sprite_.setPosition(position);
}

Vector2f Figure::getPosition() const
{
	return sprite_.getPosition();
}

Sprite Figure::GetSprite() const
{
	return sprite_;
}

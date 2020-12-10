#include "Figure.h"

Figure::Figure()
{
}

Figure::Figure(const Texture& texture, const IntRect& rectangle, const Vector2f& offset, const Cell& target_cell_) :
	texture_(texture),
	sprite_(texture, rectangle),
	target_cell_(target_cell_)
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

void Figure::SetTargetCell(const Cell& cell)
{
	target_cell_ = cell;
}

Cell Figure::GetTargetCell()
{
	return target_cell_;
}

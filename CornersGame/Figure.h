#pragma once
#include "Board.h"

#include <string>

#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Figure
{
public:
	Figure();
	Figure(const Texture& texture, const IntRect& rectangle, const Vector2f& offset, const Cell& target_cell_ = Cell());
	void Draw(RenderWindow &window) const;
	
	void SetPosition(const Vector2f& position);
	Vector2f getPosition() const;

	Sprite GetSprite() const;

	void SetTargetCell(const Cell& cell);
	Cell GetTargetCell();
private:
	Sprite sprite_;
	Texture texture_;
	Cell target_cell_;
	Cell temporary_target_cell_;
};


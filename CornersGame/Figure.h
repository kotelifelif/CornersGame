#pragma once
#include "Board.h"

#include <string>

#include <SFML/Graphics.hpp>

class Figure
{
public:
	Figure();
	Figure(const sf::Texture& texture, const sf::IntRect& rectangle, const sf::Vector2f& offset, const Cell& target_cell_ = Cell());
	void Draw(sf::RenderWindow &window) const;
	
	void SetPosition(const sf::Vector2f& position);
	sf::Vector2f GetPosition() const;

	sf::Sprite GetSprite() const;

	void SetTargetCell(const Cell& cell);
	Cell GetTargetCell();
private:
	sf::Sprite sprite_;
	sf::Texture texture_;
	Cell target_cell_;
	Cell temporary_target_cell_;
};


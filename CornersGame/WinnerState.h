#pragma once
#include "State.h"
#include "Board.h"
#include "Player.h"
#include "AI.h"

#include <vector>

#include <SFML/Graphics.hpp>

class WinnerState : public State
{
public:
	WinnerState(const bool is_player_win);
	virtual ~WinnerState();
	void Draw(sf::RenderWindow& window) override;
	GameStateType Update(sf::Event& event, sf::RenderWindow& window) override;
private:
	sf::Font font_;
	sf::Text congratulatory_text_;
	sf::Text menu_text_;
	sf::Texture board_texture_;
	Board board_;
};

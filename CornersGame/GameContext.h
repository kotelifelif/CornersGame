#pragma once
#include "State.h"

#include <SFML/Graphics.hpp>

class GameContext
{
public:
	GameContext(State* state);
	~GameContext();
	void Draw(sf::RenderWindow& window);
	void Update(sf::Event& event, sf::RenderWindow& window);
	void ChangeStateType(State* state);
private:
	State* state_;
	GameStateType state_type_;
};


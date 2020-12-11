#pragma once
#include "State.h"

class GameContext
{
public:
	GameContext(State* state);
	~GameContext();
	void Draw(RenderWindow& window);
	void Update(Event& event, RenderWindow& window);
	void ChangeStateType(State* state);
private:
	State* state_;
	GameStateType state_type_;
};


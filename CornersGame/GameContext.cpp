#include "GameContext.h"
#include "GameState.h"
#include "MenuState.h"
#include "WinnerState.h"

GameContext::GameContext(State* state) :
	state_(state)
{
}

GameContext::~GameContext()
{
	delete state_;
}

void GameContext::Draw(RenderWindow& window)
{
	state_->Draw(window);
}

void GameContext::Update(Event& event, RenderWindow& window)
{
	state_type_ = state_->Update(event, window);
	switch (state_type_)
	{
	case GameStateType::kBlackGameState:
		ChangeStateType(new GameState(false));
		break;
	case GameStateType::kWhiteGameState:
		ChangeStateType(new GameState(true));
		break;
	case GameStateType::kMenuState:
		ChangeStateType(new MenuState());
		break;
	case GameStateType::kWinnerState:
		ChangeStateType(new WinnerState());
		break;
	}
}

void GameContext::ChangeStateType(State* state)
{
	if (state_ != nullptr) {
		delete state_;
	}

	state_ = state;
}

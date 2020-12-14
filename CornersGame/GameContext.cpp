#include "GameContext.h"
#include "GameState.h"
#include "MenuState.h"
#include "WinnerState.h"

GameContext::GameContext(std::unique_ptr<State> state)
    : state_(std::move(state)), state_type_(GameStateType::kNoState) {}

GameContext::~GameContext() {}

void GameContext::Draw(sf::RenderWindow& window) { state_->Draw(window); }

void GameContext::Update(sf::Event& event, sf::RenderWindow& window) {
  state_type_ = state_->Update(event, window);
  switch (state_type_) {
    case GameStateType::kBlackGameState:
      ChangeStateType(std::make_unique<GameState>(false));
      break;
    case GameStateType::kWhiteGameState:
      ChangeStateType(std::make_unique<GameState>(true));
      break;
    case GameStateType::kMenuState:
      ChangeStateType(std::make_unique<MenuState>());
      break;
    case GameStateType::kPlayerWinnerState:
      ChangeStateType(std::make_unique<WinnerState>(true));
      break;
    case GameStateType::kComputerWinnerState:
        ChangeStateType(std::make_unique<WinnerState>(false));
        break;
  }
}

void GameContext::ChangeStateType(std::unique_ptr<State> state) {
  state_ = std::move(state);
}

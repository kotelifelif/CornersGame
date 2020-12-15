#pragma once
#include "State.h"

#include <memory>

#include <SFML/Graphics.hpp>

class GameContext {
 public:
  GameContext(std::unique_ptr<State> state);
  ~GameContext();
  void Draw(sf::RenderWindow& window) const;
  void Update(sf::Event& event, sf::RenderWindow& window);
  void ChangeStateType(std::unique_ptr<State> state);

 private:
  std::unique_ptr<State> state_;
  GameStateType state_type_;
};


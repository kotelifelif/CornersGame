#include "Player.h"
#include "Board.h"
#include "AI.h"
#include "GameState.h"
#include "MenuState.h"
#include "WinnerState.h"
#include "GameContext.h"

#include <SFML/Graphics.hpp>

#include "Constants.h"



int main() {
  const std::string kWindowName("The Corners game");
  sf::RenderWindow window(
      sf::VideoMode(constants::kWindowWidth, constants::kWindowHeight),
      kWindowName);

  GameContext context(new MenuState());

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
      context.Update(event, window);
    }

    window.clear(sf::Color::White);
    context.Draw(window);

    window.display();
  }

  return 0;
}
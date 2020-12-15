#include "MenuState.h"
#include "GameContext.h"
#include "State.h"

#include <memory>

#include <SFML/Graphics.hpp>

#include "Constants.h"



int main() {
  sf::RenderWindow window(
      sf::VideoMode(constants::kWindowWidth, constants::kWindowHeight),
      "The Corners game");

  GameContext context(std::make_unique<MenuState>());

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
      context.Update(event, window);
    }

    window.clear(sf::Color::White);
    context.Draw(window);

    window.display();
  }

  return 0;
}
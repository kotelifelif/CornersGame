#include "MenuState.h"

#include "Constants.h"


MenuState::MenuState() {
  // Texture and Sprite for board
  board_texture_.loadFromFile("../images/board.png");
  board_ = Board(board_texture_, sf::Vector2i(constants::kInitialPositionX,
                                              constants::kInitialPositionY));

  // Texture for white figure
  figure_texture_.loadFromFile("../images/figures.png");

  black_figure_ = Figure(
      figure_texture_,
      sf::IntRect(constants::kPersonFigureStartPositionX,
                  constants::kPersonFigureStartPositionY,
                  constants::kFigureWidth, constants::kFigureHeight),
      sf::Vector2f(
          constants::kPersonPositionInCellX + 3 * constants::kCellSizeX,
          constants::kPersonPositionInCellY + 4 * constants::kCellSizeY));
  white_figure_ = Figure(
      figure_texture_,
      sf::IntRect(constants::kAiFigureStartPositionX,
                  constants::kAiFigureStartPositionY, constants::kFigureWidth,
                  constants::kFigureHeight),
      sf::Vector2f(
          constants::kPersonPositionInCellX + 4 * constants::kCellSizeX,
          constants::kPersonPositionInCellY + 4 * constants::kCellSizeY));

  font_.loadFromFile("../fonts/arial.ttf");
  text_.setFont(font_);
  text_.setString(L"Выбери фигуру");
  text_.setCharacterSize(24);
  text_.setPosition(sf::Vector2f(
      constants::kPersonPositionInCellX + 2 * constants::kCellSizeX,
      constants::kPersonPositionInCellY + 3 * constants::kCellSizeY));
}

MenuState::~MenuState() {}

void MenuState::Draw(sf::RenderWindow& window) {
  board_.Draw(window);
  black_figure_.Draw(window);
  white_figure_.Draw(window);
  window.draw(text_);
}

GameStateType MenuState::Update(sf::Event& event, sf::RenderWindow& window) {
  if (event.type == sf::Event::MouseButtonPressed) {
    if (event.key.code == sf::Mouse::Left) {
      if (black_figure_.GetSprite().getGlobalBounds().contains(
              event.mouseButton.x, event.mouseButton.y)) {
        return GameStateType::kBlackGameState;
      } else if (white_figure_.GetSprite().getGlobalBounds().contains(
                     event.mouseButton.x, event.mouseButton.y)) {
        return GameStateType::kWhiteGameState;
      }
    }
  }

  return GameStateType::kNoState;
}

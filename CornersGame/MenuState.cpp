#include "MenuState.h"

#include "Constants.h"


MenuState::MenuState()
    : kMenuXOffset(2),
      kMenuYOffset(3),
      kFontSize(24),
      kMenuBlackFigureOffsetX(3),
      kMenuBlackFigureOffsetY(4),
      kMenuWhiteFigureOffsetX(4),
      kMenuWhiteFigureOffsetY(4) {
  // Texture and Sprite for board
  board_texture_.loadFromFile("../images/board.png");
  board_ = Board(board_texture_, sf::Vector2i(constants::kInitialPositionX,
                                              constants::kInitialPositionY));

  // Texture for white figure
  figure_texture_.loadFromFile("../images/figures.png");

  black_figure_ =
      Figure(figure_texture_,
             sf::IntRect(constants::kBlackFigureStartPositionX,
                         constants::kBlackFigureStartPositionY,
                         constants::kFigureWidth, constants::kFigureHeight),
             sf::Vector2f(constants::kBlackPositionInCellX +
                              kMenuBlackFigureOffsetX * constants::kCellSizeX,
                          constants::kBlackPositionInCellY +
                              kMenuBlackFigureOffsetY * constants::kCellSizeY));

  white_figure_ =
      Figure(figure_texture_,
             sf::IntRect(constants::kWhiteFigureStartPositionX,
                         constants::kWhiteFigureStartPositionY,
                         constants::kFigureWidth, constants::kFigureHeight),
             sf::Vector2f(constants::kBlackPositionInCellX +
                              kMenuWhiteFigureOffsetX * constants::kCellSizeX,
                          constants::kBlackPositionInCellY +
                              kMenuWhiteFigureOffsetY * constants::kCellSizeY));

  font_.loadFromFile("../fonts/arial.ttf");
  text_.setFont(font_);
  text_.setString(L"Выбери фигуру");
  text_.setCharacterSize(kFontSize);
  text_.setPosition(sf::Vector2f(
      constants::kBlackPositionInCellX + kMenuXOffset * constants::kCellSizeX,
      constants::kBlackPositionInCellY + kMenuYOffset * constants::kCellSizeY));
}

MenuState::~MenuState() {}

void MenuState::Draw(sf::RenderWindow& window) const {
  board_.Draw(window);
  black_figure_.Draw(window);
  white_figure_.Draw(window);
  window.draw(text_);
}

GameStateType MenuState::Update(sf::Event& event, sf::RenderWindow& window) {
  // Check if we make a click on text
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

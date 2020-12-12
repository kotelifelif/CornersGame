#include "WinnerState.h"

#include "Constants.h"

WinnerState::WinnerState(const bool is_player_win) {
  // Texture and Sprite for board
  board_texture_.loadFromFile("../images/board.png");
  board_ = Board(board_texture_, sf::Vector2i(constants::kInitialPositionX,
                                              constants::kInitialPositionY));

  font_.loadFromFile("../fonts/arial.ttf");
  congratulatory_text_.setFont(font_);

  if (is_player_win) {
    congratulatory_text_.setString(L"Вы победили!");
  } else {
    congratulatory_text_.setString(L"Победил компьютер!");
  }

  congratulatory_text_.setCharacterSize(24);
  congratulatory_text_.setPosition(sf::Vector2f(
      constants::kBlackPositionInCellX +
          constants::kCongratulatoryTextOffsetX * constants::kCellSizeX,
      constants::kBlackPositionInCellY +
          constants::kCongratulatoryTextOffsetY * constants::kCellSizeY));

  menu_text_.setFont(font_);
  menu_text_.setString(L"Перейти в меню");
  menu_text_.setCharacterSize(constants::kFontSize);
  menu_text_.setPosition(
      sf::Vector2f(constants::kBlackPositionInCellX +
                       constants::kMenuTextOffsetX * constants::kCellSizeX,
                   constants::kBlackPositionInCellY +
                       constants::kMenuTextOffsetY * constants::kCellSizeY));
}

WinnerState::~WinnerState() {}

void WinnerState::Draw(sf::RenderWindow& window) {
  board_.Draw(window);
  window.draw(congratulatory_text_);
  window.draw(menu_text_);
}

GameStateType WinnerState::Update(sf::Event& event, sf::RenderWindow& window) {
  if (event.type == sf::Event::MouseButtonPressed) {
    if (event.key.code == sf::Mouse::Left) {
      if (menu_text_.getGlobalBounds().contains(event.mouseButton.x,
                                                event.mouseButton.y)) {
        return GameStateType::kMenuState;
      }
    }
  }

  return GameStateType::kNoState;
}

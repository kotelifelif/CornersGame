#include "GameState.h"
#include "AI.h"

#include <SFML/Graphics.hpp>

#include "Constants.h"

GameState::GameState(bool is_white)
    : is_white_(is_white),
      ai_(),
      x_offset_(0),
      y_offset_(0),
      figure_number_(0) {
  // Texture and Sprite for board
  board_texture_.loadFromFile("../images/board.png");
  board_ = Board(board_texture_, sf::Vector2i(constants::kInitialPositionX,
                                              constants::kInitialPositionY));

  // Texture for white figure
  figure_texture_.loadFromFile("../images/figures.png");

  if (is_white_) {
    is_player_move_ = true;
    // Create person player
    person_player_ = Player(InitializeFigures(
        figure_texture_,
        sf::IntRect(constants::kWhiteFigureStartPositionX,
                    constants::kWhiteFigureStartPositionY,
                    constants::kFigureWidth, constants::kFigureHeight),
        sf::Vector2i(constants::kWhitePositionInCellX,
                     constants::kWhitePositionInCellY),
        board_, false));
    ;
    // Create ai_player
    ai_player_ = Player(InitializeFigures(
        figure_texture_,
        sf::IntRect(constants::kBlackFigureStartPositionX,
                    constants::kBlackFigureStartPositionY,
                    constants::kFigureWidth, constants::kFigureHeight),
        sf::Vector2i(constants::kBlackPositionInCellX,
                     constants::kBlackPositionInCellY),
        board_, true));
  } else {
    is_player_move_ = false;
    // Create person player
    person_player_ = Player(InitializeFigures(
        figure_texture_,
        sf::IntRect(constants::kBlackFigureStartPositionX,
                    constants::kBlackFigureStartPositionY,
                    constants::kFigureWidth, constants::kFigureHeight),
        sf::Vector2i(constants::kBlackPositionInCellX,
                     constants::kBlackPositionInCellY),
        board_, true));
    // Create ai_player
    ai_player_ = Player(InitializeFigures(
        figure_texture_,
        sf::IntRect(constants::kWhiteFigureStartPositionX,
                    constants::kWhiteFigureStartPositionY,
                    constants::kFigureWidth, constants::kFigureHeight),
        sf::Vector2i(constants::kWhitePositionInCellX,
                     constants::kWhitePositionInCellY),
        board_, false));
  }
}

GameState::~GameState() {}

void GameState::Draw(sf::RenderWindow& window) {
  board_.Draw(window);
  ai_player_.Draw(window);
  person_player_.Draw(window);
}


GameStateType GameState::Update(sf::Event& event, sf::RenderWindow& window) {
  if (is_player_move_) {
    if (event.type == sf::Event::MouseButtonPressed) {
      if (event.key.code == sf::Mouse::Left) {
        sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
        std::vector<Figure> person_figures = person_player_.GetFigures();
        for (size_t i = 0; i < person_figures.size(); ++i) {
          if (person_figures[i].GetSprite().getGlobalBounds().contains(
                  mouse_position.x, mouse_position.y)) {
            figure_number_ = i;
            x_offset_ = mouse_position.x -
                       person_figures[i].GetSprite().getPosition().x;
            y_offset_ = mouse_position.y -
                       person_figures[i].GetSprite().getPosition().y;
            old_position_ = person_figures[i].GetSprite().getPosition();
          }
        }
      }
    }

    if (event.type == sf::Event::MouseButtonReleased) {
      if (event.key.code == sf::Mouse::Left) {
        new_position_ = sf::Vector2f(sf::Mouse::getPosition(window));

        sf::Vector2i old_position_coordinates =
            board_.GetPointLocation(old_position_);
        sf::Vector2i mouse_position_coordinates = board_.GetPointLocation(
            sf::Vector2f(sf::Mouse::getPosition(window)));
        x_offset_ = abs(mouse_position_coordinates.x - old_position_coordinates.x);
        y_offset_ = abs(mouse_position_coordinates.y - old_position_coordinates.y);
        if ((!board_.GetBusy(new_position_)) &&
            ((x_offset_ == 1 && y_offset_ == 0) || (y_offset_ == 1 && x_offset_ == 0))) {
          board_.SetBusy(old_position_, false);
          board_.SetBusy(new_position_, true);
          board_.SetCollor(old_position_, FigureColor::kNone);
          if (is_white_) {
            board_.SetCollor(new_position_, FigureColor::kWhite);
          } else {
            board_.SetCollor(new_position_, FigureColor::kBlack);
          }
          new_position_ = board_.ConvertToBoardPosition(new_position_);
          person_player_.SetFigurePosition(figure_number_, new_position_);
          is_player_move_ = false;
        }
      }
    }

    if (event.type == sf::Event::KeyPressed) {
      if (event.key.code == sf::Keyboard::Up) {
        return GameStateType::kComputerWinnerState;
      } else if (event.key.code == sf::Keyboard::Down) {
        return GameStateType::kPlayerWinnerState;
      }
    }
  } else {
    std::vector<Figure> ai_figures = ai_player_.GetFigures();
    std::pair<sf::Vector2i, int> optimal_path =
        ai_.FindBestMove(board_, ai_player_);

    Cell position = board_.GetCell(optimal_path.first.x, optimal_path.first.y);
    new_position_ = sf::Vector2f(position.rectangle.left + constants::kXOffset,
                                position.rectangle.top + constants::kYOffset);

    board_.SetBusy(ai_figures[optimal_path.second].GetPosition(), false);
    board_.SetCollor(ai_figures[optimal_path.second].GetPosition(),
                     FigureColor::kNone);
    ai_player_.SetFigurePosition(optimal_path.second, new_position_);

    board_.SetBusy(new_position_, true);
    if (is_white_) {
      board_.SetCollor(new_position_, FigureColor::kWhite);
    } else {
      board_.SetCollor(new_position_, FigureColor::kBlack);
    }

    is_player_move_ = true;
  }

  return CheckWinner();
}


std::vector<Figure> GameState::InitializeFigures(
    const sf::Texture& texture, const sf::IntRect& rectangle,
    const sf::Vector2i& initial_position, Board& board, const bool is_left_top) {
  std::vector<Figure> figures;
  for (int i = 0; i < constants::kFigureRows; ++i) {
    for (int j = 0; j < constants::kFigureColumns; ++j) {
      Figure player_figure(
          texture, rectangle,
          sf::Vector2f(initial_position.x + i * constants::kCellSizeX,
                       initial_position.y + j * constants::kCellSizeY));
      if (is_left_top) {
        player_figure.SetTargetCell(board.GetCell(constants::kRows - i - 1,
                                                  constants::kColumns - j - 1));
        board.SetBusy(i, j, true);
        board.SetCollor(i, j, FigureColor::kBlack);
      } else {
        player_figure.SetTargetCell(board.GetCell(i, j));
        board.SetBusy(constants::kRows - i - 1, constants::kColumns - j - 1,
                      true);
        board.SetCollor(i, j, FigureColor::kWhite);
      }
      figures.push_back(player_figure);
    }
  }
  return figures;
}

GameStateType GameState::CheckWinner() {
  int figures_in_target_cell_count = 0;
  Cell cell;
  for (int i = 0; i < constants::kFigureRows; ++i) {
    for (int j = 0; j < constants::kFigureColumns; ++j) {
      if (is_white_ && board_.GetCell(i, j).color == FigureColor::kWhite) {
        ++figures_in_target_cell_count;
      } else if (!is_white_ && board_.GetCell((constants::kRows - i - 1),
                                              (constants::kColumns - j - 1))
                                       .color == FigureColor::kBlack) {
        ++figures_in_target_cell_count;
      }
    }
  }

  if (figures_in_target_cell_count ==
      constants::kFigureRows * constants::kFigureColumns) {
    return GameStateType::kPlayerWinnerState;
  }

  figures_in_target_cell_count = 0;
  for (auto& figure : ai_player_.GetFigures()) {
    cell = board_.GetCell(figure.GetPosition());
    if (figure.GetTargetCell() == cell) {
      ++figures_in_target_cell_count;
    }
  }

  if (figures_in_target_cell_count ==
      constants::kFigureRows * constants::kFigureColumns) {
    return GameStateType::kComputerWinnerState;
  }

  return GameStateType::kNoState;
}

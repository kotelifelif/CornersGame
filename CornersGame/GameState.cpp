#include "GameState.h"
#include "AI.h"

#include <SFML/Graphics.hpp>

#include "Constants.h"

GameState::GameState(bool is_white) : is_white_(is_white), ai() {
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
        sf::IntRect(constants::kAiFigureStartPositionX,
                    constants::kAiFigureStartPositionY, constants::kFigureWidth,
                    constants::kFigureHeight),
        sf::Vector2i(constants::kAiPositionInCellX,
                     constants::kAiPositionInCellY),
        board_, false));
    ;
    // Create ai_player
    ai_player_ = Player(InitializeFigures(
        figure_texture_,
        sf::IntRect(constants::kPersonFigureStartPositionX,
                    constants::kPersonFigureStartPositionY,
                    constants::kFigureWidth, constants::kFigureHeight),
        sf::Vector2i(constants::kPersonPositionInCellX,
                     constants::kPersonPositionInCellY),
        board_, true));
  } else {
    is_player_move_ = false;
    // Create person player
    person_player_ = Player(InitializeFigures(
        figure_texture_,
        sf::IntRect(constants::kPersonFigureStartPositionX,
                    constants::kPersonFigureStartPositionY,
                    constants::kFigureWidth, constants::kFigureHeight),
        sf::Vector2i(constants::kPersonPositionInCellX,
                     constants::kPersonPositionInCellY),
        board_, true));
    // Create ai_player
    ai_player_ = Player(InitializeFigures(
        figure_texture_,
        sf::IntRect(constants::kAiFigureStartPositionX,
                    constants::kAiFigureStartPositionY, constants::kFigureWidth,
                    constants::kFigureHeight),
        sf::Vector2i(constants::kAiPositionInCellX,
                     constants::kAiPositionInCellY),
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
          auto rect = person_figures[i].GetSprite().getGlobalBounds();
          if (person_figures[i].GetSprite().getGlobalBounds().contains(
                  mouse_position.x, mouse_position.y)) {
            n = i;
            // is_player_move_ = true;
            new_figure = person_figures[i];
            dx = mouse_position.x -
                 person_figures[i].GetSprite().getPosition().x;
            dy = mouse_position.y -
                 person_figures[i].GetSprite().getPosition().y;
            old_position = person_figures[i].GetSprite().getPosition();
          }
        }
      }
    }

    if (event.type == sf::Event::MouseButtonReleased) {
      if (event.key.code == sf::Mouse::Left) {
        sf::Vector2f p = new_figure.GetSprite().getPosition();
        new_position = sf::Vector2f(sf::Mouse::getPosition(window));
        // Maybe Vector2i
        std::pair<int, int> old_position_coordinates =
            board_.GetPointLocation(old_position);
        std::pair<int, int> mouse_position_coordinates =
            board_.GetPointLocation(
                sf::Vector2f(sf::Mouse::getPosition(window)));
        dx = abs(mouse_position_coordinates.first -
                 old_position_coordinates.first);
        dy = abs(mouse_position_coordinates.second -
                 old_position_coordinates.second);
        if ((!board_.GetBusy(new_position)) &&
            ((dx == 1 && dy == 0) || (dy == 1 && dx == 0))) {
          board_.SetBusy(old_position, false);
          board_.SetBusy(new_position, true);
          board_.SetCollor(old_position, FigureColor::kNone);
          if (is_white_) {
            board_.SetCollor(new_position, FigureColor::kWhite);
          } else {
            board_.SetCollor(new_position, FigureColor::kBlack);
          }
          new_position = board_.ConvertToBoardPosition(new_position);
          person_player_.SetFigurePosition(n, new_position);
          is_player_move_ = false;
        }
      }
    }

    if (event.type == sf::Event::KeyPressed) {
      if (event.key.code == sf::Keyboard::Up) {
        sf::Vector2f p = new_figure.GetSprite().getPosition();
        new_position = sf::Vector2f(p.x, p.y - constants::kCellSizeY);
        if (!board_.GetBusy(new_position)) {
          board_.SetBusy(old_position, false);
          board_.SetBusy(new_position, true);
          person_player_.SetFigurePosition(n, new_position);
          is_player_move_ = false;
        }

      } else if (event.key.code == sf::Keyboard::Left) {
        sf::Vector2f p = new_figure.GetSprite().getPosition();
        new_position = sf::Vector2f(p.x - constants::kCellSizeX, p.y);
        if (!board_.GetBusy(new_position)) {
          board_.SetBusy(old_position, false);
          board_.SetBusy(new_position, true);
          person_player_.SetFigurePosition(n, new_position);
          is_player_move_ = false;
        }

      } else if (event.key.code == sf::Keyboard::Right) {
        sf::Vector2f p = new_figure.GetSprite().getPosition();
        new_position = sf::Vector2f(p.x + constants::kCellSizeX, p.y);
        if (!board_.GetBusy(new_position)) {
          board_.SetBusy(old_position, false);
          board_.SetBusy(new_position, true);
          person_player_.SetFigurePosition(n, new_position);
          is_player_move_ = false;
        }

      } else if (event.key.code == sf::Keyboard::Down) {
        return GameStateType::kWinnerState;
        sf::Vector2f p = new_figure.GetSprite().getPosition();
        new_position = sf::Vector2f(p.x, p.y + constants::kCellSizeY);
        if (!board_.GetBusy(new_position)) {
          board_.SetBusy(old_position, false);
          board_.SetBusy(new_position, true);
          person_player_.SetFigurePosition(n, new_position);
          is_player_move_ = false;
        }
      }
    }
  } else {
    std::vector<Figure> ai_figures = ai_player_.GetFigures();
    std::pair<sf::Vector2i, int> optimal_path =
        ai.FindBestMove(board_, ai_player_);

    Cell position = board_.GetCell(optimal_path.first.x, optimal_path.first.y);
    sf::Vector2f figure_position(position.rectangle.left + constants::kXOffset,
                                 position.rectangle.top + constants::kYOffset);

    board_.SetBusy(ai_figures[optimal_path.second].GetPosition(), false);
    board_.SetCollor(ai_figures[optimal_path.second].GetPosition(),
                     FigureColor::kNone);
    ai_player_.SetFigurePosition(optimal_path.second, figure_position);

    board_.SetBusy(figure_position, true);
    if (is_white_) {
      board_.SetCollor(figure_position, FigureColor::kWhite);
    } else {
      board_.SetCollor(figure_position, FigureColor::kBlack);
    }

    is_player_move_ = true;
  }

  return CheckWinner();
}


std::vector<Figure> GameState::InitializeFigures(
    const sf::Texture& texture, const sf::IntRect& rectangle,
    const sf::Vector2i& initial_position, Board& board, bool is_left_top) {
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
    return GameStateType::kWinnerState;
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
    return GameStateType::kWinnerState;
  }

  return GameStateType::kNoState;
}

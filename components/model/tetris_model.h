/**
 * @file
 * @brief Заголовочный файл класса TetrisModel
 */

#pragma once

#include "../model.h"

extern "C" {
#include "../../brick_game/tetris/backend.h"
}

namespace s21 {
/**
 * @brief Класс модели тетриса
 */
class TetrisModel : public Model {
 public:
  TetrisModel();
  ~TetrisModel() = default;
  void userInput(UserAction_t action, bool hold) override;
  GameInfo_t updateCurrentState() override;
};
}  // namespace s21

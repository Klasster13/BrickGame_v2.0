/**
 * @brief Заголовочный файл класса Selector
 */

#pragma once

#include <iostream>

#include "../brick_game/snake/snakemodel.h"
#include "controller.h"
#include "model/tetris_model.h"
#include "view/desktop_view.h"
#include "view/cli_view.h"

namespace s21 {
/**
 * @brief Класс для начального выбора модели и представления
 */
class Selector {
 private:
  Model *model;  ///< Указатель на выбранную модель
  Controller *ctrl;  ///< Указатель на контроллер
  View *view;  ///< Указатель на выбранное представление

  void select_game();
  void select_view();

 public:
  Selector();
  ~Selector();
  void start_game();
};

}  // namespace s21

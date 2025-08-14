/**
 * @brief Заголовочный файл класса Controller
 */

#pragma once

#include "model.h"
#include "specification.h"

namespace s21 {
/**
 * @brief Класс контроллер
 */
class Controller {
 private:
  Model *model;  ///< Указатель на выбранную модель игры

 public:
  Controller(Model *model);
  ~Controller();

  GameInfo_t update(UserAction_t action, bool hold);
};
}  // namespace s21

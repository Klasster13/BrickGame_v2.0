/**
 * @file
 * @brief Заголовочный файл класса CliView
 */

#pragma once

#include "../controller.h"
#include "view.h"

// #ifdef __cplusplus
extern "C" {
// #endif

#include "../../gui/cli/frontend.h"

// #ifdef __cplusplus
}
// #endif

namespace s21 {
/**
 * @brief Класс консольного представления
 */
class CliView : public View {
 private:
  Controller *ctrl;  ///< Контроллер

 public:
  CliView(Controller *value);
  ~CliView();
  int start_game() override;
  void game_loop();
  UserAction_t get_signal();
  void color_pairs();
};
}  // namespace s21
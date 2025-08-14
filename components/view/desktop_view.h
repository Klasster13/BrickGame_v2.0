/**
 * @file
 * @brief Заголовочный файл класса DesktopView
 */

#pragma once

#include "../../gui/desktop/mainwindow.hpp"
#include "../controller.h"
#include "view.h"

namespace s21 {
/**
 * @brief Класс десктопного представления
 */
class DesktopView : public View {
 private:
  Controller *ctrl;  ///< Контроллер

 public:
  DesktopView(Controller *value);
  ~DesktopView();
  int start_game() override;
};
}  // namespace s21
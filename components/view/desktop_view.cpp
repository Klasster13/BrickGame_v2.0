/**
 * @file
 * @brief Файл с методами класса DesktopView
 */

#include "desktop_view.h"

namespace s21 {
/**
 * @brief Конструктор представления
 * @param Value Указатель на контроллер
 */
DesktopView::DesktopView(Controller *value) : ctrl(value) {}

/**
 * @brief Деструктор представления
 */
DesktopView::~DesktopView() { delete ctrl; }

/**
 * @brief Метод начала игры
 */
int DesktopView::start_game() {
  int argc = 1;
  const char *str = "main.cpp";
  char *argv = (char *)str;

  QApplication app(argc, &argv);

  Window window(ctrl);

  window.show();

  return app.exec();
}

}  // namespace s21

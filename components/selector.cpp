/**
 * @brief Файл с методами класса Selector
 */

#include "selector.h"

namespace s21 {

/**
 * @brief Конструктор класса
 */
Selector::Selector() {
  select_game();
  ctrl = new Controller(model);
  select_view();
}

/**
 * @brief Деструктор класса
 */
Selector::~Selector() { delete view; }

/**
 * @brief Метод выбора модели игры
 */
void Selector::select_game() {
  if (system("clear") == -1) std::exit(0);

  std::cout << "Select game" << std::endl;
  std::cout << "1) Tetris" << std::endl;
  std::cout << "2) Snake" << std::endl;

  int n = 0;
  std::cin >> n;

  if (n == 1)
    model = new TetrisModel;
  else if (n == 2)
    model = new SnakeModel;
  else
    std::exit(0);
}

/**
 * @brief Метод выбора представления
 */
void Selector::select_view() {
  if (system("clear") == -1) std::exit(0);

  std::cout << "Select view" << std::endl;
  std::cout << "1) CLI" << std::endl;
  std::cout << "2) Desktop" << std::endl;

  int n = 0;
  std::cin >> n;

  if (n == 1)
    view = new CliView(ctrl);
  else if (n == 2)
    view = new DesktopView(ctrl);
  else
    std::exit(0);
}

/**
 * @brief Метод запуска выбранной игры
 */
void Selector::start_game() { view->start_game(); }

}  // namespace s21

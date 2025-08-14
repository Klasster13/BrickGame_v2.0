/**
 * @file
 * @brief Основной файл, запускающий программу.
 */

/**
 * @mainpage Brick Game
 *
 * Реализация Тетриса и Змейки на языках Си и Си++.
 * \image html FSM_SNAKE.png "Конечный автомат змейки"
 * @author kristieh
 */

#include "components/selector.h"

/**
 * @brief Вход в программу.
 */
int main() {
  s21::Selector s;

  s.start_game();

  return 0;
}
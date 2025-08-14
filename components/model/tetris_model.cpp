/**
 * @file
 * @brief Методы класса TetrisModel
 */

#include "tetris_model.h"

namespace s21 {
/**
 * @brief Конструктор модели
 */
TetrisModel::TetrisModel() {}

/**
 * @brief Метод обработки нажатых пользователем клавиш
 * @param action Нажатие пользователя
 * @param hold Параметр длительного зажатия клавиши
 */
void TetrisModel::userInput(UserAction_t action, bool hold) {
  ::userInput(action, hold);
}

/**
 * @brief Метод обновления состояния игры.
 * @return Возвращает актуальную структуру с данными по игре
 */
GameInfo_t TetrisModel::updateCurrentState() { return ::updateCurrentState(); }

}  // namespace s21

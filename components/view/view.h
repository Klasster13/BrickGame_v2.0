/**
 * @brief Заголовочный файл абстрактного класса View
 */

#pragma once

#include "../specification.h"

namespace s21 {
/**
 * @brief Абстрактный класс представления
 */
class View {
 public:
  /**
   * @brief Виртуальный деструктор
   */
  virtual ~View() = default;

  /**
   * @brief Виртуальный метод начала игры
   */
  virtual int start_game() = 0;
};
}  // namespace s21

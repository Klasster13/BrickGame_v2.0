/**
 * @brief Заголовочный файл абстрактного класса Model
 */

#pragma once

#include "specification.h"

namespace s21 {
/**
 * @brief Абстрактный класс модели
 */
class Model {
 public:
  /**
   * @brief Виртуальный деструктор
   */
  virtual ~Model() = default;

  /**
   * @brief Виртуальный метод обработки нажатия клавиши пользователем
   * @param action Нажатие пользователя
   * @param hold Параметр длительного зажатия клавиши
   */
  virtual void userInput(UserAction_t action, bool hold) = 0;

  /**
   * @brief Виртаульный метод обновления состояния игры.
   * @return Возвращает актуальную структуру с данными по игре
   */
  virtual GameInfo_t updateCurrentState() = 0;
};
}  // namespace s21

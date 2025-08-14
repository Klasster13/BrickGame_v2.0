/**
 * @brief Методы класса Controller
 */

#include "controller.h"

/**
 * @brief Конструктор класса
 * @param value Указатель на модель
 */
s21::Controller::Controller(Model *value) : model(value) {}

/**
 * @brief Деструктор класса
 */
s21::Controller::~Controller() { delete model; }

/**
 * @brief Метод передачи нажатия кнопки от представления до модели и получение
 * актуальной структуры для отрисовки
 * @param action Нажатие пользователя
 * @param hold Параметр длительного зажатия клавиши
 * @return Актуальная структура для отрисовки
 */
GameInfo_t s21::Controller::update(UserAction_t action, bool hold) {
  model->userInput(action, hold);

  return model->updateCurrentState();
}

/**
 * @file
 * @brief Заголовочный файл с общими типами для игр.
 */

#ifndef SPECIFICATION_H
#define SPECIFICATION_H

/**
 * @brief Последовательность для состояния игры
 */
typedef enum {
  START = 0,   ///< Начало
  SPAWN,       ///< Появление нового блока/змейки
  MOVING,      ///< Свободное движение
  SHIFTING,    ///< Сдвиг по исчетению таймера
  COLLIDE,     ///< Столкновение
  PAUSE,       ///< Пауза
  GAMEOVER,    ///< Проигрыш
  EXIT_STATE,  ///< Выход
  WINNER       ///< Победа
} GameState_t;

/**
 * @brief Последовательность для нажатой клавиши
 */
typedef enum {
  Start = 0,  ///< Enter
  Pause,      ///< 'p'
  Terminate,  ///< 'q'
  Left,       ///< Стрелка влево
  Right,      ///< Стрелка Вправо
  Up,         ///< Стрелка вверх
  Down,       ///< Стрелка вниз
  Action,     ///< Пробел
  Another     ///< Любая другая кнопка
} UserAction_t;

/**
 * @brief Структура с актуальными данными по игре
 */
typedef struct {
  int **field;  ///< Игровое поле
  int **next;  ///< Поле следующей фигуры(не используется в змейке)
  int score;   ///< Текущий счет
  int high_score;  ///< Рекордный счет
  int level;       ///< Текущий уровень
  int speed;       ///< Текущая скорость
  int pause;       ///< Текущее состояние игры
} GameInfo_t;

#endif  // SPECIFICATION_H

/**
 * @file
 * @brief Заголовочный файл с типами тетриса.
 */

#ifndef TYPES_H
#define TYPES_H

#include "backend.h"

/**
 * @brief структура для данных о текущей и следующей фигуре
 */
typedef struct {
  int y;  ///< координата блока-курсора по оси Y
  int x;  ///< координата блока-курсора по оси X
  int figure_type;  ///< тип текущей фигуры (от 0 до 6)
  int figure_state;  ///< положение текущей фигуры (от 0 до 3)
  int next_figure_type;  ///< тип следующей фигуры (от 0 до 6)
  int figure_color;  ///< цвет текущей фигуры (от 1 до 7)
  int next_figure_color;  ///< цвет следующей фигуры (от 1 до 7)
} Figureinfo_t;

/**
 * @brief структура с данными о фигурах и самой игре
 */
typedef struct {
  GameInfo_t *gameinfo;  ///< указатель на статичную структуру данных игры
  Figureinfo_t *figureinfo;  ///< указатель на статичную структуру фигуры
  struct timespec start_time;  ///< время начала отсчета таймера
  bool hold;  ///< параметр длительного зажатия клавиши
  int lines;  ///< количество стертых линий за игру
  int I_counter;  ///< счетчик фигур без I(палки)
} Params_t;

#endif  // TYPES_H

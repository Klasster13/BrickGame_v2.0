/**
 * @file
 * @brief Заголовочный файл классов змейки.
 */

#pragma once

#include <chrono>
#include <iostream>
#include <list>
#include <vector>

#include "../../components/model.h"
#include "types.h"

namespace s21 {
/**
 * @brief Класс модели змейки
 */
class SnakeModel : public Model {
 private:
  std::vector<std::vector<int>> field;  ///< Игровое поле в виде вектора
  int **next;  ///< Поле следующей фигуры (не используется)
  int score;       ///< Текущий счет
  int high_score;  ///< Рекордный счет
  int level;       ///< Текущий уровень
  int speed;       ///< Текущая скорость
  int state;       ///< Текущее состояние игры
  long start_time;  ///< Начальное время для движения вперед

  std::pair<int, int> apple;             ///< Яблоко
  std::list<std::pair<int, int>> snake;  ///< тело змейки

  size_t length;          ///< длина змейки
  Direction_t direction;  ///< направление движения
  bool block_new_dir;  ///< флаг блокировки смены направления

  bool debug;  ///< флаг для дебага

  void fsm(const UserAction_t &action);

  void start(const UserAction_t &action);
  void spawn();
  void moving(const UserAction_t &action);
  void shifting();
  void eat_apple();
  void pause_game(const UserAction_t &action);
  void end_game(const UserAction_t &action);

  void set_direction(const UserAction_t action);
  bool same_direction(const UserAction_t action);
  void collide();
  void move_forward();
  void reset_snake();

  void new_apple_coord();

  void draw_snake();
  void erase_tail();
  void draw_apple();

  void get_hi_score_from_file();
  void save_hi_score_in_file();
  void set_time();
  void init_snake();
  bool check_timer();
  void reset_game();

 public:
  SnakeModel();
  SnakeModel(bool value);
  ~SnakeModel() override;

  std::pair<int, int> get_head_coord();
  int get_game_state();

  void userInput(UserAction_t action, bool hold) override;
  GameInfo_t updateCurrentState() override;
};

}  // namespace s21

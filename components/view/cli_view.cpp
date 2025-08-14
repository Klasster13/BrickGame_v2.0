/**
 * @file
 * @brief Файл с методами класса CliView
 */

#include "cli_view.h"

namespace s21 {
/**
 * @brief Конструктор представления
 * @param Value Указатель на контроллер
 */
CliView::CliView(Controller *value) : ctrl(value) {}

/**
 * @brief Деструктор представления
 */
CliView::~CliView() { delete ctrl; }

/**
 * @brief Метод инициализации начальных параметров ncursed и запуск основного
 * цикла
 */
int CliView::start_game() {
  srand(time(0));
  initscr();
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);
  color_pairs();

  game_loop();

  curs_set(1);
  endwin();

  return 0;
}

/**
 * @brief Метод с основным циклом игры
 */
void CliView::game_loop() {
  GameInfo_t gameinfo;
  gameinfo.pause = START;

  while (gameinfo.pause != EXIT_STATE) {
    gameinfo = ctrl->update(get_signal(), 0);
    print_game(gameinfo);
  }
}

/**
 * @brief Метод обработки ввода клавиши от пользователя
 * @return Нажатие пользователя
 */
UserAction_t CliView::get_signal() {
  UserAction_t action = (UserAction_t)ERR;

  switch (getch()) {
    case '\n':
      action = Start;
      break;
    case 'p':
      action = Pause;
      break;
    case 'q':
      action = Terminate;
      break;
    case KEY_LEFT:
      action = Left;
      break;
    case KEY_RIGHT:
      action = Right;
      break;
    case KEY_UP:
      action = Up;
      break;
    case KEY_DOWN:
      action = Down;
      break;
    case ' ':
      action = Action;
      break;
    default:
      action = (UserAction_t)ERR;
      break;
  }

  return action;
}

/**
 * @brief Метод инициализации цветов для ncursed
 */
void CliView::color_pairs() {
  start_color();
  init_pair(1, COLOR_WHITE, COLOR_BLACK);
  init_pair(2, COLOR_CYAN, COLOR_BLACK);
  init_pair(3, COLOR_GREEN, COLOR_BLACK);
  init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(5, COLOR_RED, COLOR_BLACK);
  init_pair(6, COLOR_BLUE, COLOR_BLACK);
  init_pair(7, COLOR_YELLOW, COLOR_BLACK);
}

}  // namespace s21

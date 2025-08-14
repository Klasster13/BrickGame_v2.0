/**
 * @file
 * @brief Функции отрисовки интерфейса в окне консоли.
 */
#include "frontend.h"

/**
 * @brief Функция отрисовки актуального состояния игры.
 * @param GameInfo_t Структура с актуальными данными для вывода.
 */
void print_game(GameInfo_t gameinfo) {
  // вывод поля
  for (int y = 0; y < 20; y++) {
    int shift = 0;
    for (int x = 0; x < 10; x++) {
      if (gameinfo.field[y][x]) {
        attron(COLOR_PAIR(gameinfo.field[y][x]));
        mvaddstr(y + 1, x + 1 + shift, "[]");
        attroff(COLOR_PAIR(gameinfo.field[y][x]));
      } else {
        mvaddstr(y + 1, x + 1 + shift, "  ");
      }
      shift++;
    }
  }

  // вывод следующей фигуры
  if (gameinfo.next) {
    for (int y = 1; y < MAX_FIGURE_SIZE - 1; y++) {
      int shift = 0;
      for (int x = 0; x < MAX_FIGURE_SIZE; x++) {
        if (gameinfo.next[y][x]) {
          attron(COLOR_PAIR(gameinfo.next[y][x]));
          mvaddstr(y + 13, x + 10 * 2 + HUD_WIDTH / 2 - 1 + shift, "[]");
          attroff(COLOR_PAIR(gameinfo.next[y][x]));
        } else
          mvaddstr(y + 13, x + 10 * 2 + HUD_WIDTH / 2 - 1 + shift, "  ");
        shift++;
      }
    }
  }
  // вывод статистики
  print_stats(gameinfo);

  // вывод доп сообщений
  if (gameinfo.pause == PAUSE)
    print_pause();
  else if (gameinfo.pause == START) {
    print_overlay();
    print_start();
  } else if (gameinfo.pause == GAMEOVER)
    print_gameover();
  else if (gameinfo.pause == EXIT_STATE)
    print_exit();
  else if (gameinfo.pause == WINNER)
    print_win();

  refresh();
}

/**
 * @brief Функция отрисовки границ игрового поля и заголовков.
 */
void print_overlay() {
  print_rectangle(0, 20 + 1, 0, 10 * 2 + 1);
  print_rectangle(0, 20 + 1, 10 * 2 + 2, 10 * 2 + HUD_WIDTH + 3);

  print_rectangle(1, 3, 10 * 2 + 3, 10 * 2 + HUD_WIDTH + 2);
  mvprintw(1, 10 * 2 + HUD_WIDTH / 2, "HiSCORE");
  print_rectangle(4, 6, 10 * 2 + 3, 10 * 2 + HUD_WIDTH + 2);
  mvprintw(4, 10 * 2 + HUD_WIDTH / 2 + 1, "SCORE");
  print_rectangle(7, 9, 10 * 2 + 3, 10 * 2 + HUD_WIDTH + 2);
  mvprintw(7, 10 * 2 + HUD_WIDTH / 2 + 1, "LEVEL");
  print_rectangle(10, 12, 10 * 2 + 3, 10 * 2 + HUD_WIDTH + 2);
  mvprintw(10, 10 * 2 + HUD_WIDTH / 2 + 1, "SPEED");
  print_rectangle(13, 16, 10 * 2 + 3, 10 * 2 + HUD_WIDTH + 2);
  mvprintw(13, 10 * 2 + HUD_WIDTH / 2 + 1, "NEXT");
  mvprintw(18, 10 * 2 + HUD_WIDTH / 2 - 1, "p - pause");
  mvprintw(19, 10 * 2 + HUD_WIDTH / 2 - 1, "q - exit");
}

/**
 * @brief Функция отрисовки стартового сообщения.
 */
void print_start() {
  // print_rectangle(20 / 2 - 1, 20 / 2 + 2, 10 - 5, 10 +
  // 7);
  mvprintw(20 / 2, 10 - 4, "Press ENTER");
  mvprintw(20 / 2 + 1, 10 - 4, " to start! ");
}

/**
 * @brief Функция отрисовки сообщения паузы.
 */
void print_pause() {
  print_rectangle(20 / 2 - 1, 20 / 2 + 1, 10 - 4, 10 + 4);
  mvprintw(20 / 2, 10 - 3, " PAUSE ");
}

/**
 * @brief Функция отрисовки сообщения о проигрыше.
 */
void print_gameover() {
  print_rectangle(20 / 2 - 1, 20 / 2 + 2, 10 - 7, 10 + 7);
  mvprintw(20 / 2, 10 - 6, "  GAME OVER  ");
  mvprintw(20 / 2 + 1, 10 - 6, "Press any key");
  refresh();
}

/**
 * @brief Функция отрисовки сообщения о победе.
 */
void print_win() {
  print_rectangle(20 / 2 - 1, 20 / 2 + 2, 10 - 7, 10 + 7);
  mvprintw(20 / 2, 10 - 6, "   WINNER!   ");
  mvprintw(20 / 2 + 1, 10 - 6, "Press any key");
  refresh();
}

/**
 * @brief Функция отрисовки сообщения выхода.
 */
void print_exit() {
  mvaddch(20 / 2 - 1, 0, ACS_LTEE);
  mvaddch(20 / 2 - 1, 10 * 2 + 1, ACS_RTEE);
  mvhline(20 / 2 - 1, 1, ACS_HLINE, 10 * 2);
  mvprintw(20 / 2, 10 - 9, " THANKS FOR PLAYING ");
  mvprintw(20 / 2 + 1, 10 - 9, "   Press any key    ");
  mvaddch(20 / 2 + 2, 0, ACS_LTEE);
  mvaddch(20 / 2 + 2, 10 * 2 + 1, ACS_RTEE);
  mvhline(20 / 2 + 2, 1, ACS_HLINE, 10 * 2);
  refresh();
  nodelay(stdscr, FALSE);
  getch();
  nodelay(stdscr, TRUE);
}

/**
 * @brief Функция отрисовки статистики.
 * @param gameinfo Структура с актаульными данными статистики игры.
 */
void print_stats(GameInfo_t gameinfo) {
  if (gameinfo.high_score > gameinfo.score)
    mvprintw(2, 10 * 2 + HUD_WIDTH / 2 + 1, "%04d", gameinfo.high_score);
  else
    mvprintw(2, 10 * 2 + HUD_WIDTH / 2 + 1, "%04d", gameinfo.score);

  mvprintw(5, 10 * 2 + HUD_WIDTH / 2 + 1, "%04d", gameinfo.score);
  mvprintw(8, 10 * 2 + HUD_WIDTH / 2 + 3, "%d ", gameinfo.level);
  mvprintw(11, 10 * 2 + HUD_WIDTH / 2 + 1, "0.%d", gameinfo.speed / 10);
}

/**
 * @brief Функция отрисовки прямоугольника.
 * @param y1 Координата левого верхнего угла по оси Y
 * @param y2 Координата правого нижнего угла по оси Y
 * @param x1 Координата левого верхнего угла по оси X
 * @param x2 Координата правого нижнего угла по оси X
 */
void print_rectangle(int y1, int y2, int x1, int x2) {
  // горизонтальные линии
  mvhline(y1, x1, ACS_HLINE, x2 - x1);
  mvhline(y2, x1, ACS_HLINE, x2 - x1);

  // вертикальные линии
  mvvline(y1, x1, ACS_VLINE, y2 - y1);
  mvvline(y1, x2, ACS_VLINE, y2 - y1);

  // углы
  mvaddch(y1, x1, ACS_ULCORNER);
  mvaddch(y2, x1, ACS_LLCORNER);
  mvaddch(y1, x2, ACS_URCORNER);
  mvaddch(y2, x2, ACS_LRCORNER);
}

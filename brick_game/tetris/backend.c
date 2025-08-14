/**
 * @file
 * @brief Основные функции работы тетриса.
 */

#include "backend.h"

/**
 * @brief Основная функция обработки действий пользователя на основе нажатых
 * клавиш.
 * @param action ввод пользователя или его отсутсвие
 * @param hold параметр длительного зажатия клавиши
 */
void userInput(UserAction_t action, bool hold) {
  static Params_t *prms = NULL;

  prms = create_prms(prms);

  chech_timer(prms);

  function func = fsm_table(prms->gameinfo->pause, action);
  if (func) func(prms);

  prms->hold = (hold) ? true : false;
}

/**
 * @brief Функция, хранящая в массиве координаты фигуры относительно курсора.
 * @param figure_type Текущий тип фигуры от 0 до 6
 * @param figure_state Текущее состояние фигуры от 0 до 3
 * @param block_number Номер блока фигуры от 0 до 3
 * @param coord Координата блока 0 - Y, 1 - X
 * @return int Возвращает координату блока.
 */
int get_block_coord(int figure_type, int figure_state, int block_number,
                    int coord) {
  // [номер фигуры][состояние][кол-во блоков][координаты блока]
  static const int tetrominos[FIGURES][FIGURE_STATES][BLOCKS][2] = {
      // I
      {
          {{0, -2}, {0, -1}, {0, 0}, {0, 1}},
          {{-1, 0}, {0, 0}, {1, 0}, {2, 0}},
          {{0, -2}, {0, -1}, {0, 0}, {0, 1}},
          {{-1, 0}, {0, 0}, {1, 0}, {2, 0}},
      },
      // J
      {
          {{0, -1}, {0, 0}, {0, 1}, {1, 1}},
          {{-1, 0}, {-1, 1}, {0, 0}, {1, 0}},
          {{-1, -1}, {0, -1}, {0, 0}, {0, 1}},
          {{-1, 0}, {0, 0}, {1, 0}, {1, -1}},
      },
      // L
      {
          {{1, -1}, {0, -1}, {0, 0}, {0, 1}},
          {{-1, 0}, {0, 0}, {1, 0}, {1, 1}},
          {{0, -1}, {0, 0}, {0, 1}, {-1, 1}},
          {{-1, -1}, {-1, 0}, {0, 0}, {1, 0}},
      },
      // O
      {
          {{0, -1}, {0, 0}, {1, -1}, {1, 0}},
          {{0, -1}, {0, 0}, {1, -1}, {1, 0}},
          {{0, -1}, {0, 0}, {1, -1}, {1, 0}},
          {{0, -1}, {0, 0}, {1, -1}, {1, 0}},
      },
      // S
      {
          {{0, 0}, {0, 1}, {1, -1}, {1, 0}},
          {{0, 0}, {-1, 0}, {0, 1}, {1, 1}},
          {{0, 0}, {0, 1}, {1, -1}, {1, 0}},
          {{0, 0}, {-1, 0}, {0, 1}, {1, 1}},
      },
      // T
      {
          {{0, -1}, {0, 0}, {0, 1}, {1, 0}},
          {{-1, 0}, {0, 0}, {0, 1}, {1, 0}},
          {{-1, 0}, {0, -1}, {0, 0}, {0, 1}},
          {{-1, 0}, {0, -1}, {0, 0}, {1, 0}},
      },
      // Z
      {
          {{0, 0}, {0, -1}, {1, 0}, {1, 1}},
          {{0, 0}, {1, 0}, {0, 1}, {-1, 1}},
          {{0, 0}, {0, -1}, {1, 0}, {1, 1}},
          {{0, 0}, {1, 0}, {0, 1}, {-1, 1}},
      }};

  return tetrominos[figure_type][figure_state][block_number][coord];
}

/**
 * @brief Функция, создающая основную статичную структуру, хранящую данные о
 * состоянии игры.
 * @param pointer указатель, если передается NULL, то структура создается со
 * стартовыми значенями.
 * @return Params_t* Возвращает указатель на статичную структуру.
 */
Params_t *create_prms(Params_t *pointer) {
  static Params_t prms = {0};

  if (pointer == NULL) {
    prms.figureinfo = create_figure_info();
    prms.gameinfo = get_field_info(prms.figureinfo);
    prms.gameinfo->pause = START;
    prms.start_time.tv_sec = 0;
    prms.start_time.tv_nsec = 0;
    prms.hold = false;
    prms.lines = 0;
    prms.I_counter = 0;
  }
  return &prms;
}
void reset_prms(Params_t *prms) {
  reset_figure_info(prms->figureinfo);
  reset_field_info(prms->gameinfo, prms->figureinfo);
  prms->start_time.tv_sec = 0;
  prms->start_time.tv_nsec = 0;
  prms->hold = false;
  prms->lines = 0;
  prms->I_counter = 0;
}

/**
 * @brief Функция создает статичную структуру с данными по фигурам.
 * @return Figureinfo_t* Возвращает указатель статичной структуры.
 */
Figureinfo_t *create_figure_info() {
  static Figureinfo_t current_figure = {0};

  reset_figure_info(&current_figure);

  return &current_figure;
}

/**
 * @brief Функция возвращает начальные данные по фигуре.
 */
void reset_figure_info(Figureinfo_t *current_figure) {
  srand(time(NULL));
  current_figure->y = -2;
  current_figure->x = 5;
  current_figure->figure_type = rand() % 7;
  current_figure->figure_state = 0;
  current_figure->next_figure_type = rand() % 7;
  // цвета
  if (COLOR) {
    current_figure->figure_color = current_figure->figure_type + 1;
    current_figure->next_figure_color = current_figure->next_figure_type + 1;
  } else {
    current_figure->figure_color = 1;
    current_figure->next_figure_color = 1;
  }
}

/**
 * @brief Функция получения указателя на структуру с данными по полю
 * и статистике.
 * @param figure_info Принимает указатель на структуры данных по фигурам.
 * @return GameInfo_t* Возвращает указатель статичной структуры.
 */
GameInfo_t *get_field_info(Figureinfo_t *figure_info) {
  static GameInfo_t *field_info = NULL;

  if (figure_info != NULL) field_info = create_field_info(figure_info);

  return field_info;
}

/**
 * @brief Функция создает структуру с начальными данными для поля и статистики.
 * @param figure_info Принимает указатель на структуру фигуры для заполнения
 * массива будущей фигуры.
 * @return GameInfo_t Возвращает указатель на статичную структуру.
 */
GameInfo_t *create_field_info(Figureinfo_t *figure_info) {
  static GameInfo_t field_info = {0};

  static int field[20][10];
  static int *field_pointer[20];

  for (int i = 0; i < 20; i++) field_pointer[i] = field[i];

  field_info.field = field_pointer;

  static int next[MAX_FIGURE_SIZE][MAX_FIGURE_SIZE];

  static int *next_pointer[MAX_FIGURE_SIZE];
  for (int i = 0; i < MAX_FIGURE_SIZE; i++) next_pointer[i] = next[i];

  field_info.next = next_pointer;

  reset_field_info(&field_info, figure_info);

  return &field_info;
}

/**
 * @brief  Функция возвращает начальные данные по игре.
 */
void reset_field_info(GameInfo_t *field_info, Figureinfo_t *figure_info) {
  for (int y = 0; y < 20; y++)
    for (int x = 0; x < 10; x++) field_info->field[y][x] = 0;

  for (int y = 0; y < MAX_FIGURE_SIZE; y++)
    for (int x = 0; x < MAX_FIGURE_SIZE; x++) field_info->next[y][x] = 0;

  for (int i = 0; i < BLOCKS; i++) {
    int y = 1 + get_block_coord(figure_info->next_figure_type, 0, i, 0);
    int x = 2 + get_block_coord(figure_info->next_figure_type, 0, i, 1);
    field_info->next[y][x] = figure_info->next_figure_color;
  }
  field_info->score = 0;
  field_info->high_score = 0;
  hi_score(field_info);
  field_info->level = 1;
  //скорость в наносекундах
  field_info->speed = ((11 - field_info->level) * 50);
  field_info->pause = START;
}

/**
 * @brief Функция удаления или заполнения матрицы по положению фигуры.
 * @param prms Указатель на структуру со всеми данными по игре.
 * @param param Режим работы функции: 0 - удаляет фигуру, 1 - заполняет матрицу
 * по текущему положению фигуры.
 */
void clear_or_draw_position(Params_t *prms, bool param) {
  for (int i = 0; i < BLOCKS; i++) {
    int y = prms->figureinfo->y +
            get_block_coord(prms->figureinfo->figure_type,
                            prms->figureinfo->figure_state, i, 0);
    int x = prms->figureinfo->x +
            get_block_coord(prms->figureinfo->figure_type,
                            prms->figureinfo->figure_state, i, 1);
    if (y < 0) continue;
    prms->gameinfo->field[y][x] = (param) ? prms->figureinfo->figure_color : 0;
  }
}

/**
 * @brief Функция проверки истечения времени для движения вниз.
 * @param prms Указатель на структуру со всеми данными по игре.
 */
void chech_timer(Params_t *prms) {
  if (prms->gameinfo->pause == MOVING) {
    struct timespec current_time;
    timespec_get(&current_time, TIME_UTC);

    long long diff =
        (current_time.tv_sec * 1000000000 + current_time.tv_nsec) -
        (prms->start_time.tv_sec * 1000000000 + prms->start_time.tv_nsec);

    diff = (((double)diff) / 1000000.0);

    if (diff >= prms->gameinfo->speed) prms->gameinfo->pause = SHIFTING;
  }
}

/**
 * @brief Функция для записи/чтения рекорда.
 * @param gameinfo Указатель на структуру с данными статистики по игре.
 */
void hi_score(GameInfo_t *gameinfo) {
  FILE *file;

  if (gameinfo->high_score >= gameinfo->score) {
    file = fopen("hi-score-tetris.txt", "r");
    if (file) {
      if (fscanf(file, "%d", &gameinfo->high_score) < 0) exit(0);
      fclose(file);
    } else
      gameinfo->high_score = 0;

  } else {
    file = fopen("hi-score-tetris.txt", "w");
    fprintf(file, "%d", gameinfo->score);
    fclose(file);
  }
}

/**
 * @brief Функция обновления состояния игры.
 * @return GameInfo_t Возвращает структуру с актуальными данными игры.
 */
GameInfo_t updateCurrentState() {
  GameInfo_t *gameinfo = get_field_info(NULL);

  return *gameinfo;
}

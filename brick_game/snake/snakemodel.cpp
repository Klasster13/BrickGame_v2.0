/**
 * @file
 * @brief Файл с методами класса SnakeModel
 */

#include "snakemodel.h"

namespace s21 {

/**
 * @brief Базовый конструктор модели
 */
SnakeModel ::SnakeModel() : SnakeModel(false) {}

/**
 * @brief Конструктор модели
 */
SnakeModel ::SnakeModel(bool value) {
  field.resize(20);
  for (size_t i = 0; i < 20; i++) field[i].resize(10);

  for (size_t i = 0; i < 20; i++)
    for (size_t j = 0; j < 10; j++) field[i][j] = 0;

  next = nullptr;
  score = 0;
  get_hi_score_from_file();
  level = 1;
  speed = (SPEED - level) * 10;
  state = START;
  start_time = 0;
  apple.first = 0;
  apple.second = 0;
  length = 4;
  block_new_dir = false;
  debug = value;
}

/**
 * @brief Деструктор модели
 */
SnakeModel ::~SnakeModel() { save_hi_score_in_file(); }

/**
 * @brief Метод генерации новых координат
 * @param Координаты тела змейки
 */
void SnakeModel::new_apple_coord() {
  srand(time(NULL));

  std::pair<int, int> free_cell[200] = {{0, 0}};
  int count = 0;

  for (int i = 0; i < 20; i++)
    for (int j = 0; j < 10; j++)
      if (field[i][j] == 0) free_cell[count++] = {i, j};

  apple = free_cell[rand() % count];
}

/**
 * @brief Метод конечного автомата
 * @param action Нажатие игрока
 */
void SnakeModel ::fsm(const UserAction_t &action) {
  switch (state) {
    case START:
      start(action);
      break;
    case SPAWN:
      spawn();
      break;
    case MOVING:
      moving(action);
      break;
    case SHIFTING:
      shifting();
      break;
    case COLLIDE:
      eat_apple();
      break;
    case PAUSE:
      pause_game(action);
      break;
    case GAMEOVER:
    case WINNER:
    case EXIT_STATE:
      end_game(action);
      break;
    default:
      break;
  }
}

/**
 * @brief Метод засекания времени таймера
 */
void SnakeModel::set_time() {
  if (debug) return;

  start_time = std::chrono::duration_cast<std::chrono::milliseconds>(
                   std::chrono::system_clock::now().time_since_epoch())
                   .count();
}

/**
 * @brief Метод изменения направления движения змейки
 * @param action Нажатие пользователя
 */
void SnakeModel::set_direction(const UserAction_t action) {
  if (block_new_dir) return;

  if ((direction == Direction_t::Left || direction == Direction_t::Right) &&
      (action == Up || action == Down)) {
    direction = (action == Up) ? Direction_t::Up : Direction_t::Down;
    block_new_dir = true;
  } else if ((direction == Direction_t::Up || direction == Direction_t::Down) &&
             (action == Left || action == Right)) {
    direction = (action == Left) ? Direction_t::Left : Direction_t::Right;
    block_new_dir = true;
  }
}

/**
 * @brief Метод проверки совпадения направления движения змейки и нажатия
 * пользователя для ускорения
 * @param action Нажатие пользователя
 */
bool SnakeModel::same_direction(const UserAction_t action) {
  if (action == Up && direction == Direction_t::Up)
    return true;
  else if (action == Down && direction == Direction_t::Down)
    return true;
  else if (action == Left && direction == Direction_t::Left)
    return true;
  else if (action == Right && direction == Direction_t::Right)
    return true;

  return false;
}

/**
 * @brief Метод проверки столкновения змейки при движении вперед
 * @param Координаты яблока
 * @return Возвращает состояние игры
 */
void SnakeModel::collide() {
  std::pair<int, int> head = snake.front();

  if (direction == Direction_t::Up)
    head.first--;
  else if (direction == Direction_t::Down)
    head.first++;
  else if (direction == Direction_t::Left)
    head.second--;
  else if (direction == Direction_t::Right)
    head.second++;

  if (head.first < 0 || head.first >= 20 || head.second < 0 ||
      head.second >= 10)
    state = GAMEOVER;
  else if (apple.first == head.first && apple.second == head.second)
    state = COLLIDE;
  else
    for (auto part : snake)
      if (part == head)
        state = GAMEOVER;
      else
        state = SHIFTING;
}

/**
 * @brief Метод движения вперед
 */
void SnakeModel::move_forward() {
  std::pair<int, int> head = snake.front();
  snake.splice(snake.begin(), snake, --(snake.end()));

  if (direction == Direction_t::Up)
    head = {head.first - 1, head.second};
  else if (direction == Direction_t::Down)
    head = {head.first + 1, head.second};
  else if (direction == Direction_t::Left)
    head = {head.first, head.second - 1};
  else if (direction == Direction_t::Right)
    head = {head.first, head.second + 1};

  snake.front() = head;
  block_new_dir = false;
}

/**
 * @brief Метод возвращения змейки в начальное состояние
 */
void SnakeModel::reset_snake() {
  snake.clear();
  init_snake();
}

/**
 * @brief Метод инициализации начального состояния змейки
 */
void SnakeModel::init_snake() {
  srand(time(NULL));
  length = 4;
  direction = debug ? Direction_t::Up : (Direction_t)(rand() % 4);
  block_new_dir = false;
  std::pair<int, int> coord = {10, 5};
  snake.push_back(coord);

  for (size_t i = 0; i < length - 1; i++) {
    if (direction == Direction_t::Up) {
      coord.first++;
      snake.push_back(coord);
    } else if (direction == Direction_t::Down) {
      coord.first--;
      snake.push_back(coord);
    } else if (direction == Direction_t::Left) {
      coord.second++;
      snake.push_back(coord);
    } else if (direction == Direction_t::Right) {
      coord.second--;
      snake.push_back(coord);
    }
  }
}
/**
 * @brief Метод заполнения игрового поля координатами тела змейки
 * @param body Координаты тела змейки
 */
void SnakeModel::draw_snake() {
  for (auto part : snake) field[part.first][part.second] = 1;

  field[snake.front().first][snake.front().second] = 3;
}

/**
 * @brief Метод добавления яблока на игровое поле
 * @param apple Координаты яблока
 */
void SnakeModel::draw_apple() { field[apple.first][apple.second] = 5; }

/**
 * @brief Метод удаления части змейки с игрового поля по координатам
 * @param coord Координаты части тела змейки
 */
void SnakeModel::erase_tail() {
  field[snake.back().first][snake.back().second] = 0;
}

/**
 * @brief Метод проверки таймера движения вперед
 */
bool SnakeModel::check_timer() {
  if (debug) return false;

  auto current_time = std::chrono::duration_cast<std::chrono::milliseconds>(
                          std::chrono::system_clock::now().time_since_epoch())
                          .count();

  return current_time - start_time >= speed;
}

/**
 * @brief Метод получения рекорда из файла
 */
void SnakeModel::get_hi_score_from_file() {
  FILE *file;

  file = fopen("hi-score-snake.txt", "r");
  if (file) {
    if (fscanf(file, "%d", &high_score) < 0) std::exit(0);
    fclose(file);
  } else
    high_score = 0;
}

/**
 * @brief Метод записи рекорда в файл
 */
void SnakeModel::save_hi_score_in_file() {
  if (score > high_score) {
    FILE *file;
    file = fopen("hi-score-snake.txt", "w");
    fprintf(file, "%d", score);
    fclose(file);
  }
}

/**
 * @brief Метод возвращения игры в начальное состояние
 */
void SnakeModel::reset_game() {
  for (size_t i = 0; i < 20; i++)
    for (size_t j = 0; j < 10; j++) field[i][j] = 0;

  score = 0;
  get_hi_score_from_file();
  level = 1;
  // скорость в миллисекундах
  speed = (SPEED - level) * 10;
  state = START;
  start_time = 0;
}

/**
 * @brief Метод для состояния START
 * @param action Нажатие пользователя
 */
void SnakeModel::start(const UserAction_t &action) {
  if (action == Start) {
    state = SPAWN;
  } else if (action == Terminate)
    state = EXIT_STATE;
}

/**
 * @brief Метод для состояния SPAWN
 */
void SnakeModel::spawn() {
  reset_snake();
  new_apple_coord();
  draw_snake();
  draw_apple();
  state = MOVING;
  set_time();
}

/**
 * @brief Метод для состояния MOVING
 * @param action Нажатие пользователя
 */
void SnakeModel::moving(const UserAction_t &action) {
  if (action == Action || check_timer() || same_direction(action))
    state = SHIFTING;
  else if (action == Pause)
    state = PAUSE;
  else if (action == Terminate)
    state = EXIT_STATE;
  else if (action == Start)
    end_game(action);
  else if (action == Left || action == Right || action == Up || action == Down)
    set_direction(action);
}

/**
 * @brief Метод для состояния SHIFTING
 */
void SnakeModel::shifting() {
  collide();

  if (state == SHIFTING) {
    erase_tail();
    move_forward();
    draw_snake();
    state = MOVING;
    set_time();
  }
}

/**
 * @brief Метод для состояния COLLIDE
 */
void SnakeModel::eat_apple() {
  ++score;
  if (level >= 10)
    level = 10;
  else
    level = 1 + score / 5;

  speed = (SPEED - level) * 10;

  if (++length == 200) {
    state = WINNER;
    return;
  }
  snake.push_front(apple);
  block_new_dir = false;
  draw_snake();
  new_apple_coord();
  draw_apple();
  state = MOVING;
  set_time();
}

/**
 * @brief Метод для состояния PAUSE
 * @param action Нажатие пользователя
 */
void SnakeModel::pause_game(const UserAction_t &action) {
  if (action != (UserAction_t)-1) {
    state = (action == Terminate) ? EXIT_STATE : MOVING;
    set_time();
  }
}

/**
 * @brief Метод для состояния GAMEOVER/WINNER/EXIT_STATE
 * @param action Нажатие пользователя
 */
void SnakeModel::end_game(const UserAction_t &action) {
  if (action != (UserAction_t)-1 && state != EXIT_STATE) {
    reset_game();
    state = START;
  }
  save_hi_score_in_file();
}

/**
 * @brief Метод обработки нажатых пользователем клавиш
 * @param action Нажатие пользователя
 * @param hold Параметр длительного зажатия клавиши
 */
void SnakeModel::userInput(UserAction_t action, bool hold) {
  fsm(action);
  (void)hold;
}

/**
 * @brief Метод обновления состояния игры.
 * @return Возвращает актуальную структуру с данными по игре
 */
GameInfo_t SnakeModel::updateCurrentState() {
  static GameInfo_t gameinfo = {NULL, NULL, 0, 0, 0, 0, 0};

  if (gameinfo.field == NULL) {
    static int field[20][10];
    static int *field_pointer[20];

    for (size_t i = 0; i < 20; i++) field_pointer[i] = field[i];

    gameinfo.field = field_pointer;
  }

  for (size_t y = 0; y < 20; y++)
    for (size_t x = 0; x < 10; x++) gameinfo.field[y][x] = field[y][x];

  gameinfo.next = nullptr;
  gameinfo.score = score;
  gameinfo.high_score = high_score;
  gameinfo.level = level;
  gameinfo.speed = speed;
  gameinfo.pause = state;

  return gameinfo;
}

std::pair<int, int> SnakeModel::get_head_coord() { return snake.front(); }

int SnakeModel::get_game_state() { return state; }
}  // namespace s21

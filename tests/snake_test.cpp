#include "test_main.h"

void run(s21::SnakeModel *model);

TEST_F(SnakeTest, BasicConstructor) {
  s21::SnakeModel snake;
  GameInfo_t info = snake.updateCurrentState();

  EXPECT_EQ(info.score, 0);
  EXPECT_EQ(info.speed, (SPEED - info.level) * 10);
  EXPECT_EQ(info.level, 1);
  EXPECT_EQ(info.pause, START);
}

TEST_F(SnakeTest, Basic) {
  GameInfo_t info = model->updateCurrentState();
  EXPECT_EQ(info.score, 0);
  EXPECT_EQ(info.speed, (SPEED - info.level) * 10);
  EXPECT_EQ(info.level, 1);
  EXPECT_EQ(info.pause, START);
}

TEST_F(SnakeTest, FSM_start_1) {
  model->userInput(Start, false);
  GameInfo_t info = model->updateCurrentState();
  EXPECT_EQ(info.pause, SPAWN);
}

TEST_F(SnakeTest, FSM_start_2) {
  model->userInput(Terminate, false);
  GameInfo_t info = model->updateCurrentState();
  EXPECT_EQ(info.pause, EXIT_STATE);
}

TEST_F(SnakeTest, FSM_start_3) {
  model->userInput(Left, false);
  GameInfo_t info = model->updateCurrentState();
  EXPECT_EQ(info.pause, START);
}

TEST_F(SnakeTest, FSM_spawn) {
  model->userInput(Start, false);
  model->userInput((UserAction_t)-1, false);
  GameInfo_t info = model->updateCurrentState();
  EXPECT_EQ(info.pause, MOVING);
}

TEST_F(SnakeTest, FSM_moving_1) {
  model->userInput(Start, false);
  model->userInput((UserAction_t)-1, false);
  model->userInput((UserAction_t)-1, false);
  GameInfo_t info = model->updateCurrentState();
  EXPECT_EQ(info.pause, MOVING);
}

TEST_F(SnakeTest, FSM_moving_2) {
  model->userInput(Start, false);
  model->userInput((UserAction_t)-1, false);
  model->userInput((UserAction_t)-1, false);
  model->userInput((UserAction_t)-1, false);
  GameInfo_t info = model->updateCurrentState();
  EXPECT_EQ(info.pause, MOVING);
}

TEST_F(SnakeTest, FSM_moving_3) {
  model->userInput(Start, false);
  model->userInput(Left, false);
  model->userInput((UserAction_t)-1, false);
  model->userInput(Up, false);
  model->userInput((UserAction_t)-1, false);
  GameInfo_t info = model->updateCurrentState();
  EXPECT_EQ(info.pause, MOVING);
}

TEST_F(SnakeTest, FSM_moving_4) {
  s21::SnakeModel snake;
  snake.userInput(Start, false);
  snake.userInput((UserAction_t)-1, false);
  snake.userInput(Pause, false);
  snake.userInput((UserAction_t)-1, false);
  snake.userInput(Terminate, false);
  snake.userInput((UserAction_t)-1, false);
  GameInfo_t info = snake.updateCurrentState();
  EXPECT_EQ(info.pause, EXIT_STATE);
}

TEST_F(SnakeTest, FSM_moving_5) {
  model->userInput(Start, false);
  model->userInput((UserAction_t)-1, false);
  model->userInput(Right, false);
  model->userInput(Down, false);
  model->userInput(Down, false);
  model->userInput(Right, false);
  model->userInput(Right, false);
  GameInfo_t info = model->updateCurrentState();

  EXPECT_EQ(info.pause, MOVING);
}

TEST_F(SnakeTest, FSM_moving_6) {
  model->userInput(Start, false);
  model->userInput((UserAction_t)-1, false);
  model->userInput(Right, false);
  model->userInput(Right, false);
  model->userInput(Action, false);
  model->userInput(Action, false);
  model->userInput((UserAction_t)-1, false);
  GameInfo_t info = model->updateCurrentState();

  EXPECT_EQ(info.pause, MOVING);
}

TEST_F(SnakeTest, FSM_moving_7) {
  model->userInput(Start, false);
  model->userInput((UserAction_t)-1, false);
  model->userInput(Another, false);
  model->userInput((UserAction_t)-1, false);
  model->userInput(Terminate, false);
  model->userInput((UserAction_t)-1, false);
  model->userInput((UserAction_t)-1, false);
  GameInfo_t info = model->updateCurrentState();

  EXPECT_EQ(info.pause, EXIT_STATE);
}

TEST_F(SnakeTest, FSM_gameover) {
  model->userInput(Start, false);
  model->userInput((UserAction_t)-1, false);
  for (int i = 0; i < 11; i++) model->userInput(Right, false);
  GameInfo_t info = model->updateCurrentState();

  EXPECT_EQ(info.pause, GAMEOVER);
}

TEST_F(SnakeTest, FSM_restart) {
  model->userInput(Start, false);
  model->userInput((UserAction_t)-1, false);
  for (int i = 0; i < 12; i++) model->userInput(Right, false);
  model->userInput((UserAction_t)-1, false);
  model->userInput(Start, false);
  model->userInput((UserAction_t)-1, false);

  GameInfo_t info = model->updateCurrentState();

  EXPECT_EQ(info.pause, MOVING);
}

TEST_F(SnakeTest, FSM_init_snake) {
  s21::SnakeModel snake;
  for (int i = 0; i < 40; i++) {
    snake.userInput(Start, false);
    snake.userInput((UserAction_t)-1, false);
  }
  GameInfo_t info = snake.updateCurrentState();
  EXPECT_EQ(info.pause, START);
}

TEST_F(SnakeTest, FullMove) {
  model->userInput(Start, false);
  model->userInput((UserAction_t)-1, false);

  run(model);

  GameInfo_t info = model->updateCurrentState();

  EXPECT_EQ(info.pause, WINNER);
  EXPECT_EQ(info.score, 196);
  EXPECT_EQ(info.level, 10);
}

void run(s21::SnakeModel *model) {
  while (model->get_game_state() != WINNER) {
    // вверх до конца
    while (model->get_head_coord().first != 0) {
      model->userInput(Up, false);
      if (model->get_game_state() == WINNER) return;
    }

    // вправо до конца
    while (model->get_head_coord().second != 9) {
      model->userInput(Right, false);
      if (model->get_game_state() == WINNER) return;
    }

    // начало S
    for (int i = 0; i < 5; i++) {
      // вниз до конца
      while (model->get_head_coord().first != 19) {
        model->userInput(Down, false);
        if (model->get_game_state() == WINNER) return;
      }

      // поворот вверх
      model->userInput(Left, false);
      model->userInput(Left, false);
      model->userInput((UserAction_t)-1, false);
      if (model->get_game_state() == WINNER) return;

      //  наверх до 1
      while (model->get_head_coord().first != 1) {
        model->userInput(Up, false);
        if (model->get_game_state() == WINNER) return;
      }
      if (i != 4) {
        model->userInput(Left, false);
        model->userInput(Left, false);
        model->userInput((UserAction_t)-1, false);
        if (model->get_game_state() == WINNER) return;
      }
    }
  }
}
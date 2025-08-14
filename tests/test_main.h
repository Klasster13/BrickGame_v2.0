#pragma once

#include <gtest/gtest.h>

#include "../brick_game/snake/snakemodel.h"

class SnakeTest : public ::testing::Test {
 protected:
  s21::SnakeModel *model;

  void SetUp() override { model = new s21::SnakeModel(true); }
  void TearDown() override { delete model; }
};
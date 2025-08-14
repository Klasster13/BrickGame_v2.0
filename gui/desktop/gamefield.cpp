/**
 * @file
 * @brief Файл с методами класса GameField
 */

#include "mainwindow.hpp"

/**
 * @brief Метод обновления данных
 * @param value Структура с актуальными данными игры
 */
void s21::GameField::set_info(GameInfo_t &value) {
  field = value.field;
  next = value.next;
  state = (GameState_t)value.pause;
};

/**
 * @brief Метод отрисовки полей и сообщений
 */
void s21::GameField::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  set_painter(&painter);

  print_field(&painter);
  print_next(&painter);

  if (state == START || state == PAUSE || state == GAMEOVER || state == WINNER)
    print_message(&painter);

  event->accept();
}

/**
 * @brief Метод настройки рисовальщика
 */
void s21::GameField::set_painter(QPainter *painter) {
  QPen pen;
  pen.setWidth(2);
  painter->setPen(pen);
  painter->setOpacity(0.1);
  painter->drawRect(3, 3, 203, 403);
  //   painter->drawRect(210, 282, 84, 44);
  painter->setFont(QFont("Arial", 16));
  painter->setOpacity(1);
}

/**
 * @brief Метод выбора цвета
 */
void s21::GameField::set_color(int value, QPainter *painter) {
  painter->setOpacity(1);
  if (value == 1)
    painter->setPen(QPen(Qt::black));
  else if (value == 2)
    painter->setPen(QPen(Qt::cyan));
  else if (value == 3)
    painter->setPen(QPen(Qt::green));
  else if (value == 4)
    painter->setPen(QPen(Qt::magenta));
  else if (value == 5)
    painter->setPen(QPen(Qt::red));
  else if (value == 6)
    painter->setPen(QPen(Qt::blue));
  else if (value == 7)
    painter->setPen(QPen(Qt::yellow));
  else {
    painter->setPen(QPen(Qt::black));
    painter->setOpacity(0.1);
  }
}

/**
 * @brief Метод отрисовки поля
 */
void s21::GameField::print_field(QPainter *painter) {
  if (field) {
    for (int i = 0; i < 20; ++i)
      for (int j = 0; j < 10; ++j) {
        set_color(field[i][j], painter);
        painter->drawText(j * 20 + 4, i * 20 + 22, "▣");
      }
  } else {
    painter->setPen(QPen(Qt::black));
    painter->setOpacity(0.1);
    for (int i = 0; i < 20; ++i)
      for (int j = 0; j < 10; ++j)
        painter->drawText(j * 20 + 4, i * 20 + 22, "▣");
  }
  painter->setOpacity(1);
}

/**
 * @brief Метод отрисовки следующей фигуры
 */
void s21::GameField::print_next(QPainter *painter) {
  if (next) {
    for (int i = 1; i < 3; ++i)
      for (int j = 0; j < 4; ++j) {
        set_color(next[i][j], painter);
        painter->drawText(j * 20 + 212, (i - 1) * 20 + 302, "▣");
      }
  } else {
    painter->setPen(QPen(Qt::black));
    painter->setOpacity(0.1);
    for (int i = 0; i < 2; ++i)
      for (int j = 0; j < 4; ++j)
        painter->drawText(j * 20 + 212, i * 20 + 302, "▣");
  }
  painter->setOpacity(1);
}

/**
 * @brief Метод вывода сообщения
 */
void s21::GameField::print_message(QPainter *painter) {
  painter->setPen(QPen(Qt::black));

  if (state == START) {
    painter->fillRect(6, 186, 198, 18, QBrush(QColor::fromRgb(158, 173, 134)));
    painter->drawText(30, 202, "PRESS ENTER");
  } else {
    painter->fillRect(6, 186, 198, 40, QBrush(QColor::fromRgb(158, 173, 134)));
    painter->drawText(21, 222, "PRESS ANY KEY");
    if (state == PAUSE)
      painter->drawText(70, 202, "PAUSE");
    else if (state == GAMEOVER)
      painter->drawText(44, 202, "GAMEOVER");
    else if (state == WINNER)
      painter->drawText(68, 202, "WINNER!");
  }
}

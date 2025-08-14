/**
 * @file
 * @brief Файл с методами класса Window
 */

#include "mainwindow.hpp"

#include "./ui_mainwindow.h"

/**
 * @brief Конструктор класса
 * @param value Указатель на контроллер
 */
s21::Window::Window(s21::Controller *value)
    : QMainWindow(nullptr), ui(new Ui::MainWindow), ctrl(value) {
  ui->setupUi(this);
  setFixedSize(317, 623);

  gamefield = new s21::GameField(ui->gamefield);
  gamefield->setGeometry(0, 0, 400, 600);

  connect(ui->pushButton_up, SIGNAL(clicked()), this, SLOT(screen_button()));
  connect(ui->pushButton_action, SIGNAL(clicked()), this,
          SLOT(screen_button()));
  connect(ui->pushButton_down, SIGNAL(clicked()), this, SLOT(screen_button()));
  connect(ui->pushButton_left, SIGNAL(clicked()), this, SLOT(screen_button()));
  connect(ui->pushButton_right, SIGNAL(clicked()), this, SLOT(screen_button()));
  connect(ui->pushButton_start, SIGNAL(clicked()), this, SLOT(screen_button()));
  connect(ui->pushButton_pause, SIGNAL(clicked()), this, SLOT(screen_button()));

  GameInfo_t info = ctrl->update((UserAction_t)-1, false);
  update(info);
}

/**
 * @brief Деструктор класса
 */
s21::Window::~Window() {
  delete ui;
  delete gamefield;
}

/**
 * @brief Метод обновления представления, срабатывает по таймеру
 */
void s21::Window::timerEvent(QTimerEvent *event) {
  GameInfo_t info = ctrl->update((UserAction_t)-1, false);
  update(info);
  event->accept();
}

/**
 * @brief Метод вызывающий при нажатии клавиши
 */
void s21::Window::keyPressEvent(QKeyEvent *event) {
  UserAction_t action = (UserAction_t)-1;
  int id = 0;

  switch (event->key()) {
    case Qt::Key_Return:
      action = Start;
      break;
    case Qt::Key_P:
      action = Pause;пиу
      break;
    case Qt::Key_Q:
      action = Terminate;
      break;
    case Qt::Key_Left:
      action = Left;
      break;
    case Qt::Key_Right:
      action = Right;
      break;
    case Qt::Key_Up:
      action = Up;
      break;
    case Qt::Key_Down:
      action = Down;
      break;
    case Qt::Key_Space:
      action = Action;
      break;
    default:
      action = Another;
      break;
  }

  GameInfo_t info = ctrl->update(action, false);
  update(info);

  if (info.pause == SPAWN || info.pause == MOVING)
    id = startTimer(2);
  else if (info.pause == PAUSE || info.pause == GAMEOVER ||
           info.pause == WINNER)
    killTimer(id);
  else if (info.pause == PAUSE && action != (UserAction_t)-1)
    id = startTimer(2);

  if (action == Terminate) {
    killTimer(id);
    close();
  }
  event->accept();
}

/**
 * @brief Метод обработки десктопных клавиш
 */
void s21::Window::screen_button() {
  QPushButton *buttonSender = qobject_cast<QPushButton *>(sender());
  Qt::Key key;

  if (buttonSender == ui->pushButton_up)
    key = Qt::Key_Up;
  else if (buttonSender == ui->pushButton_down)
    key = Qt::Key_Down;
  else if (buttonSender == ui->pushButton_left)
    key = Qt::Key_Left;
  else if (buttonSender == ui->pushButton_right)
    key = Qt::Key_Right;
  else if (buttonSender == ui->pushButton_action)
    key = Qt::Key_Space;
  else if (buttonSender == ui->pushButton_start)
    key = Qt::Key_Return;
  else
    key = Qt::Key_P;

  QKeyEvent *event = new QKeyEvent(QEvent::KeyPress, key, Qt::NoModifier);
  keyPressEvent(event);
  delete event;
}

/**
 * @brief Метод обновления десктопного окна
 * @param value Структура с актуальными данными игры
 */
void s21::Window::update(GameInfo_t &value) {
  ui->level_number->display(value.level);
  ui->score_number->display(value.score);
  if (value.score >= value.high_score)
    ui->hi_score_number->display(value.score);
  else
    ui->hi_score_number->display(value.high_score);
  ui->speed_number->display(QString("%1").arg(value.speed / 1000.0, 0, 'f', 2));

  gamefield->set_info(value);
  gamefield->update();
}

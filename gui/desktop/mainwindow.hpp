/**
 * @file
 * @brief Заголовочный файл классов GameField и Window
 */

#pragma once

#include <QMainWindow>
#include <QApplication>
#include <QWidget>
#include <QFrame>
#include <QKeyEvent>
#include <QPainter>
#include <QTimer>

#include "../../components/controller.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

namespace s21
{

    /**
     * @brief Класс GameField
     */
    class GameField : public QWidget
    {
        Q_OBJECT
    public:
        GameField(QWidget *parent = nullptr) : QWidget(parent), field(nullptr), next(nullptr)
        {
            setFocusPolicy(Qt::StrongFocus);
        };

        void set_info(GameInfo_t &value);
        void paintEvent(QPaintEvent *event) override;

    protected:
        void print_message(QPainter *painter);

        void print_field(QPainter *painter);
        void print_next(QPainter *painter);
        void set_painter(QPainter *painter);
        void set_color(int value, QPainter *painter);

    private:
        int **field;       ///< Игровое поле
        int **next;        ///< Поле следующей фигуры
        GameState_t state; ///< Текущее состояние игры
    };

    /**
     * @brief Класс Window
     */
    class Window : public QMainWindow
    {
        Q_OBJECT

    public:
        Window(s21::Controller *value = nullptr);
        ~Window();
        void keyPressEvent(QKeyEvent *event) override;
        void timerEvent(QTimerEvent *event) override;
        void update(GameInfo_t &value);

    private slots:
        void screen_button();

    public:
        Ui::MainWindow *ui;        ///< Указатель на десктопное представление
        s21::GameField *gamefield; ///< Указатель на виджет для отрисовки
        s21::Controller *ctrl;     ///< Указатель на контроллер 
    };

}

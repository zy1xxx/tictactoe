#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<state.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    State game_state;
    QPixmap bg;
    QPixmap x_chess;
    QPixmap o_chess;
    int box_width=147;
    init_paint_obj();
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *event);
    void search_next_step(State &s, int depth);
    bool check_win();
};

#endif // MAINWINDOW_H

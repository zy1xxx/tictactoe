#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "state.h"
#include <QPainter>
#include <QMouseEvent>
#include "dialog.h"
#include<Qstring>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    game_state.type=1;//人先下
    ui->setupUi(this);
    init_paint_obj();
}

MainWindow::~MainWindow()
{
    delete ui;
}

MainWindow::init_paint_obj(){
    bg.load("../tictactoe/bg.png");
    o_chess.load("../tictactoe/o.png");
    x_chess.load("../tictactoe/x.png");
}

void MainWindow::paintEvent(QPaintEvent *){
    QPainter painter(this);
    painter.drawPixmap(0, 0,bg);
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            int box_in_width=box_width-20;
            int bias=10;
            if(game_state.board[i][j]==1){
                painter.drawPixmap(box_width*j+bias,box_width*i+bias,box_in_width,box_in_width,o_chess);
            }
            else if(game_state.board[i][j]==4){
                painter.drawPixmap(box_width*j+bias,box_width*i+bias,box_in_width,box_in_width,x_chess);
            }

        }

    }

}

void MainWindow::search_next_step(State &s,int depth){
    if (depth==0)
    {
        s.alpha=s.beta=s.get_value();
        return;
    }
    vector<State*> state_child=s.get_child_state();
    for(auto state_i : state_child){
        int tmp_depth=depth-1;
        search_next_step(*state_i,tmp_depth);
        if (s.type==0)//max
        {
            if (state_i->alpha>s.alpha)
            {
                s.alpha=state_i->alpha;
                s.next_pos=state_i->pos;
            }
            if (state_i->beta>s.alpha)
            {
                s.alpha=state_i->beta;
                s.next_pos=state_i->pos;
            }
        }
        else
        {
            if (state_i->alpha<s.beta)
            {
                s.beta=state_i->alpha;
                s.next_pos=state_i->pos;
            }
            if (state_i->beta<s.beta)
            {
                s.beta=state_i->beta;
                s.next_pos=state_i->pos;
            }
        }
        if (s.alpha>=s.beta)
        {
            for(auto i:state_child) delete i;
            return;
        }
    }
    for(auto i:state_child) delete i;
    return;
}
bool MainWindow::check_win(){

    if(game_state.is_win()!=0){
          Dialog show_r;
        if(game_state.is_win()==1){

           show_r.changeLabel("AI win!");

        }
        else if(game_state.is_win()==4){

            show_r.changeLabel("player win!");

        }
        else if(game_state.is_win()==8){

            show_r.changeLabel("no one win!");

        }

        if (show_r.exec()==QDialog::Accepted){
            game_state.reload();
            return true;
        }else{
            this->close();
            return true;
        }

    }
    return false;
 }
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    // 如果是鼠标左键按下

    if(event->button() == Qt::LeftButton)
   {
        if(game_state.type==0){
               return;
        }
          int x=event->pos().x();
          int y=event->pos().y();
          int i=y/box_width;
          int j=x/box_width;
          if (game_state.board[i][j]==0)
          {
              game_state.board[i][j]=4;
              game_state.type=0;
              update();
          }
          if(check_win()){
               return;
          }
          //AI
          State tmp;
          tmp=game_state;
          search_next_step(tmp,2);
          if (game_state.board[tmp.next_pos.x][tmp.next_pos.y]==0)
          {
             game_state.board[tmp.next_pos.x][tmp.next_pos.y]=1;
             game_state.type=1;
             update();
          }

          if(check_win()){
               return;
          }
   }
}

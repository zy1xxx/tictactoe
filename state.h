#ifndef STATE_H
#define STATE_H


#include<iostream>
#include<limits.h>
#include<vector>
using namespace std;

class Coords
{
public:
    int x;
    int y;
    Coords(){}
    Coords( const Coords &obj){
        x=obj.x;
        y=obj.y;
    }
    Coords(int x,int y){
        x=x;
        y=y;
    }

};

class State
{
public:
    int board[3][3];//0代表无棋子，1代表self（max层），4代表player（min层）
    int alpha=INT_MIN;
    int beta=INT_MAX;
    int type=1;//0代表max层，1代表min层
    Coords pos;
    Coords next_pos;
    State(){
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                board[i][j]=0;
            }
        }
    }
    void reload(){
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                board[i][j]=0;
            }
        }
        type=1;
    }
    State(const State &obj){
        memcpy(*board,*obj.board,sizeof(int)*9);
        alpha=obj.alpha;
        beta=obj.beta;

    }
    int get_value(){
        int AI_value=0;
        int player_value=0;
        vector<int> line_v;
        for (int i = 0; i < 3; i++)//
        {
            int row_value=board[i][0]+board[i][1]+board[i][2];
            int col_value=board[0][i]+board[1][i]+board[2][i];
            line_v.push_back(row_value);
            line_v.push_back(col_value);

        }
        int oblique_left=board[0][0]+board[1][1]+board[2][2];
        int oblique_right=board[0][2]+board[1][1]+board[2][0];
        line_v.push_back(oblique_left);
        line_v.push_back(oblique_right);
        for(auto line_value : line_v){
            if (line_value==3)
            {
                AI_value+=100;
            }
            else if (line_value==2)
            {
                AI_value+=10;
            }
            else if(line_value==1)
            {
                AI_value+=3;
            }
            else if(line_value==4)
            {
                player_value+=3;
            }
            else if(line_value==8)
            {
                player_value+=10;
            }
            else if(line_value==12)
            {
                player_value+=100;
            }
        }
        return AI_value-player_value;
    }
    vector<State*> get_child_state(){
        vector<State*> child_state;
        for (int i = 0; i < 9; i++)
        {
            if(board[i/3][i%3]==0)
            {

                State *tmp=new State(*this);

                if (type==0){
                    tmp->board[i/3][i%3]=1;
                    tmp->type=1;
                }
                else{
                    tmp->board[i/3][i%3]=4;
                    tmp->type=0;
                }
                tmp->pos.x=i/3;
                tmp->pos.y=i%3;
                child_state.push_back(tmp);
            }
        }
        return child_state;
    }
    int is_win(){
        vector<int> line_v;

        for (int i = 0; i < 3; i++)//
        {
            int row_value=board[i][0]+board[i][1]+board[i][2];
            int col_value=board[0][i]+board[1][i]+board[2][i];
            line_v.push_back(row_value);
            line_v.push_back(col_value);

        }
        int oblique_left=board[0][0]+board[1][1]+board[2][2];
        int oblique_right=board[0][2]+board[1][1]+board[2][0];
        line_v.push_back(oblique_left);
        line_v.push_back(oblique_right);
        for(auto line_value : line_v){
            if (line_value==3){
                return 1;
              }
            else if(line_value==12){
                return 4;
            }
        }


        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(board[i][j]==0){
                    return 0;
                }
            }
        }
        return 8;
    }
    void clear_a_b(){
        alpha=INT_MIN;
        beta=INT_MAX;
    }
    void print(){
        cout<<"-----------------\n";
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                cout<<board[i][j]<<" ";
            }
            cout<<"\n";
        }
        cout<<"-----------------\n";
    }
};


#endif // STATE_H



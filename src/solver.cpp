#include<iostream>
#include<string>
#include<vector>

#include "game.hpp"

using namespace std;

string direction, dir, pred;
int max_score = 0, sum = 0;

void next_board(vector<vector<int> > current, int g);
int tile_count(vector<vector<int> > board);
int max_tile(vector<vector<int> > board, int x);
int right_most(vector<vector<int> > board);
bool pow_line(vector<vector<int> > board);

string solver(){
    vector<vector<int> > board = game::get_board();
    vector<vector<int> > copy(4, vector<int>(4, 0));
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            copy[i][j] = board[i][j];
        }
    }

    max_score = 0;
    if(tile_count(copy) <= 5){
        if(game::can_right(copy)){
            return "d";
        } else if(game::can_down(copy)){
            return "s";
        } else if(game::can_up(copy)){
            return "w";
        } else if(game::can_left(copy)){
            return "a";
        }
    } else {
        pred = direction;
        if(!game::can_right(copy) && !game::can_down(copy) && !game::can_up(copy))direction = "a";
        else next_board(copy, 1);
    }
    if(pred == "w" && (tile_count(copy) <= 8 || right_most(copy) != 4))direction = "s";
    else if(pred == "a")direction = "d";
    return direction;
}

void next_board(vector<vector<int> > current, int g){
    if(g == 3){
        if(sum > max_score){
            max_score = sum;
            direction = dir;
        }
        return;
    }
    vector<vector<vector<int> > > forward(4, vector<vector<int> >(4, vector<int>(4)));
    for(int i = 0; i < 4; i++){
        forward[i] = current;
    }
    if(game::can_right(current)){
        if(g == 1){
            dir = "d";
        }
        if(tile_count(forward[0]) < 8)game::generate_num(forward[0]);
        game::right(forward[0]);
        int tmp = game::get_add();
        if(g == 1)tmp += 128;
        if(max_tile(forward[0], 3) == forward[0][3][3])tmp += 128;
        sum += tmp;
        next_board(forward[0], g+1);
        sum -= tmp;
    }
    if(game::can_down(current)){
        if(g == 1){
            dir = "s";
        }
        if(tile_count(forward[1]) < 8)game::generate_num(forward[1]);
        game::down(forward[1]);
        int tmp = game::get_add();
        if(g == 1)tmp += 128;
        if(max_tile(forward[1], 3) == forward[1][3][3])tmp += 128;
        sum += tmp;
        next_board(forward[1], g+1);
        sum -= tmp;
    }
    if(game::can_up(current)){
        if(g == 1){
            dir = "w";
        }
        if(tile_count(forward[2]) < 8)game::generate_num(forward[2]);
        game::up(forward[2]);
        int tmp = game::get_add();
        if(g == 1)tmp += 128;
        if(max_tile(forward[2], 3) == forward[2][3][3])tmp += 128;
        sum += tmp;
        next_board(forward[2], g+1);
        sum -= tmp;
    }
    /*if(game::can_left(current)){
        if(g == 1){
            dir = "a";
        }
        game::left(forward[3]);
        int tmp = game::get_add();
        sum += tmp;
        next_board(forward[3], g+1);
        sum -= tmp;
    }*/
}

int tile_count(vector<vector<int> > board){
    int cnt = 0;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if(board[i][j] != 0)cnt++;
        }
    }
    return cnt;
}

int max_tile(vector<vector<int> > board, int x){
    int ans = 0;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j <= x; j++){
            if(board[i][j] >= ans)ans = board[i][j];
        }
    }
    return ans;
}

int right_most(vector<vector<int> > board){
    int ans = 0;
    for(int i = 0; i < 4; i++){
        if(board[i][3] != 0)ans++;
    }
    return ans;
}

bool pow_line(vector<vector<int> > board){
    for(int i = 3; i >= 1; i--){
        if(board[i][3] > board[i-1][3] && board[i][3] != 0 && board[i-1][3] != 0)continue;
        else return false;
    }
    return true;
}

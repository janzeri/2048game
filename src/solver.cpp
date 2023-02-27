#include<iostream>
#include<string>
#include<cstring>
#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<iomanip>

#include <stack>
#include <vector>

#include "game.hpp"

using namespace std;

string solve_all(){
    vector<vector<int> > copy = game::get_board();

    if(game::can_right(copy)){
        return "d";
    } else if(game::can_down(copy)){
        return "s";
    } else if(game::can_up(copy)){
        return "w";
    } else {
        return "a";
    }
}
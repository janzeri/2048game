#include<iostream>
#include<string>
#include<cstring>
#include<ctime>
#include<iomanip>
#include<unistd.h>
#include<stack>
#include<vector>

#include "solver.hpp"
#include "myconio.h"

#define RATIO 7 //2の生成率
#define NUM_OF_DATA 50

using namespace std;

bool collect = false;
vector<vector<int> > board(4, vector<int>(4, 0));
int add = 0;
int score;

class game{
	stack<int> score_stack;
	
	public:
    void menu();
	static vector<vector<int> > get_board();
	static int get_add();
	static bool can_up(vector<vector<int> > &board);
	static bool can_down(vector<vector<int> > &board);
	static bool can_left(vector<vector<int> > &board);
	static bool can_right(vector<vector<int> > &board);
	static void up(vector<vector<int> > &board);
	static void down(vector<vector<int> > &board);
	static void left(vector<vector<int> > &board);
	static void right(vector<vector<int> > &board);
	static void generate_num(vector<vector<int> > &board);

	private:
	string mode;
	void draw_board();
	void out_num(int y);
	bool board_notfull();

	void normal_play();
	void auto_play();
	void collect_data();

	void move();

	void end_game();
};

void game::menu(){
	score = 0;
	cout << "\t\t\t\t\t2048 GAME" << endl << endl;
	draw_board();
	cout << endl << "\t\t\tChoose mode :  N  - Normal play" << endl;
	cout << "\t\t\t\t       A  - Auto play (only watching)" << endl;
	cout << "\t\t\t\t       C  - Collect data (result only)" << endl;
	cout << "\t\t\tInput : ";
	cin >> mode;
	if(strcasecmp(mode.c_str(), "N") == 0){
		normal_play();
	} else if(strcasecmp(mode.c_str(), "A") == 0){
		auto_play();
	} else if(strcasecmp(mode.c_str(), "C") == 0){
		collect_data();
	} else {
		cout << endl <<  "\t\t\tError!  Input N or A or C" << endl;
		return;
	}
}

vector<vector<int> > game::get_board(){
	return board;
}

int game::get_add(){
	return add;
}

void game::draw_board(){
	cout << "\t\t\t\t+------+------+------+------+" << endl;
	cout << "\t\t\t\t|      |      |      |      |" << endl;
	out_num(0);
	cout << "|" << endl;
	cout << "\t\t\t\t|      |      |      |      |" << endl;
	cout << "\t\t\t\t+------+------+------+------+" << endl;
	cout << "\t\t\t\t|      |      |      |      |" << endl;
	out_num(1);
	cout << "|" << endl;
	cout << "\t\t\t\t|      |      |      |      |" << endl;
	cout << "\t\t\t\t+------+------+------+------+" << endl;
	cout << "\t\t\t\t|      |      |      |      |" << endl;
	out_num(2);
	cout << "|" << endl;
	cout << "\t\t\t\t|      |      |      |      |" << endl;
	cout << "\t\t\t\t+------+------+------+------+" << endl;
	cout << "\t\t\t\t|      |      |      |      |" << endl;
	out_num(3);
	cout << "|" << endl;
	cout << "\t\t\t\t|      |      |      |      |" << endl;
	cout << "\t\t\t\t+------+------+------+------+" << endl;
}

void game::out_num(int y){
	cout << "\t\t\t\t";
	for(int i = 0; i < 4; i++){
		if(board[y][i] == 0)cout << "|      ";
		else cout << "| " << setw(4) << board[y][i] << " ";
	}
}

void game::generate_num(vector<vector<int> > &board){
	int y = rand() % 4;
	int x = rand() % 4;
	if(board[y][x] != 0){
		generate_num(board);
	} else {
		int n = rand() % 10;
		if(n <= RATIO){
			board[y][x] = 2;
		} else {
			board[y][x] = 4;
		}
	}
}

bool game::board_notfull(){
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			if(board[i][j] == 0)return true;
		}
	}
	return false;
}

void game::normal_play(){
	while(board_notfull()){
		cout << endl << endl << "\t\t\t\t    -----Normal play-----" << endl << endl;
		cout << "\t\tSCORE : " << score << endl;
		generate_num(board);
		draw_board();
		if(!can_up(board) && !can_down(board) && !can_left(board) && !can_right(board))break;
		cout << endl << "\t\t\tW\t   ↑" << endl << endl;
		cout << "\t\t     A  S  D\t←  ↓  →\t\tH - Hint\tQ - Quit" << endl << endl;
		move();
		score += add;
	}
	end_game();
}

void game::auto_play(){
	string ans;
	score = 0;
	while(board_notfull()){
		generate_num(board);
		if(!collect){
			cout << endl << endl << "\t\t\t\t     -----Auto play-----" << endl << endl;
			cout << "\t\tscore : " << score << endl;
			draw_board();
		}
		if(!can_up(board) && !can_down(board) && !can_left(board) && can_right(board))break;
		ans = solver();
		if(ans == "w")up(board);
		else if(ans == "d")right(board);
		else if(ans == "s")down(board);
		else if(ans == "a")left(board);
		if(!collect)cout << "\t\t\t\t\tInput : " << ans << endl;
		if(!collect)usleep(500000);
		score += add;
	}
	if(collect)draw_board();
	end_game();
}

void game::collect_data(){
	int sum = 0;
	collect = true;
	for(int i = 0; i < NUM_OF_DATA; i++){
		auto_play();
		sum += score;
		score_stack.push(score);
		for(int j = 0; j < 4; j++){
			for(int k = 0; k < 4; k++){
				board[j][k] = 0;
			}
		}
	}
	cout << endl << "\t\t";
	for(int i = 1; i < NUM_OF_DATA+1; i++){
		cout << score_stack.top() << "  ";
		score_stack.pop();
		if(i%10 == 0)cout << endl << "\t\t";
	}
	cout << endl << "\t\tavarage score is " << sum/NUM_OF_DATA << endl;
}

void game::move(){
	int c = mygetch();
	if(c == 27){ //方向キーの入力に対応
		if(mygetch() == 91){
			c = mygetch();
			if(c == 65)c = 87;
			else if(c == 66)c = 83;
			else if(c == 67)c = 68;
			else c = 65;
		}
	}
	//cout << char(c) << endl;

	if(c == 87 || c == 119){
		if(can_up(board)){
			up(board);
		} else {
			move();
		}
	} else if(c == 65 || c == 97){
		if(can_left(board)){
			left(board);
		} else {
			move();
		}
	} else if(c == 83 || c == 115){
		if(can_down(board)){
			down(board);
		} else {
			move();
		}
	} else if(c == 68 || c == 100){
		if(can_right(board)){
			right(board);
		} else {
			move();
		}
	} else if(c == 72 || c == 104){
		cout << "\t\t\t\t\tHint : " << solver();
		move();
	} else if(c == 81 || c == 113){
		cout << endl << "\t\t\t\t----------------------------" << endl;
		cout << "\t\t\t\t----------- Quit -----------" << endl;
		cout << "\t\t\t\t----------------------------" << endl;
		exit(1);
	} else {
		move();
	}
}

bool game::can_up(vector<vector<int> > &board){
	for(int i = 3; i >= 0; i--){
		for(int j = 0; j < 4; j++){
			int tmp = board[i][j];
			if(tmp == 0)continue;
			for(int k = i-1; k >= 0; k--){
				if(board[k][j] == 0)return true;
				if(board[k][j] == tmp)return true;
				else break;
			}
		}
	}
	return false;
}

void game::up(vector<vector<int> > &board){
	add = 0;
	for(int j = 0; j < 4; j++){
		bool merge_flag = false;
		for(int i = 1; i < 4; i++){
			int y = -1;
			if(board[i][j] == 0)continue;
			for(int k = i-1; k >= 0; k--){
				if(board[k][j] == 0)y = k;
				else if(board[i][j] == board[k][j]){
					y = k;
					if(!merge_flag)merge_flag = true;
					else merge_flag = false;
					break;
				} else {
					merge_flag = false;
					break;
				}
			}
			if(y == -1)continue;
			if(merge_flag){
				board[y][j] *= 2;
				add += board[y][j];
				board[i][j] = 0;
			} else {
				board[y][j] = board[i][j];
				board[i][j] = 0;
			}
		}
	}
}

bool game::can_down(vector<vector<int> > &board){
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			int tmp = board[i][j];
			if(tmp == 0)continue;
			for(int k = i+1; k < 4; k++){
				if(board[k][j] == 0)return true;
				if(board[k][j] == tmp)return true;
				else break;
			}
		}
	}
	return false;
}

void game::down(vector<vector<int> > &board){
	add = 0;
	for(int j = 0; j < 4; j++){
		bool merge_flag = false;
		for(int i = 3; i >= 0; i--){
			int y = -1;
			if(board[i][j] == 0)continue;
			for(int k = i+1; k < 4; k++){
				if(board[k][j] == 0)y = k;
				else if(board[i][j] == board[k][j]){
					y = k;
					if(!merge_flag)merge_flag = true;
					else merge_flag = false;
					break;
				} else {
					merge_flag = false;
					break;
				}
			}
			if(y == -1)continue;
			if(merge_flag){
				board[y][j] *= 2;
				add += board[y][j];
				board[i][j] = 0;
			} else {
				board[y][j] = board[i][j];
				board[i][j] = 0;
			}
		}
	}
}

bool game::can_left(vector<vector<int> > &board){
	for(int j = 3; j >= 0; j--){
		for(int i = 0; i < 4; i++){
			int tmp = board[i][j];
			if(tmp == 0)continue;
			for(int k = j-1; k >= 0; k--){
				if(board[i][k] == 0)return true;
				if(board[i][k] == tmp)return true;
				else break;
			}
		}
	}
	return false;
}

void game::left(vector<vector<int> > &board){
	add = 0;
	for(int i = 0; i < 4; i++){
		bool merge_flag = false;
		for(int j = 1; j < 4; j++){
			int x = -1;
			if(board[i][j] == 0)continue;
			for(int k = j-1; k >= 0; k--){
				if(board[i][k] == 0)x = k;
				else if(board[i][j] == board[i][k]){
					x = k;
					if(!merge_flag)merge_flag = true;
					else merge_flag = false;
					break;
				} else {
					merge_flag = false;
					break;
				}
			}
			if(x == -1)continue;
			if(merge_flag){
				board[i][x] *= 2;
				add += board[i][x];
				board[i][j] = 0;
			} else {
				board[i][x] = board[i][j];
				board[i][j] = 0;
			}
		}
	}
}

bool game::can_right(vector<vector<int> > &board){
	for(int j = 0; j < 4; j++){
		for(int i = 0; i < 4; i++){
			int tmp = board[i][j];
			if(tmp == 0)continue;
			for(int k = j+1; k < 4; k++){
				if(board[i][k] == 0)return true;
				if(board[i][k] == tmp)return true;
				else break;
			}
		}
	}
	return false;
}

void game::right(vector<vector<int> > &board){
	add = 0;
	for(int i = 0; i < 4; i++){
		bool merge_flag = false;
		for(int j = 2; j >= 0; j--){
			int x = -1;
			if(board[i][j] == 0)continue;
			for(int k = j+1; k < 4; k++){
				if(board[i][k] == 0)x = k;
				else if(board[i][j] == board[i][k]){
					x = k;
					if(!merge_flag)merge_flag = true;
					else merge_flag = false;
					break;
				} else {
					merge_flag = false;
					break;
				}
			}
			if(x == -1)continue;
			if(merge_flag){
				board[i][x] *= 2;
				add += board[i][x];
				board[i][j] = 0;
			} else {
				board[i][x] = board[i][j];
				board[i][j] = 0;
			}
		}
	}
}

void game::end_game(){
	cout << endl << "\t\t\t\t----------------------------" << endl;
	cout << "\t\t\t\t-------- Game over! --------" << endl;
	cout << "\t\t\t\t----------------------------" << endl;
	cout << "\t\t\t\t\tYour score : " << score << endl;
}

int main(){
	game g;
	srand(time(NULL));
	g.menu();

	return 0;
}
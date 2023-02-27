#ifndef GAME_HPP
#define GAME_HPP

#include <vector>

class game{
    public:
    static int add;
    static std::vector<std::vector<int > > get_board();
    static int get_add();
    static void generate_num(std::vector<std::vector<int > > &board);

    static bool can_up(std::vector<std::vector<int > > &board);
	static bool can_down(std::vector<std::vector<int > > &board);
	static bool can_left(std::vector<std::vector<int > > &board);
	static bool can_right(std::vector<std::vector<int > > &board);
	static void up(std::vector<std::vector<int > > &board);
	static void down(std::vector<std::vector<int > > &board);
	static void left(std::vector<std::vector<int > > &board);
	static void right(std::vector<std::vector<int > > &board);
};

#endif
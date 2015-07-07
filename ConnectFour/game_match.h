#ifndef GAME_MATCH_H
#define GAME_MATCH_H



using namespace std;

const int min_dimensions = 4;
const int max_dimensions = 20;
const int fill_val = '\0';
const int default_width = 7;
const int default_height = 6;
const int default_tok_1 = '1';
const int default_tok_2 = '2';
const int default_rounds = 1;
const int default_is_connect_six = false;
const int default_is_ai_match = false;

//maintains a single match's state
class GameMatch
{
private:
    int width;
    int height;
    char grid[max_dimensions][max_dimensions];
    char token_1;
    char token_2;
    bool player_1_first_turn;
    int rounds_left;
    int player_1_round_wins;
    int player_2_round_wins;
    bool is_connect_six;
    bool is_ai_match;
public:
    GameMatch(int width = default_width, int height = default_height, char token_1 = default_tok_1, char token_2 = default_tok_2, int rounds_left = default_rounds, bool is_connect_six = default_is_connect_six, bool is_ai_match = default_is_ai_match);
    void reset();
    int drop_token(int pos, bool isPlayer1);
    bool check_if_won(bool is_player_1, int x, int y);
    int get_player_1_round_wins();
    int get_player_2_round_wins();
    int get_rounds_left();
    bool get_player_1_first_turn();
    int get_width();
    int get_height();
    char get_grid_tok(int x, int y);
    bool get_is_connect_six();
    bool get_is_ai_match();
    char* get_grid_row(int y);
};

#include "ai.h"

#endif // GAME_MATCH_H

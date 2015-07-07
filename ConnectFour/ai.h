#ifndef AI_H
#define AI_H

#include <iostream>
#include "game_match.h"

using namespace std;

class ai
{
private:
    bool is_player_1_turn;
    int seconds_to_play;
    char p1_scenario_buff[1024] = {0};
    char p2_scenario_buff[1024] = {0};
    int p1_col_buff[64] = {0};
    int p2_col_buff[64] = {0};
    int p1_scenario_buff_size;
    int p2_scenario_buff_size;
    int p1_col_buff_size;
    int p2_col_buff_size;
    char scen_list[65530] = {0};
    int col_list[3120][default_width] = {{0}};//put board width inside second []
    int scen_list_size;
    int col_list_size;
public:
    ai();
    int choose_column(GameMatch* match, bool is_player_1_turn = false);
    play_turn();
    gen_1();
    void grid_to_buff(int col);
    void buff_to_list(bool is_p1_win);
};

#endif // AI_H


#ifndef AI_H
#define AI_H

#include <iostream>
#include "game_match.h"
#include <string.h>

using namespace std;

const int scen_list_max = 65530;
const int col_list_max = 3120;
const int scen_buff_max = 1024;
const int col_buff_max = 64;

class ai
{
private:
    bool is_player_1_turn;
    int seconds_to_play;
    char p1_scenario_buff[scen_buff_max] = {0}; //scen_buff: [(size of this scenario entry: chars in the scenario + 1 for this char)(scenario characters)][another scenario...]...
    char p2_scenario_buff[scen_buff_max] = {0};
    int p1_col_buff[col_buff_max] = {0}; //col_buff: [(column choice for first scenario)][(column choice for second scenario)
    int p2_col_buff[col_buff_max] = {0};
    int p1_scenario_buff_size;
    int p2_scenario_buff_size;
    int p1_col_buff_size;
    int p2_col_buff_size;
    char scen_list[scen_list_max] = {0}; // [(num rows in scenario)(scnario characters)][another scenario...]...
    unsigned int col_list[col_list_max][default_width] = {{0}};//put board width inside second []
    int scen_list_size; // number of array indexes scen currently uses - 1 (idx of last used position in list)
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


#include <stdlib.h>
#include <time.h>
#include "ai.h"

GameMatch* ai_match;
const char end_scen = '~';
const int board_width = default_width;
const int board_height = default_height;

ai::ai() {
    is_player_1_turn = true;
    seconds_to_play = 60 * 2;
    p1_scenario_buff_size = 0;
    p2_scenario_buff_size = 0;
    p1_col_buff_size = 0;
    p2_col_buff_size = 0;
    scen_list_size = 0;
    col_list_size = 0;
}


int ai::choose_column(GameMatch* cur_match, bool is_player_1_turn)
{
    int width = cur_match->get_width();
    GameMatch sim_match;

    //if it can win this turn, choose the column that results in winning
    for (int i= 0; i < width; i++) {
        memcpy(&sim_match, cur_match, sizeof(*cur_match));
        if (sim_match.drop_token(i, is_player_1_turn) == 2) {
            return i;
        }
    }

    //if it prevents the opponent from winning, choose the column that blocks the opponent
    for (int i= 0; i < width; i++) {
        memcpy(&sim_match, cur_match, sizeof(*cur_match));
        if (sim_match.drop_token(i, !is_player_1_turn) == 1) {
            return i;
        }
    }

    //otherwise choose a random column that is not full
    srand(time(NULL));
    int r = rand() % width;
    for (int i = 0; i < width; i++) {
        memcpy(&sim_match, cur_match, sizeof(*cur_match));
        if (sim_match.drop_token(r, is_player_1_turn) == 0) {
            return r;
        }
        r = (r+1) % width;
    }
    return r;
}

ai::play_turn()
{
    int col = choose_column(ai_match);
    is_player_1_turn ? is_player_1_turn = false : is_player_1_turn = true;
    col = choose_column(ai_match, is_player_1_turn);
    ai_match->drop_token(col, is_player_1_turn);
    return -1;
}

ai::gen_1()
{
    GameMatch* ai_match = new GameMatch(board_width, board_height);
    clock_t start = clock();
    double duration = 0;
    int count = 0;

    new_match:
    p1_scenario_buff_size = 0;
    p2_scenario_buff_size = 0;
    p1_col_buff_size = 0;
    p2_col_buff_size = 0;
    ai_match->reset();
    while (seconds_to_play > duration) {
        int col = choose_column(ai_match, is_player_1_turn);

        grid_to_buff(col);

        count++;
        duration = (clock() - start) / (double) CLOCKS_PER_SEC;
        //check if next scenario will overfow the buff

        int winner = ai_match->drop_token(col, is_player_1_turn);
        if (winner == 1) {
            buff_to_list(true);
            goto new_match;
        } else if (winner == 2) {
            buff_to_list(false);
            goto new_match;
        } else if (winner == 3) {
            goto new_match;
        }


    }
    delete(ai_match);
    cout << "\n\nNumber of matches:  " << count;
    return -1;
}

inline void ai::grid_to_buff(int col) {
    char* scen_buff_ptr;
    int* col_buff_ptr;
    int* scen_buff_size_ptr;
    int* col_buff_size_ptr;

    if (is_player_1_turn) {
        is_player_1_turn = false;
        scen_buff_ptr = &p2_scenario_buff[p2_scenario_buff_size];
        col_buff_ptr = &p2_col_buff[p2_col_buff_size];
        scen_buff_size_ptr = &p2_scenario_buff_size;
        col_buff_size_ptr = &p2_col_buff_size;
    } else {
        is_player_1_turn = true;
        scen_buff_ptr = &p1_scenario_buff[p1_scenario_buff_size];
        col_buff_ptr = &p1_col_buff[p1_col_buff_size];
        scen_buff_size_ptr = &p1_scenario_buff_size;
        col_buff_size_ptr = &p1_col_buff_size;
    }

    int row_idx;
    char num_rows_in_scenario = 0;
    scen_buff_ptr++;
    //fill the scenario buffer row by row with game board contents
    for (row_idx = board_height - 1; row_idx >= 0; row_idx--) {
        char row[board_width];
        memcpy(row, ai_match->get_grid_row(row_idx), board_width);
        for (int i = 0; i < board_width; i++) {
            //fill the scenario buffer only with rows that aren't empty
            if (row[i] != fill_val) {
                num_rows_in_scenario++;
                memcpy(scen_buff_ptr, row, board_width);
                scen_buff_ptr += board_width; //!
                break;
            }
        }
        //go to the beginning index of the current scenario that was skipped over and place there the size of the scenario entry
        *(scen_buff_ptr - 1 - (num_rows_in_scenario * board_width)) = num_rows_in_scenario * board_width + 1;
        *scen_buff_size_ptr += (num_rows_in_scenario * board_width) + 1;
    }

    *col_buff_ptr = col;
    col_buff_ptr++;
    (*col_buff_size_ptr)++;
}

inline void ai::buff_to_list(bool is_p1_win) {
    char* scen_buff_ptr;
    int* col_buff_ptr;
    int* scen_buff_size_ptr;
    int* col_buff_size_ptr;

    if (is_p1_win) {
        scen_buff_ptr = &p1_scenario_buff[0];
        col_buff_ptr = &p1_col_buff[0];
        scen_buff_size_ptr = &p1_scenario_buff_size;
        col_buff_size_ptr = &p1_col_buff_size;

    } else {
        scen_buff_ptr = &p2_scenario_buff[0];
        col_buff_ptr = &p2_col_buff[0];
        scen_buff_size_ptr = &p2_scenario_buff_size;
        col_buff_size_ptr = &p2_col_buff_size;
    }

    while (*scen_buff_ptr < *scen_buff_size_ptr) {
        bool scen_list_is_full = false;
        char* scen_list_ptr = &scen_list[0];
        int scen_idx = 0;
        //look through the scen list for a scenario in scen buff
        while (scen_list_ptr + *scen_list_ptr < scen_list + scen_list_size) {
            if (*scen_list_ptr == *scen_buff_ptr && !memcmp(scen_list_ptr, scen_buff_ptr, (size_t) *scen_buff_ptr)) {
                if (col_list[scen_idx][*(col_buff_ptr+scen_idx)] < 4294967296) {   //magic num is max int val
                    //if the scenairio is found and it will not overflow, increment the
                    //index in the column list of the position chosen in the current scenario
                    //to add weight to choosing this column in this scenario since this scenario
                    //won and thus this choice will more likely result in winning
                    col_list[scen_idx][*(col_buff_ptr+scen_idx)]++;
                } else {
                    cout << "col_list entry tried to overflow!" << endl; //! remove this if() and just increment if overflow limit won't be reached
                }
                goto found_scen;
            }
            scen_idx++;
            scen_list_ptr += *scen_list_ptr;
        }

        //if the scenario wasn't found and there is room in scen list, add it to the scen and col lists
        if (!scen_list_is_full && scen_list_size + *scen_buff_ptr < scen_list_max) {
            memcpy(scen_list + scen_list_size, scen_buff_ptr, (size_t) *scen_buff_ptr);
            scen_list_size += *scen_buff_ptr;
            //TODO: col_list
        } else {
            scen_list_is_full = true;
        }
        found_scen:
        scen_buff_ptr += *scen_buff_ptr;
    }

    //instead of this, copy each scenario one at a time to try to match scenarios to scenarios that exist in the list
    memcpy(scen_list + scen_list_size, scen_buff_ptr, *scen_buff_size_ptr);
    col_list[col_list_size - 1][*(col_buff_ptr + *col_buff_size_ptr - 1)];
}

//void get_scen_idx

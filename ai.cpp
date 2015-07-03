#include <connect_four.h>
#include <stdlib.h>
#include <time.h>

Game_Match* ai_match;

ai::ai() {
    is_player_1_turn = true;
    width = default_width;
    height = default_height;
    seconds_to_play = 60 * 2;
    /*p1_scenario_buff;
    p2_scenario_buff = {0};
    p1_col_buff = {0};
    p2_col_buff = {0};
    */
    p1_scenario_buff_end = 0;
    p2_scenario_buff_end = 0;
    p1_col_buff_end = 0;
    p2_col_buff_end = 0;
}


int ai::choose_column(Game_Match* cur_match, bool is_player_1_turn)
{
    int width = cur_match->get_width();
    Game_Match sim_match;

    //if it can win this turn, choose the column that results in winning
    for (int i= 0; i < width; i++) {
        memcpy(&sim_match, cur_match, sizeof(*cur_match));
        if (sim_match.drop_token(i, is_player_1_turn) == 2) {
            return i;
        }
    }

    //if it prevent the opponent from winning, choose the column that blocks the opponent
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
    Game_Match* ai_match = new Game_Match(width, height);
    clock_t start;
    double duration;
    int count = 0;
    int col;

    start = clock();
    while (seconds_to_play > duration) {
        char* scen_buff_ptr;
        int* col_buff_ptr;
        int* scen_end_ptr;
        int* col_end_ptr;

        if(is_player_1_turn) {
            is_player_1_turn = false;
            scen_buff_ptr = &p2_scenario_buff[p2_scenario_buff_end];
            col_buff_ptr = &p2_col_buff[p2_col_buff_end];
            scen_end_ptr = &p2_scenario_buff_end;
            col_end_ptr = &p2_col_buff_end;
        } else {
            is_player_1_turn = true;
            scen_buff_ptr = &p1_scenario_buff[p1_scenario_buff_end];
            col_buff_ptr = &p1_col_buff[p1_col_buff_end];
            scen_end_ptr = &p1_scenario_buff_end;
            col_end_ptr = &p1_col_buff_end;
        }
        col = choose_column(ai_match, is_player_1_turn);


        int buf_width = ai_match->get_width();
        int row_idx;
        for (row_idx = ai_match->get_height() - 1; row_idx >= 0; row_idx--) {
            char row[buf_width];
            memcpy(row, ai_match->get_grid_row(row_idx), sizeof(row));
            int i;
            for (i = 0; i < buf_width; i++) {
                if (row[i] != fill_val) {
                    memcpy(scen_buff_ptr, row, sizeof(row));
                    scen_buff_ptr += buf_width * sizeof(char); //!
                    *scen_end_ptr += buf_width;
                    break;
                }
            }
        }
        *col_buff_ptr = col;
        *col_end_ptr += sizeof(int);


        ai_match->drop_token(col, is_player_1_turn);
        count++;
        duration = (clock() - start) / (double) CLOCKS_PER_SEC;
                //check if next scenario will overfow the buff

    }
    delete(ai_match);
    cout << "\n\nNumber of matches:  " << count;
    return -1;
}

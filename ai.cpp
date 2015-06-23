#include <connect_four.h>
#include <stdlib.h>
#include <time.h>

class ai
{
private:
    bool is_player_1_turn;
    int width;
    int height;
    int seconds_to_play;
    char[];
    int[];
public:
    ai();
    int choose_column(Game_Match* match, bool is_player_1_turn = false);
    play_turn();
    gen_1();
};

Game_Match* ai_match;

ai::ai() {
    is_player_1_turn = true;
    width = default_width;
    height = default_height;
    seconds_to_play = 60 * 2;

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
        count++;
        duration = (clock() - start) / (double) CLOCKS_PER_SEC;
        is_player_1_turn ? is_player_1_turn = false : is_player_1_turn = true;
        col = choose_column(ai_match, is_player_1_turn);
    }
    delete(ai_match);
    cout << "\n\nNumber of matches:  " << count;
    return -1;
}

#include "game_match.h"

GameMatch::GameMatch(int width, int height, char token_1, char token_2, int rounds, bool is_connect_six, bool is_ai_match)
{
    if (width < min_dimensions || height < min_dimensions || width > max_dimensions || height > max_dimensions) {
        throw 1;
    }
    if (token_1 == token_2 || token_1 == fill_val || token_2 == fill_val) throw 2;
    this->width = width;
    this->height = height;
    this->token_1 = token_1;
    this->token_2 = token_2;
    player_1_first_turn = true;
    rounds_left = rounds;
    this->is_connect_six = is_connect_six;
    this->is_ai_match = is_ai_match;
    player_1_round_wins = 0;
    player_2_round_wins = 0;
    reset();
}

//called at the beginning of a new turn
void GameMatch::reset()
{
    player_1_first_turn = (player_1_first_turn) ? false : true;
    std::fill(&(grid[0][0]), &(grid[max_dimensions - 1][max_dimensions - 1]), fill_val);
}

//paremeters: pos - index of grid where token is dropped (from 0 to width-1)
//is_player_1 - true if it is player 1's turn
//returns: 0 for no win, 1 for player 1 win, 2 for player 2, 3 for tie,
//and -1 for invalid column choice (column is full)
int GameMatch::drop_token(int pos, bool is_player_1)
{
    if (pos > width) throw 3;
    char next_tok;
    int i = -1;
    do {
        i++;
        next_tok = grid[i][pos];
    } while (next_tok == fill_val && i < height);
    if (i <= 0) {
        return -1;
    }
    if (is_player_1) {
        grid[i-1][pos] = token_1;
    } else {
        grid[i-1][pos] = token_2;
    }

    //check to see if tie game (all positions filled)
    for (int j = 0; j < width; j++) {
        if (grid[0][j] == fill_val) break;
        if (j == width - 1) {
            rounds_left--;
            return 3;
        }
    }
    //check if player 1 won
    bool won = check_if_won(is_player_1, pos, i-1);
    if (is_player_1 && won) {
        player_1_round_wins++;
        rounds_left--;
        return 1;
    //check if player 2 won
    } else if (won) {
        player_2_round_wins++;
        rounds_left--;
        return 2;
    }
    return 0;
}

bool GameMatch::check_if_won(bool is_player_1, int x, int y)
{
    char target_tok;
    if (is_player_1) target_tok = token_1;
    else target_tok = token_2;
    int num_to_connect;
    is_connect_six ? num_to_connect = 6 : num_to_connect = 4;
    //check horizontal
    int num_connected = 1;
    for (int i = 1; i < num_to_connect; i++) {
        if (x+i > width - 1) break;
        if (grid[y][x+i] == target_tok) {
            num_connected++;
            if (num_connected == num_to_connect) return true;
        } else break;
    }
    for (int j = 1; j < num_to_connect; j++) {
        if (x-j < 0) break;
        if (grid[y][x-j] == target_tok) {
            num_connected++;
            if (num_connected == num_to_connect) return true;
        } else break;
    }
    //check right diagonal
    num_connected = 1;
    for (int i = 1; i < num_to_connect; i++) {
        if (y+i > height - 1 || x+i > width - 1) break;
        if (grid[y+i][x+i] == target_tok) {
            num_connected++;
            if (num_connected == num_to_connect) return true;
        } else break;
    }
    for (int j = 1; j < num_to_connect; j++) {
        if (y-j < 0 || x-j < 0) break;
        if (grid[y-j][x-j] == target_tok) {
            num_connected++;
            if (num_connected == num_to_connect) return true;
        } else break;
    }
    //check vertical diagonal
    num_connected = 1;
    for (int i = 1; i < num_to_connect; i++) {
        if (y+i > height - 1) break;
        if (grid[y+i][x] == target_tok) {
            num_connected++;
            if (num_connected == num_to_connect) return true;
        } else break;
    }
    for (int j = 1; j < num_to_connect; j++) {
        if (y-j < 0) break;
        if (grid[y-j][x] == target_tok) {
            num_connected++;
            if (num_connected == num_to_connect) return true;
        } else break;
    }
    //check left diagonal
    num_connected = 1;
    for (int i = 1; i < num_to_connect; i++) {
        if (y+i > height - 1 || x-i < 0) break;
        if (grid[y+i][x-i] == target_tok) {
            num_connected++;
            if (num_connected == num_to_connect) return true;
        } else break;
    }
    for (int j = 1; j < num_to_connect; j++) {
        if (y-j < 0 || x+j > width - 1) break;
        if (grid[y-j][x+j] == target_tok) {
            num_connected++;
            if (num_connected == num_to_connect) return true;
        } else break;
    }
    return false;
}

int GameMatch::get_player_1_round_wins() {
    return player_1_round_wins;
}

int GameMatch::get_player_2_round_wins() {
    return player_2_round_wins;
}

int GameMatch::get_rounds_left() {
    return rounds_left;
}

bool GameMatch::get_player_1_first_turn() {
    return player_1_first_turn;
}

int GameMatch::get_width() {
    return width;
}

int GameMatch::get_height() {
    return height;
}

char GameMatch::get_grid_tok(int x, int y) {
    return grid[y][x];
}

bool GameMatch::get_is_connect_six() {
    return is_connect_six;
}

bool GameMatch::get_is_ai_match() {
    return is_ai_match;
}

char* GameMatch::get_grid_row(int y){
    return grid[y];
}


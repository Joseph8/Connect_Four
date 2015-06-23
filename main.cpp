#include <connect_four.h>

//TODO: make these ^^^ into Game_MAtch fields<-------------------

Game_Match::Game_Match(int width, int height, char token_1, char token_2, int rounds, bool is_connect_six, bool is_ai_match)
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
void Game_Match::reset()
{
    player_1_first_turn = (player_1_first_turn) ? false : true;
    std::fill(&(grid[0][0]), &(grid[max_dimensions - 1][max_dimensions - 1]), fill_val);
}

//paremeters: pos - index of grid where token is dropped (from 0 to width-1)
//is_player_1 - true if it is player 1's turn
//returns: 0 for no win, 1 for player 1 win, 2 for player 2, 3 for tie,
//and -1 for invalid column choice (column is full)
int Game_Match::drop_token(int pos, bool is_player_1)
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

bool Game_Match::check_if_won(bool is_player_1, int x, int y)
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

int Game_Match::get_player_1_round_wins() {
    return player_1_round_wins;
}

int Game_Match::get_player_2_round_wins() {
    return player_2_round_wins;
}

int Game_Match::get_rounds_left() {
    return rounds_left;
}

bool Game_Match::get_player_1_first_turn() {
    return player_1_first_turn;
}

int Game_Match::get_width() {
    return width;
}

int Game_Match::get_height() {
    return height;
}

char Game_Match::get_grid_tok(int x, int y) {
    return grid[y][x];
}

bool Game_Match::get_is_connect_six() {
    return is_connect_six;
}

bool Game_Match::get_is_ai_match() {
    return is_ai_match;
}

char* Game_Match::get_grid_row(int y){
    return grid[y];
}

//-------------------------------------------------------

void start_match();
void play_round();
void display_grid();

Game_Match* match;

int main()
{
    cout << "LET'S PLAY CONNECT FOUR!\n\n";
    int player_1_match_wins = 0;
    int player_2_match_wins = 0;
    int player_1_tot_round_wins = 0;
    int player_2_tot_round_wins = 0;
    while (true) {
        start_match();

        while (match->get_rounds_left()) {
            play_round();
        }

        player_1_tot_round_wins += match->get_player_1_round_wins();
        player_2_tot_round_wins += match->get_player_2_round_wins();
        if (match->get_player_1_round_wins() > match->get_player_2_round_wins()) {
            player_1_match_wins++;
            cout << "\n\n--------------------------------------------\n     ||||||  PLAYER 1 WINS THIS MATCH  ||||||\n--------------------------------------------";
        } else if (match->get_player_1_round_wins() < match->get_player_2_round_wins()) {
            player_2_match_wins++;
            cout << "\n\n--------------------------------------------\n     ||||||  PLAYER 2 WINS THIS MATCH  ||||||\n--------------------------------------------";
        }
        Sleep(500);
        cout << "\n\n\nPlayer 1 won " << player_1_match_wins << " matches and " << player_1_tot_round_wins << " total rounds.";
        cout << "\n\nPlayer 2 won " << player_2_match_wins << " matches and " << player_2_tot_round_wins << " total rounds.";


        char c = '0';
        do {
            cout << "\n\n\nDo you want to quit playing? (y or n): ";
            cin.clear();
            cin.ignore(1000, '\n');
            cin >> c;
        } while (c != 'y' && c != 'n');
        if (c == 'y') {
            if (player_1_match_wins > player_2_match_wins) {
                Sleep(1000);
                cout << "\n\n\nPLAYER 1...";
                Sleep(3000);
                cout << "\n\n!!!!!!!!!!!   YOU WIN!!   !!!!!!!!!!!";
                Sleep(1000);
                cout << "\n\n!!!!!!!!!!!   YOU WIN!!   !!!!!!!!!!!";
                Sleep(1000);
                cout << "\n\n!!!!!!!!!!!   YOU WIN!!   !!!!!!!!!!!";
                Sleep(1000);
                cout << "\n\n!!!!!!!!!!!   YOU WIN!!   !!!!!!!!!!!";
            } else if (player_2_match_wins > player_1_match_wins) {
                Sleep(1000);
                cout << "\n\n\nPLAYER 2...";
                Sleep(3000);
                cout << "\n\n!!!!!!!!!!!   YOU WIN!!   !!!!!!!!!!!";
                Sleep(1000);
                cout << "\n\n!!!!!!!!!!!   YOU WIN!!   !!!!!!!!!!!";
                Sleep(1000);
                cout << "\n\n!!!!!!!!!!!   YOU WIN!!   !!!!!!!!!!!";
                Sleep(1000);
                cout << "\n\n!!!!!!!!!!!   YOU WIN!!   !!!!!!!!!!!";
            } else {
                Sleep(1000);
                cout << "\n\nIt's a draw.";
                Sleep(3000);
            }
            Sleep(2000);
            break;
        }
        delete(match);
    }
    return 0;
}

void start_match()
{
    char c = '\0';
    do {
        cout << "\nEnter custom settings? (y or n):  ";
        cin >> c;
    } while (c != 'y' && c != 'n');
    int width = default_width;
    int height = default_width;
    char token_1 = default_tok_1;
    char token_2 = default_tok_2;
    int rounds = 1;
    bool is_connect_six = default_is_connect_six;
    bool is_ai_match = default_is_ai_match;
    if (c == 'y') {
        c = '\0';
        do {
            cout << "\nDo you want to play connect six? (y or n):  ";
            cin.clear();
            cin.ignore(1000, '\n');
            cin >> c;
        } while (c != 'y' && c != 'n');
        if (c == 'y') is_connect_six = true;
        do {
            cout << "\nDo you want to play against an ai opponent (as opposed to a human)? (y or n):  ";
            cin.clear();
            cin.ignore(1000, '\n');
            cin >> c;
        } while (c != 'y' && c != 'n');
        if (c == 'y') is_ai_match = true;
        int ans = 0;
        do {
            cout << "\nEnter the board width between " << min_dimensions << " and " << max_dimensions << ":  ";
            cin.clear();
            cin.ignore(1000, '\n');
        } while (!(cin >> ans) || ans < min_dimensions || ans > max_dimensions);
        width = ans;
        do {
            cout << "\nEnter the board height between " << min_dimensions << " and " << max_dimensions << ":  ";
            cin.clear();
            cin.ignore(1000, '\n');
        } while (!(cin >> ans) || ans < min_dimensions || ans > max_dimensions);
        height = ans;
        do {
            cout << "\nEnter a character to use for Player 1's token (cannot be " << fill_val << "):  ";
            cin >> token_1;
        } while (token_1 == fill_val);
        do {
            cout << "\nEnter a character to use for Player 2's token (cannot be " << fill_val << " or " << token_1 << " ):  ";
            cin >> token_2;
        } while (token_2 == fill_val || token_2 == token_1);
        do {
            //cout << "\nstr" << str;
            //cout << "\nr1" << rounds;
            cout << "\nEnter the number of rounds to play (1-" << max_dimensions << "):  ";
            cin.clear();
            cin.ignore(1000, '\n');
            //getline(cin, str);
            //cin >> rounds;
            //stringstream(str) >> rounds;
            //cout << "\n:::::" << rounds;
        } while (!(cin >> rounds) || rounds <= 0 || rounds > 20);
    }

    match = new Game_Match(width, height, token_1, token_2, rounds, is_connect_six, is_ai_match);
    return;
}

//returns true to play another round, false to quit the match
void play_round() {
    match->reset();
    bool is_player_1_turn = match->get_player_1_first_turn();
    Sleep(500);
    cout << "\n\n--------------------------------------------\n |              BEGIN ROUND              | \n--------------------------------------------\n\n";
    int connect_six_turn = 1;
    int col = -1;
    int winner = 0;
    ai AI;
    //keep playing turns
    do {
        if (winner != -1) {
            if (!match->get_is_connect_six() || connect_six_turn == 3) {
               is_player_1_turn = is_player_1_turn ? false : true;
               connect_six_turn = 1;
            }
            connect_six_turn++;
            display_grid();
        } else {
            cout << "\nColumn full. Choose a different column.";
        }
        col = 0;
        cout << "\n\nPlayer " << (is_player_1_turn ? "1" : "2") <<"'s turn.";
        if (match->get_is_ai_match() && !is_player_1_turn) {
            //Sleep(1000);
            col = AI.choose_column(match);
            cout << "\n\nColumn to place token in (1 - " << match->get_width() << "):  " << col + 1 << "\n";
        } else {
            do {
                cout << "\n\nColumn to place token in (1 - " << match->get_width() << "):  ";
                cin.clear();
                cin.ignore(1000, '\n');
            } while (!(cin >> col) || col <= 0 || col > match->get_width());
            col--;
        }
    } while ((winner = match->drop_token(col, is_player_1_turn)) <= 0);

    display_grid();
    Sleep(1000);
    if (winner == 3) {
        cout << "\nIt's a tie!";
    } else if (winner == -1) {
        cout << "\nERROR!";
    } else {
        cout << "\nPlayer " << winner << " wins!";
    }
    Sleep(1000);
}

void display_grid() {

    for (int i = 0; i < match->get_width(); i++) {
        if (i+1 > 9) cout << " |" << i+1;
        else cout << " | " << i+1;
    }
    cout << " | \n";
    for (int i = 0; i < match->get_height(); i++) {
        for (int u = 0; u < match->get_width(); u++) {
            cout << "-|--";
        }
        cout << "-|-\n";
        for (int j = 0; j < match->get_width(); j++) {
            cout << " | " << match->get_grid_tok(j, i);
        }
        cout << " | \n";
    }
    for (int u = 0; u < match->get_width() + 1; u++) {
        cout << "----";
    }
    cout << "\n";
    for (int i = 0; i < match->get_width(); i++) {
        if (i+1 > 9) cout << " |" << i+1;
        else cout << " | " << i+1;
    }
    cout << " | \n";
}

#include "connect_four.h"

void start_match();
void play_round();
void display_grid();

GameMatch* match;

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

    match = new GameMatch(width, height, token_1, token_2, rounds, is_connect_six, is_ai_match);
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

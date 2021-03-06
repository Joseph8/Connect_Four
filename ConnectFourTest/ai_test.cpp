#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "../ConnectFour/connect_four.h"

TEST_CASE ("choose column chooses the right column", "[choose_column]" ) {
    GameMatch* match = new GameMatch();
    AI* ai = new AI();
    int result = ai->choose_column(match);
    SECTION ("choose_column returns a value within game board bounds") {
        REQUIRE(result < match->get_width());
        REQUIRE(result >= 0);
        result = ai->choose_column(match);
        REQUIRE(result < match->get_width());
        REQUIRE(result >= 0);
        result = ai->choose_column(match);
        REQUIRE(result < match->get_width());
        REQUIRE(result >= 0);
        result = ai->choose_column(match);
        REQUIRE(result < match->get_width());
        REQUIRE(result >= 0);
        result = ai->choose_column(match);
        REQUIRE(result < match->get_width());
        REQUIRE(result >= 0);
        result = ai->choose_column(match);
        REQUIRE(result < match->get_width());
        REQUIRE(result >= 0);
        result = ai->choose_column(match);
        REQUIRE(result < match->get_width());
        REQUIRE(result >= 0);
        result = ai->choose_column(match);
        REQUIRE(result < match->get_width());
        REQUIRE(result >= 0);
        result = ai->choose_column(match);
        REQUIRE(result < match->get_width());
        REQUIRE(result >= 0);
    }

    SECTION ("chooses the column that blocks a match win") {
        match->drop_token(0, true);
        match->drop_token(1, true);
        match->drop_token(2, true);
        match->drop_token(ai->choose_column(match), false); //player 2 should block the winning move
        REQUIRE (match->drop_token(3, true) == 0); //a return of 0 for no win means p2 blocked
    }

    SECTION ("chooses the column that wins the match") {
        match->drop_token(0, true);
        match->drop_token(1, true);
        match->drop_token(2, true);
        match->drop_token(0, false);
        match->drop_token(0, false);
        match->drop_token(0, false);
        REQUIRE (match->drop_token(ai->choose_column(match), false) == 2); //player 2 should win instead of block
    }

    delete(match);
    delete(ai);
}

TEST_CASE ("check buff contents", "[grid_to_buff]") {
    GameMatch* match = new GameMatch();
    AI* ai = new AI();

    SECTION ("check contents after a few rounds") {
        int col = 2;
        ai->grid_to_buff(col);
        //scen buff array initialized all elements to 0, so this checks to make sure nothing was added to scen buff
        REQUIRE (ai->p1_scenario_buff[0] == 0);
        REQUIRE (ai->p1_scenario_buff[2] == 0);
        REQUIRE (ai->p1_scenario_buff[6] == 0);
        REQUIRE (ai->p1_col_buff[0] == col);
        match->drop_token(col, true);

        //ai->next_turn();
        col = 3;
        ai->grid_to_buff(col);
        REQUIRE (ai->p1_scenario_buff[0] == fill_val);
        REQUIRE (ai->p1_scenario_buff[2] == default_tok_1);
        REQUIRE (ai->p1_scenario_buff[6] == fill_val);
        REQUIRE (ai->p1_scenario_buff[7] == 0);
        REQUIRE (ai->p1_col_buff[0] == 2);
        match->drop_token(col, false);

    }
    /*
    SECTION ("") {
        match->drop_token(0, true);
        match->drop_token(0, false);
        match->drop_token(1, true);
        match->drop_token(5, false);
        match->drop_token(0, true);
    }
    */
    delete(match);
    delete(ai);
}


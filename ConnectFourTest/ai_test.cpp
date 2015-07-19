#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "../ConnectFour/connect_four.h"

TEST_CASE ("Choose column chooses an index within the board width", "[ai]" ) {
    GameMatch* match = new GameMatch();
    AI* ai = new AI();
    int result = ai->choose_column(match);
    REQUIRE(result < match->get_width());
    REQUIRE(result >= 0);
    delete(match);
    delete(ai);
}

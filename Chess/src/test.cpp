#include <gtest/gtest.h>
#include "Engine.h"

TEST(EngineTest, InitialBoardSetup) {
std::string initialBoard =
        "R########"
        "########"
        "########"
        "########"
        "########"
        "########"
        "########"
        "r#######";
Engine engine(initialBoard);

std::string expectedBoard =
        "R#######\n"
        "########\n"
        "########\n"
        "########\n"
        "########\n"
        "########\n"
        "########\n"
        "r#######\n";
EXPECT_EQ(engine.printBoard(), expectedBoard);
}

TEST(EngineTest, MovePiece) {
std::string initialBoard =
        "R#######"
        "########"
        "########"
        "########"
        "########"
        "########"
        "########"
        "r#######";
Engine engine(initialBoard);

// Valid move
EXPECT_EQ(engine.checkMove("a1a2"), 42); // move Rook from a1 to a2
std::string expectedBoard =
        "########\n"
        "R#######\n"
        "########\n"
        "########\n"
        "########\n"
        "########\n"
        "########\n"
        "r#######\n";
EXPECT_EQ(engine.printBoard(), expectedBoard);

// Invalid move (trying to move opponent's piece)
EXPECT_EQ(engine.checkMove("a8a7"), 12);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

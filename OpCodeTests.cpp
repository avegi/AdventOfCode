#include "gtest/gtest.h"
#include "../Parser.h"

TEST(BinaryFunctionsTests, AddTest)
{
    std::vector<int> inputCode = {1,0,0,0,2,0,0,0,99};
    Parser parser = Parser();
    int t = parser.parse(inputCode, 0);
    //EXPECT_EQ(parser.parse(inputCode, 0), 4);
}




int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
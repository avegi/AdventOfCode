#include "gtest/gtest.h"
#include "Parser.h"

TEST(BinaryFunctionsTests, AddTest)
{
    {
        std::vector<int> inputCode = {1, 0, 0, 0, 99};
        Parser parser = Parser();
        EXPECT_EQ(parser.parse(inputCode, 0), 2);
    }
    {
        std::vector<int> inputCode = {2, 0, 0, 0, 99};
        Parser parser = Parser();
        EXPECT_EQ(parser.parse(inputCode, 0), 4);
    }
    {
        std::vector<int> inputCode = {1, 0, 0, 0, 2, 0, 0, 0, 99};
        Parser parser = Parser();
        EXPECT_EQ(parser.parse(inputCode, 0), 4);
    }
    {
        std::vector<int> inputCode = {1,1,1,4,99,5,6,0,99};
        Parser parser = Parser();
        EXPECT_EQ(parser.parse(inputCode, 4), 2);
        EXPECT_EQ(parser.parse(inputCode, 0), 30);
    }
    {
        std::vector<int> inputCode = {1,9,10,3,2,3,11,0,99,30,40,50};
        Parser parser = Parser();
        EXPECT_EQ(parser.parse(inputCode, 0), 3500);
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
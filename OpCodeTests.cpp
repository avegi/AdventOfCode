#include "gtest/gtest.h"
#include "Parser.h"

TEST(ThreeParamsExpressionTests, AddTest)
{
    {
        std::vector<int> inputCode = {1, 0, 0, 0, 99};
        Parser parser = Parser(inputCode);
        parser.parse();
        EXPECT_EQ(parser.getValue(0), 2);
    }
    {
        std::vector<int> inputCode = {2, 0, 0, 0, 99};
        Parser parser = Parser(inputCode);
        parser.parse();
        EXPECT_EQ(parser.getValue(0), 4);
    }
    {
        std::vector<int> inputCode = {1, 0, 0, 0, 2, 0, 0, 0, 99};
        Parser parser = Parser(inputCode);
        parser.parse();
        EXPECT_EQ(parser.getValue( 0), 4);
    }
    {
        std::vector<int> inputCode = {1,1,1,4,99,5,6,0,99};
        Parser parser = Parser(inputCode);
        parser.parse();
        EXPECT_EQ(parser.getValue(4), 2);
        EXPECT_EQ(parser.getValue(0), 30);
    }
    {
        std::vector<int> inputCode = {1,9,10,3,2,3,11,0,99,30,40,50};
        Parser parser = Parser(inputCode);
        parser.parse();
        EXPECT_EQ(parser.getValue(0), 3500);
    }
}

TEST(ThreeParamsExpressionTests, MultiplyTest)
{
    {
        std::vector<int> inputCode = {2,4,4,5,99,0};
        Parser parser = Parser(inputCode);
        parser.parse();
        EXPECT_EQ(parser.getValue(5), 9801);
    }
}

TEST(OneParamExpressionTests, InputExpressionTest)
{
    {
        std::vector<int> inputCode = {3,0,99};
        Parser parser = Parser(inputCode);
        parser.parse(100);
        EXPECT_EQ(parser.getValue(0), 100);
    }
}

TEST(OneParamExpressionTests, OutputExpressionTest)
{
    {
        std::vector<int> inputCode = {4,50,99};
        Parser parser = Parser(inputCode);
        auto output = parser.parse(100);
        EXPECT_EQ(output.value(), 50);
    }
}

TEST(ModeTests, ImmediateModeTest)
{
    {
        std::vector<int> inputCode = {1002,4,3,4,33};
        Parser parser = Parser(inputCode);
        parser.parse();
        EXPECT_EQ(parser.getValue(4), 99);
    }
}

TEST(TwoParamExpressionTests, JumpIfTrueExpressionTest)
{
    {
        std::vector<int> inputCode = {5,3,4,1000,99};
        Parser parser = Parser(inputCode);
        parser.parse(100);
    }
}

TEST(TwoParamExpressionTests, JumpIfFalseExpressionTest)
{
    {
        std::vector<int> inputCode = {5,3,4,0,99};
        Parser parser = Parser(inputCode);
        parser.parse(100);
    }
}

TEST(ThreeParamsExpressionTests, LessThanExpressionTest)
{
    {
        std::vector<int> inputCode = {3,9,7,9,10,9,4,9,99,-1,8};
        Parser parser = Parser(inputCode);
        auto output = parser.parse(7);
        EXPECT_EQ(output.value(), 1);
    }
    {
        std::vector<int> inputCode = {3,9,7,9,10,9,4,9,99,-1,8};
        Parser parser = Parser(inputCode);
        auto output = parser.parse(8);
        EXPECT_EQ(output.value(), 0);
    }
}

TEST(ThreeParamsExpressionTests, EqualsExpressionTest)
{
    {
        std::vector<int> inputCode = {3,9,8,9,10,9,4,9,99,-1,8};
        Parser parser = Parser(inputCode);
        auto output = parser.parse(8);
        EXPECT_EQ(output.value(), 1);
    }
    {
        std::vector<int> inputCode = {3,9,8,9,10,9,4,9,99,-1,8};
        Parser parser = Parser(inputCode);
        auto output = parser.parse(9);
        EXPECT_EQ(output.value(), 0);
    }
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
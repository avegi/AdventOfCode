#include <iostream>
#include "vector"
#include "Parser.h"

int main() {

    std::vector<int> inputCode = {1,12,2,3,1,1,2,3,1,3,4,3,1,5,0,3,2,1,6,19,1,19,6,23,2,23,6,27,2,6,27,31,2,13,31,35,1,9,35,39,2,10,39,43,1,6,43,47,1,13,47,51,2,6,51,55,2,55,6,59,1,59,5,63,2,9,63,67,1,5,67,71,2,10,71,75,1,6,75,79,1,79,5,83,2,83,10,87,1,9,87,91,1,5,91,95,1,95,6,99,2,10,99,103,1,5,103,107,1,107,6,111,1,5,111,115,2,115,6,119,1,119,6,123,1,123,10,127,1,127,13,131,1,131,2,135,1,135,5,0,99,2,14,0,0};

    // Part 1
    {
        Parser parser = Parser(inputCode);
        parser.parse();
        std::cout << parser.getValue(0) << endl;
    }

    {
        for (int noun = 0; noun < 100; noun++)
            for (int verb = 0; verb < 100; verb++)
            {
                inputCode[1] = noun;
                inputCode[2] = verb;
                Parser parser = Parser(inputCode);
                parser.parse();
                if (parser.getValue(0) == 19690720)
                {
                    std::cout << 100 * noun + verb;
                }
            }
    }

    // Day 5

    {
        std::vector<int> inputCode_day5 = {4,0,99};
        Parser parser = Parser(inputCode_day5);
        std::optional<int> a = parser.parse();

    }

    return 0;
}

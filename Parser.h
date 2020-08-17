#pragma once

#include <sstream>
#include "vector"
#include "Context.h"
#include "Expression.h"
#include "optional"

/** Parser for intCode computer.
 * Makes a copy of the input intCode and stores for processing.
 */
class Parser{
public:
    explicit Parser(std::vector<int> intCode)
        : m_context(Context(intCode, 0))
    {}

/** Parses the intCode
 * Accepts an input value and returns the last output (if any).
 * @param input: input for the computer.
 * @return: output of the computer.
 */
    std::optional<int> parse( int input = std::numeric_limits<int>::max())
    {
        int pos = 0;

        int test = 1101;
        auto a = getMask(test);

        std::optional<int> retval;
        while (m_context.getValue(pos) != 99) {
            pos = m_context.getPos();
            int intCommand = m_context.getValue(pos);
            auto maskedCommand = getMask(intCommand);
            string commandString = maskedCommand.command;
            unique_ptr<Expression> uptr_exp;

            if (commandString == "1" || commandString == "01")
            {
                uptr_exp = make_unique<AddExpression>(m_context, maskedCommand.modes);
                uptr_exp->process();
            }
            else if (commandString == "2" || commandString == "02")
            {
                uptr_exp = make_unique<MultiplyExpression>(m_context, maskedCommand.modes);
                uptr_exp->process();
            }
            else if (commandString == "3" || commandString == "03")
            {
                uptr_exp = make_unique<InputExpression>(m_context, maskedCommand.modes);
                uptr_exp->writeData(input);
            }
            else if (commandString == "4" || commandString == "04"){
                uptr_exp = make_unique<OutputExpression>(m_context, maskedCommand.modes);
                input = uptr_exp->readData();
                std::cout << input << endl;
            }
            else if (commandString == "5" || commandString == "05"){
                uptr_exp = make_unique<JumpIfTrueExpression>(m_context, maskedCommand.modes);
                uptr_exp->process();
            }
            else if (commandString == "6" || commandString == "06"){
                uptr_exp = make_unique<JumpIfFalseExpression>(m_context, maskedCommand.modes);
                uptr_exp->process();
            }
            else if (commandString == "7" || commandString == "07"){
                uptr_exp = make_unique<LessThanExpression>(m_context, maskedCommand.modes);
                uptr_exp->process();
            }
            else if (commandString == "8" || commandString == "08"){
                uptr_exp = make_unique<EqualsExpression>(m_context, maskedCommand.modes);
                uptr_exp->process();
            }

        }
        if (input != std::numeric_limits<int>::max())
            retval = input;
        return retval;
    }
/** Returns the value stored at the requested position of the intCode input.
 * @param pos: position to be checked.
 * @return: the velaue at the position.
 */
    int getValue(int pos)
    {
        return m_context.getValue(pos);
    }

private:
    CommandMode getMask(int mode)
    {

        CommandMode mask = CommandMode();
        std::stringstream ss;
        ss << mode;
        std::string strDigits = ss.str();
        int strSize = strDigits.size();
        // '01101'
        if (strSize <= 2)
        {
            mask.command = to_string(mode);
        }
        else
        {
            string code = strDigits.substr(strSize-2, strSize-1);
            mask.command = code;

            for (int i = strSize-3, j=0; i>=0; i--, j++)
            {
                mask.modes[j] = string() + strDigits[i];
            }
        }

        return mask;
    }

private:
    Context m_context;
};

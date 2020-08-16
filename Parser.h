#pragma once

#include <sstream>
#include "vector"
#include "Context.h"
#include "Expression.h"
#include "optional"

class Parser{
public:
    Parser(std::vector<int> opCode)
        : m_context(Context(opCode, 0))
    {}

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
                uptr_exp->Calculate();
            }
            else if (commandString == "2" || commandString == "02")
            {
                uptr_exp = make_unique<MultiplyExpression>(m_context, maskedCommand.modes);
                uptr_exp->Calculate();
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

        }
        if (input != std::numeric_limits<int>::max())
            retval = input;
        return retval;
    }

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

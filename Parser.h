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

    std::optional<int> parse()
    {
        int pos = 0;

        int test = 10101;
        auto a = getMask(test);

        std::optional<int> retval;
        int buffer = std::numeric_limits<int>::max();
        while (m_context.getValue(pos) != 99) {
            pos = m_context.getPos();
            int intCommand = m_context.getValue(pos);
            auto maskedCommand = getMask(intCommand);
            unique_ptr<Expression> uptr_exp;
            string commandString = maskedCommand.front();
            if (commandString == "1" || commandString == "01")
            {
                uptr_exp = make_unique<AddExpression>(m_context);
                uptr_exp->Calculate();
            }
            else if (commandString == "2" || commandString == "02")
            {
                uptr_exp = make_unique<MultiplyExpression>(m_context);
                uptr_exp->Calculate();
            }
            else if (commandString == "3" || commandString == "03")
            {
                uptr_exp = make_unique<InputExpression>(m_context);
                uptr_exp->writeData(buffer);
            }
            else if (commandString == "4" || commandString == "04"){
                uptr_exp = make_unique<OutputExpression>(m_context);
                buffer = uptr_exp->readData();
            }

        }
        if (buffer != std::numeric_limits<int>::max())
            retval = buffer;
        return retval;
    }

    int getValue(int pos)
    {
        return m_context.getValue(pos);
    }

private:
    std::vector<string> getMask(int mode)
    {
        std::vector<string> mask;
        std::stringstream ss;
        ss << mode;
        std::string strDigits = ss.str();
        int strSize = strDigits.size();
        // '01101'
        if (strSize <= 2)
        {
            mask.push_back(to_string(mode));
        }
        else
        {
            string code = strDigits.substr(strSize-2, strSize-1);
            mask.push_back(code);
            for (int i = strSize-3; i>=0; i--)
            {
                mask.push_back(string() + strDigits[i]);
            }
        }

        return mask;
    }

private:
    Context m_context;
};

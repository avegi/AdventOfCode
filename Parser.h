#pragma once

#include "vector"
#include "Context.h"
#include "Expression.h"
# include "optional"

class Parser{
public:
    Parser(std::vector<int> opCode)
        : m_context(Context(opCode, 0))
    {}


    std::optional<int> parse()
    {
        int pos = 0;
        std::optional<int> retval;
        while (m_context.getValue(pos) != 99) {
            pos = m_context.getPos();
            int command = m_context.getValue(pos);
            if (command == 1) {
                auto ptr_exp = make_shared<AddExpression>(m_context);
                ptr_exp->Calculate();
                m_context.setPos(pos + 4);
            } else if (command == 2) {
                auto ptr_exp = make_shared<MultiplyExpression>(m_context);
                ptr_exp->Calculate();
                m_context.setPos(pos + 4);
            }
        }

        //return m_context.getValue(retPos);
        return retval;
    }

    int getValue(int pos)
    {
        return m_context.getValue(pos);
    }

private:
    Context m_context;
};

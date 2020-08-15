#pragma once

#include "vector"
#include "Context.h"
#include "Expression.h"
class Parser{
public:
    Parser() = default;

    int parse(std::vector<int> opCode, int retPos)
    {
        Context context = Context(opCode, 0);

        int pos = 0;
        while (context.getValue(pos) != 99) {
            pos = context.getPos();
            int command = context.getValue(pos);
            if (command == 1) {
                auto ptr_exp = make_shared<AddExpression>(context);
                ptr_exp->Calculate();
                context.setPos(pos + 4);
            } else if (command == 2) {
                auto ptr_exp = make_shared<MultiplyExpression>(context);
                ptr_exp->Calculate();
                context.setPos(pos + 4);
            }
        }

        return context.getValue(retPos);
    }
};

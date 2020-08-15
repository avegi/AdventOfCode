#pragma once

#include "vector"
#include "memory"
#include "Context.h"

using namespace std;

/** Expression ABC
 *
 */
class Expression {
public:
    Expression(Context &input);
    virtual ~Expression();

protected:
    int m_pos;
    Context &m_input;
};

class BinaryExpression : protected Expression{
public:
    BinaryExpression(Context &input);
    virtual int Calculate() = 0;

protected:
    int m_lhsPos;
    int m_rhsPos;
    int m_outPos;
};

/**
 *
 */
class AddExpression : BinaryExpression{
public:
    AddExpression(Context &input);
    int Calculate() override;
};

/**
 *
 */
class MultiplyExpression : BinaryExpression{
public:
    MultiplyExpression(Context &input);
    int Calculate() override;

};

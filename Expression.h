#ifndef ADVENTOFCODE_EXPRESSION_H
#define ADVENTOFCODE_EXPRESSION_H
#endif //ADVENTOFCODE_EXPRESSION_H

#include "vector"
#include "memory"

using namespace std;

/** Expression ABC
 *
 */
class Expression {
public:
    Expression(std::vector<int> &input, int pos);
    virtual ~Expression();

protected:
    int m_pos;
    std::vector<int> &m_input;
};

class BinaryExpression : protected Expression{
public:
    BinaryExpression(std::vector<int> &input, int pos);
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
    AddExpression(std::vector<int> &input, int pos);
    int Calculate() override;
};

/**
 *
 */
class MultiplyExpression : BinaryExpression{
public:
    MultiplyExpression(std::vector<int> &input, int pos);
    int Calculate() override;

};



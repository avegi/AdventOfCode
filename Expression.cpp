#include "Expression.h"
#include <iostream>

Expression::Expression(std::vector<int> &input, int pos)
    : m_input(input)
    , m_pos(pos)
    {}

Expression::~Expression() noexcept {}

BinaryExpression::BinaryExpression(std::vector<int> &input, int pos)
    : Expression(input, pos)
    {
    m_lhsPos = input[pos+1];
    m_rhsPos = input[pos+2];
    m_outPos = input[pos+3];
    }

AddExpression::AddExpression(std::vector<int> &input, int pos)
    : BinaryExpression(input, pos)
    {}


int AddExpression::Calculate() {
    int lhs = m_input[m_lhsPos];
    int rhs = m_input[m_rhsPos];
    m_input[m_outPos] = lhs + rhs;
}

MultiplyExpression::MultiplyExpression(std::vector<int> &input, int pos)
    : BinaryExpression(input, pos)
    {}


int MultiplyExpression::Calculate() {
    int lhs = m_input[m_lhsPos];
    int rhs = m_input[m_rhsPos];
    m_input[m_outPos] = lhs * rhs;
}
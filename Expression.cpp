#include "Expression.h"
#include <iostream>

Expression::Expression(Context &input)
    : m_input(input)
    {
        m_pos = m_input.getPos();
    }

Expression::~Expression() noexcept {}

BinaryExpression::BinaryExpression(Context &input)
    : Expression(input)
    {
    m_lhsPos = input.getValue(m_pos+1);
    m_rhsPos = input.getValue(m_pos+2);
    m_outPos = input.getValue(m_pos+3);
    }

AddExpression::AddExpression(Context &input)
    : BinaryExpression(input)
    {}


int AddExpression::Calculate() {
    int lhs = m_input.getValue(m_lhsPos);
    int rhs = m_input.getValue(m_rhsPos);
    m_input.setValue(lhs + rhs, m_outPos);
}

MultiplyExpression::MultiplyExpression(Context &input)
    : BinaryExpression(input)
    {}


int MultiplyExpression::Calculate() {
    int lhs = m_input.getValue(m_lhsPos);
    int rhs = m_input.getValue(m_rhsPos);
    m_input.setValue(lhs * rhs, m_outPos);
}

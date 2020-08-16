#include "Expression.h"
#include <iostream>

Expression::Expression(Context &input)
    : m_input(input)
    {
        m_pos = m_input.getPos();
    }

Expression::~Expression() noexcept {}

int Expression::Calculate() {
    return 0;
}

void Expression::writeData(int inValue) {

}

int Expression::readData() {
    return 0;
}

BinaryExpression::BinaryExpression(Context &input, std::vector<string> mask)
    : Expression(input)
    {
        m_lhsPos = getMaskedPos(0, mask);
        m_rhsPos = getMaskedPos(1, mask);
        m_outPos = getMaskedPos(2, mask);
    }

AddExpression::AddExpression(Context &input, std::vector<string> mask)
    : BinaryExpression(input, mask)
    {}


int AddExpression::Calculate() {
    int lhs = m_input.getValue(m_lhsPos);
    int rhs = m_input.getValue(m_rhsPos);
    m_input.setValue(lhs + rhs, m_outPos);
    m_input.setPos(m_pos + 4);
}

MultiplyExpression::MultiplyExpression(Context &input, std::vector<string> mask)
    : BinaryExpression(input, mask)
    {}


int MultiplyExpression::Calculate() {
    int lhs = m_input.getValue(m_lhsPos);
    int rhs = m_input.getValue(m_rhsPos);
    m_input.setValue(lhs * rhs, m_outPos);
    m_input.setPos(m_pos + 4);
}

UnaryExpression::UnaryExpression(Context &input, std::vector<string> mask)
    : Expression(input)
    {
        m_expressionPos = getMaskedPos(0, mask);
    }

InputExpression::InputExpression(Context &input, std::vector<string> mask)
    : UnaryExpression(input, mask)
    {}

void InputExpression::writeData(int inValue) {
    m_input.setValue(inValue, m_expressionPos);
    m_input.setPos(m_pos + 2);
}

OutputExpression::OutputExpression(Context &input, std::vector<string> mask)
    : UnaryExpression(input, mask)
    {}

int OutputExpression::readData() {
    m_input.setPos(m_pos + 2);
    return m_input.getValue(m_expressionPos);
}

int Expression::getMaskedPos(int relativePos, std::vector<string> mask)
{
    if (mask.at(relativePos) == "0")
        return m_input.getValue(m_pos + (relativePos + 1));
    else
        return m_pos + (relativePos + 1);
}
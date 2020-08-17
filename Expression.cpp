#include "Expression.h"
#include <iostream>

Expression::Expression(Context &input)
    : m_input(input)
    {
        m_pos = m_input.getPos();
    }

Expression::~Expression() noexcept {}

int Expression::process() {
    return 0;
}

void Expression::writeData(int inValue) {

}

int Expression::readData() {
    return 0;
}

int Expression::getMaskedPos(int relativePos, std::vector<string> mask)
{
    if (mask.at(relativePos) == "0")
        return m_input.getValue(m_pos + (relativePos + 1));
    else
        return m_pos + (relativePos + 1);
}

OneParamExpression::OneParamExpression(Context &input, std::vector<string> mask)
        : Expression(input)
{
    m_expressionPos = getMaskedPos(0, mask);
}

TwoParamsExpression::TwoParamsExpression(Context &input, std::vector<string> mask)
    : Expression(input)
    {
        m_inPos = getMaskedPos(0, mask);
        m_outPos = getMaskedPos(1, mask);
    }

ThreeParamsExpression::ThreeParamsExpression(Context &input, std::vector<string> mask)
    : Expression(input)
    {
        m_lhsPos = getMaskedPos(0, mask);
        m_rhsPos = getMaskedPos(1, mask);
        m_outPos = getMaskedPos(2, mask);
    }

AddExpression::AddExpression(Context &input, std::vector<string> mask)
    : ThreeParamsExpression(input, mask)
    {}


int AddExpression::process() {
    int lhs = m_input.getValue(m_lhsPos);
    int rhs = m_input.getValue(m_rhsPos);
    m_input.setValue(lhs + rhs, m_outPos);
    m_input.setPos(m_pos + 4);
    m_pos = m_input.getPos();
}

MultiplyExpression::MultiplyExpression(Context &input, std::vector<string> mask)
    : ThreeParamsExpression(input, mask)
    {}


int MultiplyExpression::process() {
    int lhs = m_input.getValue(m_lhsPos);
    int rhs = m_input.getValue(m_rhsPos);
    m_input.setValue(lhs * rhs, m_outPos);
    m_input.setPos(m_pos + 4);
    m_pos = m_input.getPos();
}

InputExpression::InputExpression(Context &input, std::vector<string> mask)
    : OneParamExpression(input, mask)
    {}

void InputExpression::writeData(int inValue) {
    m_input.setValue(inValue, m_expressionPos);
    m_input.setPos(m_pos + 2);
    m_pos = m_input.getPos();
}

OutputExpression::OutputExpression(Context &input, std::vector<string> mask)
    : OneParamExpression(input, mask)
    {}

int OutputExpression::readData() {
    m_input.setPos(m_pos + 2);
    m_pos = m_input.getPos();
    return m_input.getValue(m_expressionPos);
}

JumpIfTrueExpression::JumpIfTrueExpression(Context &input, std::vector<string> mask)
    : TwoParamsExpression(input, mask)
    {}

int JumpIfTrueExpression::process() {
    if (m_input.getValue(m_inPos) != 0)
    {
        m_input.setPos(m_input.getValue(m_outPos));
        m_pos = m_input.getPos();
    }
    else {
        m_input.setPos(m_pos + 3);
        m_pos = m_input.getPos();
    }
}

JumpIfFalseExpression::JumpIfFalseExpression(Context &input, std::vector<string> mask)
        : TwoParamsExpression(input, mask)
    {}

int JumpIfFalseExpression::process() {
    if (m_input.getValue(m_inPos) == 0)
    {
        m_input.setPos(m_input.getValue(m_outPos));
        m_pos = m_input.getPos();
    }
    else {
        m_input.setPos(m_pos + 3);
        m_pos = m_input.getPos();
    }
}

LessThanExpression::LessThanExpression(Context &input, std::vector<string> mask)
    : ThreeParamsExpression(input, mask)
    {}

int LessThanExpression::process() {
    if (m_input.getValue(m_lhsPos) < m_input.getValue(m_rhsPos))
        m_input.setValue(1, m_outPos);
    else
        m_input.setValue(0, m_outPos);
    m_input.setPos(m_pos + 4);
    m_pos = m_input.getPos();
}

EqualsExpression::EqualsExpression(Context &input, std::vector<string> mask)
    : ThreeParamsExpression(input, mask)
    {}

int EqualsExpression::process() {
    if (m_input.getValue(m_lhsPos) == m_input.getValue(m_rhsPos))
        m_input.setValue(1, m_outPos);
    else
        m_input.setValue(0, m_outPos);
    m_input.setPos(m_pos + 4);
    m_pos = m_input.getPos();
}
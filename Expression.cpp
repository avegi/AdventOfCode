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
    m_input.setPos(m_pos + 4);
}

MultiplyExpression::MultiplyExpression(Context &input)
    : BinaryExpression(input)
    {}


int MultiplyExpression::Calculate() {
    int lhs = m_input.getValue(m_lhsPos);
    int rhs = m_input.getValue(m_rhsPos);
    m_input.setValue(lhs * rhs, m_outPos);
    m_input.setPos(m_pos + 4);
}

UnaryExpression::UnaryExpression(Context &input)
    : Expression(input)
    {}

InputExpression::InputExpression(Context &input)
    : UnaryExpression(input)
    {}

void InputExpression::writeData(int inValue) {
    int inPos = m_input.getValue(m_pos + 1);
    m_input.setValue(inValue, inPos);
    m_input.setPos(m_pos + 2);
}

OutputExpression::OutputExpression(Context &input)
    : UnaryExpression(input)
    {}

int OutputExpression::readData() {
    int outPos = m_input.getValue(m_pos + 1);
    m_input.setPos(m_pos + 2);
    return m_input.getValue(outPos);
}
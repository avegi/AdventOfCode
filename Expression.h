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
    explicit Expression(Context &input);
    virtual int Calculate();
    virtual void writeData(int inValue);
    virtual int readData();
    virtual ~Expression();

protected:
    int m_pos;
    Context &m_input;
};

class BinaryExpression : public Expression{
public:
    BinaryExpression(Context &input);

protected:
    int m_lhsPos;
    int m_rhsPos;
    int m_outPos;
};

/**
 *
 */
class AddExpression : public BinaryExpression{
public:
    AddExpression(Context &input);
    int Calculate() override;
};

/**
 *
 */
class MultiplyExpression : public BinaryExpression{
public:
    MultiplyExpression(Context &input);
    int Calculate() override;

};

class UnaryExpression : public Expression{
public:
    UnaryExpression(Context &input);
};

class InputExpression : public UnaryExpression{
public:
    InputExpression(Context &input);
    void writeData(int inValue);
};

class OutputExpression : public UnaryExpression{
public:
    OutputExpression(Context &input);
    int readData();
};
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
    int getMaskedPos(int relativPos, std::vector<string> mask);
protected:
    int m_pos;
    Context &m_input;
};

class BinaryExpression : public Expression{
public:
    BinaryExpression(Context &input, std::vector<string> mask);

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
    AddExpression(Context &input, std::vector<string> mask);
    int Calculate() override;
};

/**
 *
 */
class MultiplyExpression : public BinaryExpression{
public:
    MultiplyExpression(Context &input, std::vector<string> mask);
    int Calculate() override;

};

class UnaryExpression : public Expression{
public:
    UnaryExpression(Context &input, std::vector<string> mask);
protected:
    int m_expressionPos;
};

class InputExpression : public UnaryExpression{
public:
    InputExpression(Context &input, std::vector<string> mask);
    void writeData(int inValue);
};

class OutputExpression : public UnaryExpression{
public:
    OutputExpression(Context &input, std::vector<string> mask);
    int readData();
};
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
    virtual int process();
    virtual void writeData(int inValue);
    virtual int readData();
    virtual ~Expression();

protected:
    int getMaskedPos(int relativPos, std::vector<string> mask);
protected:
    int m_pos;
    Context &m_input;
};

class OneParamExpression : public Expression{
public:
    OneParamExpression(Context &input, std::vector<string> mask);
protected:
    int m_expressionPos;
};

class TwoParamsExpression : public Expression{
public:
    TwoParamsExpression(Context &input, std::vector<string> mask);

protected:
    int m_inPos;
    int m_outPos;
};

class ThreeParamsExpression : public Expression{
public:
    ThreeParamsExpression(Context &input, std::vector<string> mask);

protected:
    int m_lhsPos;
    int m_rhsPos;
    int m_outPos;
};

/**
 *
 */
class AddExpression : public ThreeParamsExpression{
public:
    AddExpression(Context &input, std::vector<string> mask);
    int process() override;
};

/**
 *
 */
class MultiplyExpression : public ThreeParamsExpression{
public:
    MultiplyExpression(Context &input, std::vector<string> mask);
    int process() override;

};



class InputExpression : public OneParamExpression{
public:
    InputExpression(Context &input, std::vector<string> mask);
    void writeData(int inValue) override;
};

class OutputExpression : public OneParamExpression{
public:
    OutputExpression(Context &input, std::vector<string> mask);
    int readData() override;
};

class JumpIfTrueExpression : public TwoParamsExpression{
public:
    JumpIfTrueExpression(Context &input, std::vector<string> mask);
    int process() override;
};

class JumpIfFalseExpression : public TwoParamsExpression{
public:
    JumpIfFalseExpression(Context &input, std::vector<string> mask);
    int process() override;
};

class LessThanExpression : public ThreeParamsExpression{
public:
    LessThanExpression(Context &input, std::vector<string> mask);
    int process() override;
};

class EqualsExpression : public ThreeParamsExpression{
public:
    EqualsExpression(Context &input, std::vector<string> mask);
    int process() override;
};

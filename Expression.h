#pragma once

#include "vector"
#include "memory"
#include "Context.h"

using namespace std;

/** Expression Base Class
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

/** Base class for expressions with one parameters
 */
class OneParamExpression : public Expression{
public:
    OneParamExpression(Context &input, std::vector<string> mask);
protected:
    int m_expressionPos;
};

/** Base class for expressions with two parameters
 */
class TwoParamsExpression : public Expression{
public:
    TwoParamsExpression(Context &input, std::vector<string> mask);

protected:
    int m_inPos;
    int m_outPos;
};

/** Base class for expressions with three parameters
 */
class ThreeParamsExpression : public Expression{
public:
    ThreeParamsExpression(Context &input, std::vector<string> mask);

protected:
    int m_lhsPos;
    int m_rhsPos;
    int m_outPos;
};

/** Add expression
 *  Adds the first two parameters (param1 + param2).
 *  Stores the result at the location marked by the third parameter.
 */
class AddExpression : public ThreeParamsExpression{
public:
    AddExpression(Context &input, std::vector<string> mask);
    int process() override;
};

/** Multiply expression
 *  Multiplies the first two parameters (param1 * param2).
 *  Stores the result at the location marked by the third parameter.
 */
class MultiplyExpression : public ThreeParamsExpression{
public:
    MultiplyExpression(Context &input, std::vector<string> mask);
    int process() override;

};

/** Input expression
 *  Reads the standard input and stores the value marked the expression parameter.
 */
class InputExpression : public OneParamExpression{
public:
    InputExpression(Context &input, std::vector<string> mask);
    void writeData(int inValue) override;
};

/** Output expression
 * Returns the value stored at the expression parameter.
 */
class OutputExpression : public OneParamExpression{
public:
    OutputExpression(Context &input, std::vector<string> mask);
    int readData() override;
};

/** Jump if True expression
 * Checks if the value at first parameter is not zero (param1 != 0).
 * Jumps to position marked by the second parameter if true.
 * Does nothing otherwise.
 */
class JumpIfTrueExpression : public TwoParamsExpression{
public:
    JumpIfTrueExpression(Context &input, std::vector<string> mask);
    int process() override;
};

/** Jump if False expression
 * Checks if the value at first parameter is zero (param1 == 0).
 * Jumps to position marked by the second parameter if true.
 * Does nothing otherwise.
 */
class JumpIfFalseExpression : public TwoParamsExpression{
public:
    JumpIfFalseExpression(Context &input, std::vector<string> mask);
    int process() override;
};

/** Less Than expression
 * Compares the first two parameters (param1 < param2).
 * Stores 1 at the location marked by the third parameter if true.
 * Stores 0 otherwise.
 */
class LessThanExpression : public ThreeParamsExpression{
public:
    LessThanExpression(Context &input, std::vector<string> mask);
    int process() override;
};

/** Equals expression
 * Compares the first two parameters (param1 == param2).
 * Stores 1 at the location marked by the third parameter if true.
 * Stores 0 otherwise.
 */
class EqualsExpression : public ThreeParamsExpression{
public:
    EqualsExpression(Context &input, std::vector<string> mask);
    int process() override;
};


#ifndef ADVENTOFCODE_CONTEXT_H
#define ADVENTOFCODE_CONTEXT_H

#endif //ADVENTOFCODE_CONTEXT_H

#include "vector"

class Context {
public:
    Context(std::vector<int> &opCode, int actualPos)
    : m_pos(actualPos)
    , m_opCode(opCode)
    {}

    void SetPos(int newPos)
    {
        m_pos = newPos;
    }

    int GetPos()
    {
        return m_pos;
    }

    int getValue(int pos)
    {
        return m_opCode[pos];
    }

    void setValue(int value, int pos)
    {
        m_opCode[pos] = value;
    }

private:
    int m_pos;
    std::vector<int> m_opCode;
};
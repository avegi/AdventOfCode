#pragma once

#include "vector"

class Context {
public:
    Context(std::vector<int> tape, int actualPos)
    : m_pos(actualPos)
    , m_tape(std::move(tape))
    {}

    void setPos(int newPos)
    {
        m_pos = newPos;
    }

    int getPos()
    {
        return m_pos;
    }

    int getPos() const
    {
        return m_pos;
    }

    int getValue(int pos)
    {
        return m_tape[pos];
    }

    int getValue(int pos) const
    {
        return m_tape[pos];
    }

    void setValue(int value, int pos)
    {
        m_tape[pos] = value;
    }

private:
    int m_pos;
    std::vector<int> m_tape;
};

#pragma once

#include "vector"

/** Context of the intCode computer
 * Stores the intCode input tape and the actual location of the head.
 */
class Context {
public:
    Context(std::vector<int> tape, int actualPos)
    : m_pos(actualPos)
    , m_tape(std::move(tape))
    {}

/** Move the head to a position.
 * @param newPos: requested head position.
 */
    void setPos(int newPos)
    {
        m_pos = newPos;
    }

/* Returns the head position.
 */
    int getPos() const
    {
        return m_pos;
    }

/* Returns the value stored at the head position.
 */
    int getValue(int pos) const
    {
        return m_tape[pos];
    }

/* Stores the input at the given location
 * Will not move the position of the head.
 */
    void setValue(int value, int pos)
    {
        m_tape[pos] = value;
    }

private:
    int m_pos;
    std::vector<int> m_tape;
};

/* Stores command modes
 * "0": position mode
 * "1": immediate mode
 */
struct CommandMode
{
    CommandMode()
        : modes(std::vector<std::string> {"0", "0", "0"})
        {}
    std::string command;
    std::vector<std::string> modes;
};
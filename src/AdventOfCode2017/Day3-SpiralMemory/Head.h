#pragma once

#include <utility>

enum class Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Head
{
private:
    std::pair<int, int> m_position;
    Direction m_direction;

public:
    Head(std::pair<int, int> m_position, Direction m_direction);

    const std::pair<int, int>& getPosition() const;
    Direction getDirection() const;

    void step();
    void turnLeft();
};


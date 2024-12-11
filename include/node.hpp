#ifndef __PATHFINDER_NODE_HPP__
#define __PATHFINDER_NODE_HPP__

#include <raylib.h>
#include <memory>

#define NODE_SIZE   20.0f

enum State { NONE, START, END, WALL };

class Color;

class Node {
public:
    Node(int x, int y);

    void changeState(State newState);
    void draw() const;

private:
    Rectangle _rect;
    int _x, _y;
    State _state;

    std::unique_ptr<Color> _color;
};


#endif
#ifndef _PATHFINDER_NODE_HPP_
#define _PATHFINDER_NODE_HPP_

#include <raylib.h>
#include <memory>

#define NODE_SIZE   20.0f


enum State { NONE, START, END, PATH, EMPTY, WALL };

class Node {
public:
    Node(Rectangle rect, int x, int y);

    State getState() const;
    void changeState(State newState);

    void draw() const;

private:
    Rectangle _rect;
    int _x, _y;
    State _state;

    std::unique_ptr<Color> _color;
};


#endif
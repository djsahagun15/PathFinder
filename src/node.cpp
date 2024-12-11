#include <raylib.h>

#include "node.hpp"


Node::Node(int x, int y) : _x(x), _y(y) {}


void Node::draw() const {
    DrawRectangleLines(this->_x * 20, this->_y * 20, 20, 20, DARKGRAY);
}
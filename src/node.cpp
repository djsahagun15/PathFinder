#include "node.hpp"


Node::Node(Rectangle rect, int x, int y) : 
_rect(rect),
_x(x), _y(y), 
_state(NONE), 
_color(std::make_unique<Color>(WHITE)) {}


void Node::changeState(State state) {
    this->_state = state;
    switch (this->_state) {
        case NONE : { *this->_color = WHITE; }; break;
        case START : { *this->_color = GREEN; }; break;
        case END : { *this->_color = RED; }; break;
        case WALL : { *this->_color = BLACK; }; break;
        default: break;
    }
}


void Node::draw() const {
    DrawRectangleRec(this->_rect, *this->_color);
    DrawRectangleLinesEx(this->_rect, 1.0f, DARKGRAY);
}
#include "node.hpp"


Node::Node(Rectangle rect, int x, int y) : 
_rect(rect),
_x(x), _y(y), 
_state(EMPTY), 
_color(std::make_unique<Color>(WHITE)) {}


State Node::getState() const { return this->_state; }


void Node::changeState(State state) {
    this->_state = state;
    switch (this->_state) {
        case START : { *this->_color = GREEN; }; break;
        case END : { *this->_color = RED; }; break;
        case EMPTY : { *this->_color = WHITE; }; break;
        case WALL : { *this->_color = BLACK; }; break;

        case NONE :
        default: break;
    }
}


void Node::draw() const {
    DrawRectangleRec(this->_rect, *this->_color);
    DrawRectangleLinesEx(this->_rect, 1.0f, DARKGRAY);
}
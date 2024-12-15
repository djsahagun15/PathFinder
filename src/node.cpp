#include "node.hpp"


Node::Node(Rectangle rect, int x, int y) : 
_rect(rect),
_x(x), _y(y), 
_state(EMPTY), 
_isVisited(false),
_color(std::make_unique<Color>(WHITE)),
_parent(nullptr) {}


State Node::getState() const { return this->_state; }


void Node::setState(State state, bool visited) {
    this->_isVisited = visited;
    
    this->_state = state;
    switch (this->_state) {
        case START : { *this->_color = GREEN; }; break;
        case END : { *this->_color = RED; }; break;
        case PATH : { *this->_color = YELLOW; }; break;
        case EMPTY : { *this->_color = this->_isVisited ? SKYBLUE : WHITE; }; break;
        case WALL : { *this->_color = BLACK; }; break;

        
        case NONE :
        default: break;
    }
}


bool Node::isVisited() const { return this->_isVisited; }


unsigned int Node::getColIndex() const { return this->_x; }


unsigned int Node::getRowIndex() const { return this->_y; }


Node* Node::getParent() const { return this->_parent; }


void Node::setParent(Node* newParent) { this->_parent = newParent; }


void Node::draw() const {
    DrawRectangleRec(this->_rect, *this->_color);
    DrawRectangleLinesEx(this->_rect, 1.0f, DARKGRAY);
}
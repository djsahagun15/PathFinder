#include <limits>
#include <cmath>

#include "node.hpp"
#include "pathfinding_algorithm.hpp"





Node::Node(Rectangle rect, int x, int y) : 
_rect(rect),
_x(x), _y(y), 
_state(EMPTY), 
_isVisited(false),
_color(std::make_unique<Color>(WHITE)),
_parent(nullptr) {
    this->_center = {
        rect.x + rect.width / 2.0f,
        rect.y + rect.height / 2.0f
    };

    this->_gCost = std::numeric_limits<float>::max();
    this->_hCost = 0.0f;
    this->_fCost = this->_gCost + this->_hCost;
}


float Node::getDistance(Node* other) const {
    return manhattanDistance(this->_center, other->_center);
}


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


unsigned int Node::getX() const { return this->_x; }


unsigned int Node::getY() const { return this->_y; }


void Node::setGCost(float gCost) {
    this->_gCost = gCost;
    this->_fCost = this->_gCost + this->_hCost;
}


float Node::getGCost() const { return this->_gCost; }


void Node::setHCost(float hCost) {
    this->_hCost = hCost;
    this->_fCost = this->_gCost + this->_hCost;
}


void Node::setHCost(Node* endNode) {
    this->_hCost = this->getDistance(endNode);
    this->_fCost = this->_gCost + this->_hCost;
}


float Node::getHCost() const { return this->_hCost; }


float Node::getFCost() const { return this->_fCost; }


Node* Node::getParent() const { return this->_parent; }


void Node::setParent(Node* newParent) { this->_parent = newParent; }


void Node::draw() const {
    DrawRectangleRec(this->_rect, *this->_color);
    DrawRectangleLinesEx(this->_rect, 1.0f, DARKGRAY);
}
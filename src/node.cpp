#include <limits>
#include <cmath>
#include <functional>

#include "node.hpp"
#include "pathfinding_algorithm.hpp"

// Constructor for Node class
Node::Node(Rectangle rect, int x, int y) : 
_rect(rect),
_x(x), _y(y), 
_state(State::EMPTY),
_terrain(TerrainType::AIR),
_isVisited(false),
_color(std::make_unique<Color>(WHITE)),
_parent(nullptr) {
    // Calculate the center of the rectangle
    this->_center = {
        rect.x + rect.width / 2.0f,
        rect.y + rect.height / 2.0f
    };

    // Initialize costs
    this->_gCost = std::numeric_limits<float>::max();
    this->_hCost = 0.0f;
    this->_fCost = this->_gCost + this->_hCost;
}

// Set the rectangle and update the center
void Node::setRect(Rectangle rect) {
    this->_rect = rect;
    this->_center = {
        rect.x + rect.width / 2.0f,
        rect.y + rect.height / 2.0f
    };
}

// Calculate the Manhattan distance to another node
unsigned int selectedDistanceFormula = 0;
float Node::getDistance(Node* other) const {
    return DISTANCE_FORMULAS[selectedDistanceFormula](this->_center, other->_center);
}

// Get the state of the node
State Node::getState() const { return this->_state; }

// Set the state of the node and update its color
void Node::setState(State state) {
    this->_state = state;
    switch (this->_state) {
        case State::START : { *this->_color = { 46, 204, 113, 255 }; }; break;
        case State::END : { *this->_color = { 231, 76, 60, 255 }; }; break;
        case State::EMPTY : { this->setTerrain(this->_terrain); }; break;
        case State::WALL : { *this->_color = BLACK; }; break;
        default: break;
    }
}

// Get the weight of the node based on the terrain type
float Node::getWeight() const { return static_cast<float>(this->_terrain); }

// Set the terrain type of the node and update its color
void Node::setTerrain(TerrainType terrain) {
    if (static_cast<int>(terrain) != 0) this->_state = State::EMPTY;
    
    this->_terrain = terrain;

    // Set the color based on the terrain type
    switch (this->_terrain) {
        case TerrainType::AIR : {
            this->_state = State::EMPTY;
            *this->_color = WHITE;
        }; break;
        case TerrainType::GRASS : { *this->_color = { 0, 140, 30, 255 }; }; break;
        case TerrainType::SAND : { *this->_color = { 244, 164, 96, 255 }; }; break;
        case TerrainType::STONE : { *this->_color = { 112, 128, 144, 255 }; }; break;
        case TerrainType::MOUNTAIN : { *this->_color = {139, 137, 137, 255}; }; break;
        case TerrainType::WATER : { *this->_color = {0, 191, 255, 255}; }; break;
        default: {
            this->_state = State::WALL;
            *this->_color = BLACK;
        }; break;
    }

    // If the node has been visited, blend the color with a blue tint
    if (this->_isVisited) *this->_color = ColorAlphaBlend(*this->_color, { 0, 191, 255, 100 }, WHITE);
}

void Node::setVisited(bool visited) {
    this->_isVisited = visited;
    this->setState(this->_state);
}

// Check if the node has been visited
bool Node::isVisited() const { return this->_isVisited; }

// Get the x-coordinate of the node
unsigned int Node::getX() const { return this->_x; }

// Get the y-coordinate of the node
unsigned int Node::getY() const { return this->_y; }

// Set the G cost and update the F cost
void Node::setGCost(float gCost) {
    this->_gCost = gCost;
    this->_fCost = this->_gCost + this->_hCost;
}

// Get the G cost
float Node::getGCost() const { return this->_gCost; }

// Set the H cost and update the F cost
void Node::setHCost(float hCost) {
    this->_hCost = hCost;
    this->_fCost = this->_gCost + this->_hCost;
}

// Calculate and set the H cost based on the distance to the end node
void Node::setHCost(Node* endNode) {
    this->_hCost = this->getDistance(endNode);
    this->_fCost = this->_gCost + this->_hCost;
}

// Get the H cost
float Node::getHCost() const { return this->_hCost; }

// Get the F cost
float Node::getFCost() const { return this->_fCost; }

// Get the parent node
Node* Node::getParent() const { return this->_parent; }

// Set the parent node
void Node::setParent(Node* newParent) { this->_parent = newParent; }

// Draw the node
void Node::draw() const {
    DrawRectangleRec(this->_rect, *this->_color);
    DrawRectangleLinesEx(this->_rect, 1.0f, DARKGRAY);

    if (this->_state == State::PATH) {
        DrawCircleV(this->_center, this->_rect.width * 0.25f, (Color){ 241, 196, 15, 255 });
    }
}
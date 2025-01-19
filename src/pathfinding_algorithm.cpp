#include "pathfinding_algorithm.hpp"

#include <cmath>

// Calculate the Euclidean distance between two points
float euclideanDistance(Vector2 a, Vector2 b) {
    return std::sqrt(
        (a.x - b.x) * (a.x - b.x) +
        (a.y - b.y) * (a.y - b.y)
    );
}


// Calculate the Manhattan distance between two points
float manhattanDistance(Vector2 a, Vector2 b) {
    return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}


// Calculate the Chebyshev distance between two points
float chebyshevDistance(Vector2 a, Vector2 b) {
    return std::max(std::abs(a.x - b.x), std::abs(a.y - b.y));
}


// Constructor for PathfindingAlgorithm class
PathfindingAlgorithm::PathfindingAlgorithm(std::shared_ptr<Grid> grid) : _grid(grid), _isFirstIter(true) {}


// Function to get the neighboring nodes of a given node
std::vector<Node*> PathfindingAlgorithm::getNeighbors(Node* node) const {
    return this->_grid->getNeighbors(node);
}


// Function to trace the path from the end node to the start node
void PathfindingAlgorithm::tracePath(Node* start, Node* end) {
    Node* current = end;
    while (current) {
        if (current != start && current != end) {
            current->setState(State::PATH);
        }
        current = current->getParent();
    }
}
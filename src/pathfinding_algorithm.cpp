#include "pathfinding_algorithm.hpp"

#include <cmath>

float euclideanDistance(Vector2 a, Vector2 b) {
    return std::sqrt(
        (a.x - b.x) * (a.x - b.x) +
        (a.y - b.y) * (a.y - b.y)
    );
}


float manhattanDistance(Vector2 a, Vector2 b) {
    return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}


PathfindingAlgorithm::PathfindingAlgorithm(std::shared_ptr<Grid> grid) : _grid(grid) {}


std::vector<Node*> PathfindingAlgorithm::getNeighbors(Node* node) const {
    return this->_grid->getNeighbors(node);
}


void PathfindingAlgorithm::tracePath(Node* start, Node* end) {
    Node* current = end;
    while (current) {
        if (current != start && current != end) {
            current->setState(State::PATH);
        }
        current = current->getParent();
    }
}
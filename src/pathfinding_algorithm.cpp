#include "pathfinding_algorithm.hpp"


PathfindingAlgorithm::PathfindingAlgorithm(std::shared_ptr<Grid> grid) : _grid(grid) {}


std::vector<Node*> PathfindingAlgorithm::getNeighbors(Node* node) const {
    return this->_grid->getNeighbors(node);
}


#include <iostream>
void PathfindingAlgorithm::tracePath(Node* start, Node* end) {
    Node* current = end;
    while (current) {
        if (current != start && current != end) {
            current->setState(State::PATH);
        }
        current = current->getParent();
    }
}
#include "astar.hpp"

#include <queue>


AStar::AStar(std::shared_ptr<Grid> grid) : PathfindingAlgorithm(grid) {}


void AStar::findPath(Node* start, Node* end) {
    std::priority_queue<Node*, std::vector<Node*>, CompareNode> nodeQueue;

    start->setGCost(0.0f);
    start->setHCost(end);
    nodeQueue.push(start);
    
    while (!nodeQueue.empty()) {
        Node* current = nodeQueue.top();
        nodeQueue.pop();

        State currentState = current->getState();
        current->setState(currentState, true);

        if (current == end) {
            tracePath(start, end);
            break;
        }

        std::vector<Node*> neighbors = this->_grid->getNeighbors(current);
        for (Node* neighbor : neighbors) {
            State neighborState = neighbor->getState();

            if (neighborState == State::WALL || neighbor->isVisited()) continue;
            
            float gCost = current->getGCost() + manhattanDistance(current->getCenter(), neighbor->getCenter());

            if (gCost < neighbor->getGCost()) {
                neighbor->setState(neighborState, true);
                neighbor->setGCost(gCost);
                neighbor->setHCost(end);
                neighbor->setParent(current);

                nodeQueue.push(neighbor);
            }
        }
    }
}
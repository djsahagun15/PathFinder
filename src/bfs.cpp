#include "bfs.hpp"

#include <queue>


BFS::BFS(std::shared_ptr<Grid> grid) : PathfindingAlgorithm(grid) {}


void BFS::findPath(Node* start, Node* end) {
    std::queue<Node*> nodeQueue;
    nodeQueue.push(start);

    while (!nodeQueue.empty()) {
        Node* current = nodeQueue.front();
        nodeQueue.pop();

        State currentState = current->getState();
        current->setState(currentState, true);

        if (current == end) {
            tracePath(start, end);
            break;
        }
        
        std::vector<Node*> neighbors = this->getNeighbors(current);
        for (Node* neighbor : neighbors) {
            State neighborState = neighbor->getState();

            if (neighborState != State::WALL && !neighbor->isVisited()) {
                neighbor->setState(neighborState, true);
                neighbor->setParent(current);

                nodeQueue.push(neighbor);
            }
        }
    }
}
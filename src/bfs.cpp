#include "bfs.hpp"

#include <queue>


BFS::BFS(std::shared_ptr<Grid> grid) : PathfindingAlgorithm(grid) {}


#include <iostream>
Node* BFS::findPath(Node* start, Node* end) {
    std::queue<Node*> nodeQueue;
    nodeQueue.push(start);

    while (!nodeQueue.empty()) {
        Node* current = nodeQueue.front();
        nodeQueue.pop();

        current->setVisited(true);

        if (current == end) {
            tracePath(start, end);
            break;
        }
        
        std::vector<Node*> neighbors = this->getNeighbors(current);
        for (Node* neighbor : neighbors) {
            if (!neighbor->isVisited()) {
                neighbor->setVisited(true);
                neighbor->setParent(current);

                nodeQueue.push(neighbor);
            }
        }
    }

    return nullptr;
}
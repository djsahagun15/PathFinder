#include "dijkstra.hpp"

#include <queue>


Dijkstra::Dijkstra(std::shared_ptr<Grid> grid) : PathfindingAlgorithm(grid) {}


void Dijkstra::findPath(Node* start, Node* end, float speed) {
    static int added = 0;

    if (this->_isFirstIter) {
        while (!this->_queue.empty()) this->_queue.pop();
        
        start->setGCost(0.0f);

        this->_queue.push(start);
        added++;

        this->_isFirstIter = false;
    }

    int maxIter = speed == 0.0f ? this->_grid->getColRowCount() : added * speed + 1;
    added = 0;
    
    do {
        if (this->_queue.empty()) {
            this->_isFirstIter = true;
            
            added = 0;
            break;
        }
        
        Node* current = this->_queue.top();
        this->_queue.pop();

        State currentState = current->getState();
        current->setState(currentState, true);

        if (current == end) {
            this->tracePath(start, end);
            this->reset();
            
            added = 0;
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
                neighbor->setParent(current);

                this->_queue.push(neighbor);

                added++;
            }
        }
    } while (--maxIter);
}


void Dijkstra::reset() {
    this->_isFirstIter = true;
    while (!this->_queue.empty()) this->_queue.pop();
}


bool Dijkstra::isSearchComplete() {
    return this->_queue.empty();
}
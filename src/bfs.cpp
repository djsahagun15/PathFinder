#include <queue>
#include <limits>

#include "bfs.hpp"


BFS::BFS(std::shared_ptr<Grid> grid) : PathfindingAlgorithm(grid) {}


void BFS::findPath(Node* start, Node* end, float speed) {
    static int added = 0;

    if (this->_isFirstIter) {
        while (!this->_queue.empty()) this->_queue.pop();
        
        this->_queue.push(start);
        added++;

        this->_isFirstIter = false;
    }

    int maxIter = speed == 0.0f ? this->_grid->getColRowCount() : added * speed + 1;
    added = 0;

    do {
        if (this->_queue.empty()) break;

        Node* current = this->_queue.front();
        this->_queue.pop();

        State currentState = current->getState();
        current->setState(currentState, true);

        if (current == end) {
            this->tracePath(start, end);
            this->reset();

            added = 0;
            break;
        }
        
        std::vector<Node*> neighbors = this->getNeighbors(current);
        for (Node* neighbor : neighbors) {
            State neighborState = neighbor->getState();

            if (neighborState != State::WALL && !neighbor->isVisited()) {
                neighbor->setState(neighborState, true);
                neighbor->setParent(current);

                this->_queue.push(neighbor);

                added++;
            }
        }
    } while (--maxIter);
}


void BFS::reset() {
    this->_isFirstIter = true;
    while (!this->_queue.empty()) this->_queue.pop();
}


bool BFS::isSearchComplete() {
    return this->_queue.empty();
}
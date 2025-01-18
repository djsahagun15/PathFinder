#include <queue>
#include <limits>

#include "bfs.hpp"


BFS::BFS(std::shared_ptr<Grid> grid) : PathfindingAlgorithm(grid) {}


void BFS::findPath(Node* start, Node* end, float speed) {
    static int added = 0;

    if (this->_isFirstIter) {
        // Reset the added counter and clear the queue for the first iteration
        added = 0;
        while (!this->_queue.empty()) this->_queue.pop();

        start->setVisited(true);
        
        // Add the start node to the queue
        this->_queue.push(start);
        added++;

        this->_isFirstIter = false;
    }

    // Determine the maximum number of iterations based on speed
    int maxIter = speed == 0.0f ? this->_grid->getColRowCount() : added * speed + 1;
    added = 0;

    do {
        if (this->_queue.empty()) {
            // If the queue is empty, reset for the next search
            this->_isFirstIter = true;
            
            added = 0;
            break;
        }

        // Get the current node from the front of the queue
        Node* current = this->_queue.front();
        this->_queue.pop();

        if (current == end) {
            // If the end node is reached, trace the path and reset
            this->tracePath(start, end);
            this->reset();

            added = 0;
            break;
        }
        
        // Get the neighbors of the current node
        std::vector<Node*> neighbors = this->getNeighbors(current);
        for (Node* neighbor : neighbors) {
            if (neighbor->getState() != State::WALL && !neighbor->isVisited()) {
                neighbor->setParent(current);
                neighbor->setVisited(true);

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
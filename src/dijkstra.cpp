#include "dijkstra.hpp"

#include <queue>
#include <unordered_set>


Dijkstra::Dijkstra(std::shared_ptr<Grid> grid) : PathfindingAlgorithm(grid) {}


void Dijkstra::findPath(Node* start, Node* end, float speed) {
    static int added = 0;
    static std::unordered_set<Node*> tracker;

    // Initialize on the first iteration
    if (this->_isFirstIter) {
        added = 0;
        while (!this->_queue.empty()) this->_queue.pop();
        tracker.clear();
        
        start->setGCost(0.0f);

        this->_queue.push(start);
        added++;

        this->_isFirstIter = false;
    }

    // Determine the maximum number of iterations for this step
    int maxIter = speed == 0.0f ? this->_grid->getColRowCount() : added * speed + 1;
    added = 0;
    
    do {
        // If the queue is empty, the search is complete
        if (this->_queue.empty()) {
            this->_isFirstIter = true;
            
            added = 0;
            break;
        }
        
        // Get the node with the smallest cost
        Node* current = this->_queue.top();
        this->_queue.pop();

        // Mark the current node as visited
        current->setVisited(true);

        // If the end node is reached, trace the path and reset
        if (current == end) {
            this->tracePath(start, end);
            this->reset();
            
            added = 0;
            break;
        }

        // Process each neighbor of the current node
        std::vector<Node*> neighbors = this->_grid->getNeighbors(current);
        for (Node* neighbor : neighbors) {
            // Skip walls and visited nodes
            if (neighbor->getState() == State::WALL || neighbor->isVisited()) continue;
            
            float gCost = current->getGCost() + current->getDistance(neighbor) * neighbor->getWeight();

            // If a shorter path to the neighbor is found
            if (gCost < neighbor->getGCost()) {
                neighbor->setGCost(gCost);
                neighbor->setParent(current);

                if (!tracker.contains(neighbor)) {
                    this->_queue.push(neighbor);
                    tracker.insert(neighbor);
                }

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
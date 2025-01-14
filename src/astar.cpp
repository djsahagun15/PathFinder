#include "astar.hpp"

#include <queue>
#include <algorithm>


AStar::AStar(std::shared_ptr<Grid> grid) : PathfindingAlgorithm(grid) {}


void AStar::findPath(Node* start, Node* end, float speed) {
    static int added = 0;

    if (this->_isFirstIter) {
        added = 0;
        this->_openSet.clear();
        
        start->setGCost(0.0f);
        start->setHCost(end);

        this->_openSet.push_back(start);
        added++;

        this->_isFirstIter = false;
    }

    int maxIter = speed == 0.0f ? this->_grid->getColRowCount() : added * speed + 1;
    added = 0;
    
    do {
        if (this->_openSet.empty()) {
            this->_isFirstIter = true;

            added = 0;
            break;
        }

        auto lowest = this->_openSet.begin();
        for (auto it = lowest + 1; it != this->_openSet.end(); it++) {
            if ((*it)->getFCost() <= (*lowest)->getFCost()) {
                if ((*it)->getHCost() < (*lowest)->getHCost()) lowest = it;
            }
        }
        
        Node* current = *lowest;
        this->_openSet.erase(lowest);

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

            bool inOpenSet = std::find(this->_openSet.begin(), this->_openSet.end(), neighbor) != this->_openSet.end();
            
            float gCost = current->getGCost() + current->getDistance(neighbor);

            if (gCost < neighbor->getGCost() || !inOpenSet) {
                neighbor->setGCost(gCost);
                neighbor->setHCost(end);
                neighbor->setParent(current);

                if (!inOpenSet) this->_openSet.push_back(neighbor);

                added++;
            }
        }
    } while (--maxIter);
}


void AStar::reset() {
    this->_isFirstIter = true;
    this->_openSet.clear();
}


bool AStar::isSearchComplete() {
    return this->_openSet.empty();
}
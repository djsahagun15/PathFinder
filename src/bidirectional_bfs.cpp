#include "bidirectional_bfs.hpp"

#include <cmath>
#include <algorithm>
#include <unordered_map>


BiDirectionalBFS::BiDirectionalBFS(std::shared_ptr<Grid> grid) : PathfindingAlgorithm(grid) {}


void BiDirectionalBFS::findPath(Node* start, Node* end, float speed) {
    static int startAdded = 0, endAdded = 0;
    
    static std::unordered_map<Node*, Node*> startVisited;
    static std::unordered_map<Node*, Node*> endVisited;
    
    if (this->_isFirstIter) {
        while (!this->_startQueue.empty()) this->_startQueue.pop();
        while (!this->_endQueue.empty()) this->_endQueue.pop();

        startVisited.clear();
        endVisited.clear();

        start->setVisited(true);
        end->setVisited(true);
        
        this->_startQueue.push(start);
        this->_endQueue.push(end);

        startAdded = 1;
        endAdded = 1;

        this->_isFirstIter = false;
    }

    int maxIter = speed == 0.0f ? this->_grid->getColRowCount() : std::max(startAdded, endAdded) * speed + 1;
    startAdded = endAdded = 0;

    do {
        Node* mid = nullptr;
        
        mid = this->expand(this->_startQueue, startVisited, endVisited, startAdded);
        if (mid != nullptr) {
            this->tracePath(start, end, mid, startVisited, endVisited);
            this->reset();
            break;
        }

        mid = this->expand(this->_endQueue, endVisited, startVisited, endAdded);
        if (mid != nullptr) {
            this->tracePath(start, end, mid, startVisited, endVisited);
            this->reset();
            break;
        }
    } while (--maxIter);
}


Node* BiDirectionalBFS::expand(
std::queue<Node*>& currentQueue, std::unordered_map<Node*, Node*>& currentVisited, 
const std::unordered_map<Node*, Node*>& otherVisited, int& addedCounter) {
    if (currentQueue.empty()) return nullptr;

    Node* current = currentQueue.front();
    currentQueue.pop();

    if (otherVisited.contains(current)) return current;

    for (Node* neighbor : this->getNeighbors(current)) {
        if (neighbor->getState() == State::WALL) continue;

        if (!currentVisited.contains(neighbor)) {
            neighbor->setVisited(true);

            currentQueue.push(neighbor);
            currentVisited[neighbor] = current;

            addedCounter++;

            if (otherVisited.contains(neighbor)) return neighbor;
        }
    }

    return nullptr;
}


void BiDirectionalBFS::tracePath(Node* start, Node* end, Node* mid, std::unordered_map<Node*, Node*>& startVisited, std::unordered_map<Node*, Node*>& endVisited) {
    Node* tracer = mid;
    while (tracer != start) {
        tracer->setState(State::PATH);
        tracer = startVisited[tracer];
    }

    tracer = mid;
    while (tracer != end) {
        tracer->setState(State::PATH);
        tracer = endVisited[tracer];
    }
}


void BiDirectionalBFS::reset() {
    this->_isFirstIter = true;
    while (!this->_startQueue.empty()) this->_startQueue.pop();
    while (!this->_endQueue.empty()) this->_endQueue.pop();
}


bool BiDirectionalBFS::isSearchComplete() {
    return this->_startQueue.empty() && this->_endQueue.empty();
}
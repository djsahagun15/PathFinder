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
        if (!this->_startQueue.empty()) {
            Node* current = this->_startQueue.front();
            this->_startQueue.pop();

            if (endVisited.find(current) != endVisited.end()) {
                this->tracePath(start, end, current, startVisited, endVisited);
                this->reset();
                break;
            }
            
            for (Node* neighbor : this->getNeighbors(current)) {
                if (neighbor->getState() == State::WALL) continue;
                
                if (startVisited.find(neighbor) == startVisited.end()) {
                    neighbor->setVisited(true);
                    
                    this->_startQueue.push(neighbor);
                    startVisited[neighbor] = current;

                    startAdded++;

                    if (endVisited.find(neighbor) != endVisited.end()) {
                        this->tracePath(start, end, neighbor, startVisited, endVisited);
                        this->reset();
                        break;
                    }
                }
            }
        }

        if (!this->_endQueue.empty()) {
            Node* current = this->_endQueue.front();
            this->_endQueue.pop();

            if (startVisited.find(current) != startVisited.end()) {
                this->tracePath(start, end, current, startVisited, endVisited);
                this->reset();
                break;
            }
            
            for (Node* neighbor : this->getNeighbors(current)) {
                if (neighbor->getState() == State::WALL) continue;
                
                if (endVisited.find(neighbor) == endVisited.end()) {
                    neighbor->setVisited(true);
                    
                    this->_endQueue.push(neighbor);
                    endVisited[neighbor] = current;

                    endAdded++;

                    if (startVisited.find(neighbor) != startVisited.end()) {
                        this->tracePath(start, end, neighbor, startVisited, endVisited);
                        this->reset();
                        break;
                    }
                }
            }
        }
    } while (--maxIter);
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
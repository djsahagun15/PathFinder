#ifndef _PATHFINDER_DIJKSTRA_HPP_
#define _PATHFINDER_DIJKSTRA_HPP_

#include <queue>

#include "pathfinding_algorithm.hpp"


class Dijkstra : public PathfindingAlgorithm {
public:
    Dijkstra(std::shared_ptr<Grid> grid);

    void findPath(Node* start, Node* end, float speed = 0.0f) override;
    void reset() override;
    bool isSearchComplete() override;

private:
    struct CompareNode {
        bool operator()(Node* lhs, Node* rhs) const {
            return lhs->getGCost() > rhs->getGCost();
        }
    };

    std::priority_queue<Node*, std::vector<Node*>, CompareNode> _queue;
};


#endif
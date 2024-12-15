#ifndef _PATHFINDER_DIJKSTRA_HPP_
#define _PATHFINDER_DIJKSTRA_HPP_

#include "pathfinding_algorithm.hpp"


class Dijkstra : public PathfindingAlgorithm {
public:
    Dijkstra(std::shared_ptr<Grid> grid);

    void findPath(Node* start, Node* end) override;

private:
    struct CompareNode {
        bool operator()(Node* lhs, Node* rhs) const {
            return lhs->getGCost() > rhs->getGCost();
        }
    };
};


#endif
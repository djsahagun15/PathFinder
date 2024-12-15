#ifndef _PATHFINDER_ASTAR_HPP_
#define _PATHFINDER_ASTAR_HPP_

#include "pathfinding_algorithm.hpp"


class AStar : public PathfindingAlgorithm {
public:
    AStar(std::shared_ptr<Grid> grid);

    void findPath(Node* start, Node* end) override;

private:
    struct CompareNode {
        bool operator()(Node* lhs, Node* rhs) const {
            return lhs->getFCost() > rhs->getFCost();
        }
    };
};


#endif
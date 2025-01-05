#ifndef _PATHFINDER_ASTAR_HPP_
#define _PATHFINDER_ASTAR_HPP_

#include <queue>

#include "pathfinding_algorithm.hpp"


class AStar : public PathfindingAlgorithm {
public:
    AStar(std::shared_ptr<Grid> grid);

    void findPath(Node* start, Node* end, float speed = 0.0f) override;
    void reset() override;
    bool isSearchComplete() override;

private:
    std::vector<Node*> _openSet;
};


#endif
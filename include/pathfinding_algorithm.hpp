#ifndef _PATHFINDER_PATHFINDING_ALGORITHM_HPP_
#define _PATHFINDER_PATHFINDING_ALGORITHM_HPP_

#include "grid.hpp"


class PathfindingAlgorithm {
public:
    virtual ~PathfindingAlgorithm() = default;

    virtual Node* findPath(Node* start, Node* end) = 0;

protected:
    PathfindingAlgorithm(std::shared_ptr<Grid> grid);

    std::vector<std::unique_ptr<Node>> getNeighbors(Node* node);

    std::shared_ptr<Grid> _grid;
};


#endif
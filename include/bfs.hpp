#ifndef _PATHFINDER_BFS_HPP_
#define _PATHFINDER_BFS_HPP_

#include "pathfinding_algorithm.hpp"


class BFS : public PathfindingAlgorithm {
public:
    BFS(std::shared_ptr<Grid> grid);

    void findPath(Node* start, Node* end) override;
};


#endif
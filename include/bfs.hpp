#ifndef _PATHFINDER_BFS_HPP_
#define _PATHFINDER_BFS_HPP_

#include <queue>

#include "pathfinding_algorithm.hpp"


class BFS : public PathfindingAlgorithm {
public:
    BFS(std::shared_ptr<Grid> grid);

    void findPath(Node* start, Node* end, float speed = 0.0f) override;
    void reset() override;
    bool isSearchComplete() override;

private:
    std::queue<Node*> _queue;
};


#endif
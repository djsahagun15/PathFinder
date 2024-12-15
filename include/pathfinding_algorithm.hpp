#ifndef _PATHFINDER_PATHFINDING_ALGORITHM_HPP_
#define _PATHFINDER_PATHFINDING_ALGORITHM_HPP_

#include "grid.hpp"


float euclideanDistance(Vector2 a, Vector2 b);
float manhattanDistance(Vector2 a, Vector2 b);


class PathfindingAlgorithm {
public:
    virtual ~PathfindingAlgorithm() = default;

    virtual void findPath(Node* start, Node* end) = 0;

protected:
    PathfindingAlgorithm(std::shared_ptr<Grid> grid);

    std::vector<Node*> getNeighbors(Node* node) const;
    void tracePath(Node* start, Node* end);

    std::shared_ptr<Grid> _grid;
};


#endif
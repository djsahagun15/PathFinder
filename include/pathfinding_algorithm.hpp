#ifndef _PATHFINDER_PATHFINDING_ALGORITHM_HPP_
#define _PATHFINDER_PATHFINDING_ALGORITHM_HPP_

#include "grid.hpp"


float euclideanDistance(Vector2 a, Vector2 b);
float manhattanDistance(Vector2 a, Vector2 b);


class PathfindingAlgorithm {
public:
    virtual ~PathfindingAlgorithm() = default;

    virtual void findPath(Node* start, Node* end, float speed = 0.0f) = 0;
    virtual void reset() = 0;
    virtual bool isSearchComplete() = 0;

protected:
    PathfindingAlgorithm(std::shared_ptr<Grid> grid);

    std::vector<Node*> getNeighbors(Node* node) const;
    void tracePath(Node* start, Node* end);

    std::shared_ptr<Grid> _grid;

    bool _isFirstIter;
};


#endif
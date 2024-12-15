#ifndef _PATHFINDER_HPP_
#define _PATHFINDER_HPP_

#include "grid.hpp"
#include "pathfinding_algorithm.hpp"

#include <functional>


class PathFinder {
public:
    PathFinder(unsigned int cols, unsigned int rows);
    ~PathFinder();

    void run();

private:
    void update();
    void draw() const;

    void reset();
    void clearPath();

    std::shared_ptr<Grid> _grid;

    std::unique_ptr<PathfindingAlgorithm> _BFS;
    std::unique_ptr<PathfindingAlgorithm> _Dijkstra;

    std::function<void(Node*, Node*)> _selectedAlgorithm;
};


#endif
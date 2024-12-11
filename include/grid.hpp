#ifndef __PATHFINDER_GRID_HPP__
#define __PATHFINDER_GRID_HPP__

#include <vector>
#include <memory>

#include "node.hpp"


class Grid {
public:
    Grid(unsigned int cols, unsigned int rows);
    ~Grid() = default;

    void draw() const;

private:
    std::vector<std::vector<std::unique_ptr<Node>>> _matrix;
    unsigned int _cols, _rows;
};


#endif
#ifndef __PATHFINDER_HPP__
#define __PATHFINDER_HPP__

#include <memory>
#include "grid.hpp"


class PathFinder {
public:
    PathFinder(unsigned int cols, unsigned int rows);
    ~PathFinder();

    void run();

private:
    void update();
    void draw() const;

    std::unique_ptr<Grid> _grid;
};


#endif
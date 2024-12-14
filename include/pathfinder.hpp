#ifndef _PATHFINDER_HPP_
#define _PATHFINDER_HPP_

#include "grid.hpp"


class PathFinder {
public:
    PathFinder(unsigned int cols, unsigned int rows);
    ~PathFinder();

    void run();

private:
    void update();
    void draw() const;

    std::shared_ptr<Grid> _grid;
};


#endif
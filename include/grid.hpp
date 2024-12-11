#ifndef __PATHFINDER_GRID_HPP__
#define __PATHFINDER_GRID_HPP__

#include <vector>

#include "node.hpp"


class Grid {
public:
    Grid(unsigned int cols, unsigned int rows);
    ~Grid() = default;

    void update();
    void draw() const;

private:
    bool isMouseInRect(Vector2 mouse) const;
    Node* getNode(Vector2 mouse) const;

    std::vector<std::vector<std::unique_ptr<Node>>> _matrix;
    unsigned int _cols, _rows;

    Rectangle _rect;
};


#endif
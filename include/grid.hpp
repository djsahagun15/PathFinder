#ifndef _PATHFINDER_GRID_HPP_
#define _PATHFINDER_GRID_HPP_

#include <vector>
#include "node.hpp"


class Grid {
public:
    Grid(unsigned int cols, unsigned int rows);
    ~Grid() = default;

    float getWidth() const;
    float getHeight() const;

    unsigned int getCols() const;
    unsigned int getRows() const;

    void update();
    void draw() const;

private:
    bool isMouseInRect(Vector2 mouse) const;
    Node* getNode(Vector2 mouse) const;

    std::vector<std::vector<std::unique_ptr<Node>>> _matrix;
    Node* _startNode;
    Node* _endNode;
    
    unsigned int _cols, _rows;

    Rectangle _rect;
};


#endif
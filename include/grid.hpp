#ifndef _PATHFINDER_GRID_HPP_
#define _PATHFINDER_GRID_HPP_

#include <vector>
#include "node.hpp"


class Grid {
public:
    Grid(unsigned int cols, unsigned int rows);
    ~Grid() = default;

    void resize(unsigned int cols, unsigned int rows);

    float getWidth() const;
    float getHeight() const;

    unsigned int getColCount() const;
    unsigned int getRowCount() const;
    unsigned int getColRowCount() const;

    std::vector<Node*> getNeighbors(Node* node) const;

    bool shouldUpdatePath() const;
    void resetShouldUpdatePathFlag();
    
    void clearPath();
    void reset();

    void update();
    void draw() const;

private:
    bool isMouseInRect(Vector2 mouse) const;
    Node* getNode(Vector2 mouse) const;

    std::vector<std::vector<std::unique_ptr<Node>>> _matrix;
    Node* _startNode;
    Node* _endNode;

    bool _shouldUpdatePath;
    
    unsigned int _cols, _rows;

    float _nodeSize;

    Rectangle _rect;

    friend class PathFinder;
};


#endif
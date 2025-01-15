#ifndef _PATHFINDER_GRID_HPP_
#define _PATHFINDER_GRID_HPP_

#include <vector>
#include "node.hpp"

/**
 * @class Grid
 * @brief Represents a grid of nodes for pathfinding.
 */
class Grid {
public:
    /**
     * @brief Constructs a Grid with the specified number of columns and rows.
     * @param cols Number of columns.
     * @param rows Number of rows.
     */
    Grid(unsigned int cols, unsigned int rows);
    ~Grid() = default;

    /**
     * @brief Resizes the grid to the specified number of columns and rows.
     * @param cols New number of columns.
     * @param rows New number of rows.
     */
    void resize(unsigned int cols, unsigned int rows);

    /**
     * @brief Gets the width of the grid.
     * @return Width of the grid.
     */
    float getWidth() const;

    /**
     * @brief Gets the height of the grid.
     * @return Height of the grid.
     */
    float getHeight() const;

    /**
     * @brief Gets the number of columns in the grid.
     * @return Number of columns.
     */
    unsigned int getColCount() const;

    /**
     * @brief Gets the number of rows in the grid.
     * @return Number of rows.
     */
    unsigned int getRowCount() const;

    /**
     * @brief Gets the total number of columns and rows in the grid.
     * @return Total number of columns and rows.
     */
    unsigned int getColRowCount() const;

    /**
     * @brief Gets the neighboring nodes of the specified node.
     * @param node The node to get neighbors for.
     * @return Vector of neighboring nodes.
     */
    std::vector<Node*> getNeighbors(Node* node) const;

    /**
     * @brief Checks if the path should be updated.
     * @return True if the path should be updated, false otherwise.
     */
    bool shouldUpdatePath() const;

    /**
     * @brief Resets the flag indicating whether the path should be updated.
     */
    void resetShouldUpdatePathFlag();
    
    /**
     * @brief Clears the current path.
     */
    void clearPath();

    /**
     * @brief Resets the grid to its initial state.
     */
    void reset();

    /**
     * @brief Updates the grid.
     */
    void update();

    /**
     * @brief Draws the grid.
     */
    void draw() const;

private:
    /**
     * @brief Checks if the mouse is within the grid's rectangle.
     * @param mouse Mouse position.
     * @return True if the mouse is within the rectangle, false otherwise.
     */
    bool isMouseInRect(Vector2 mouse) const;

    /**
     * @brief Gets the node at the specified mouse position.
     * @param mouse Mouse position.
     * @return Pointer to the node at the mouse position.
     */
    Node* getNode(Vector2 mouse) const;

    // Matrix of nodes.
    std::vector<std::vector<std::unique_ptr<Node>>> _matrix;


    // Starting node for pathfinding.
    Node* _startNode;

    // Ending node for pathfinding.
    Node* _endNode;


    // Flag indicating whether the path should be updated.
    bool _shouldUpdatePath;

    
    // Number of columns and rows.
    unsigned int _cols, _rows;

    // Size of each node.
    float _nodeSize;


    // Rectangle representing the grid's area.
    Rectangle _rect;

    friend class PathFinder;
};


#endif
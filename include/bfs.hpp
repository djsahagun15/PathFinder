#ifndef _PATHFINDER_BFS_HPP_
#define _PATHFINDER_BFS_HPP_

#include <queue>

#include "pathfinding_algorithm.hpp"

/**
 * @class BFS
 * @brief Implements the Breadth-First Search algorithm for pathfinding.
 */
class BFS : public PathfindingAlgorithm {
public:
    /**
     * @brief Constructs a BFS object with a given grid.
     * @param grid A shared pointer to the grid on which the pathfinding will be performed.
     */
    BFS(std::shared_ptr<Grid> grid);

    /**
     * @brief Finds the path from the start node to the end node.
     * @param start The starting node.
     * @param end The ending node.
     * @param speed The speed of the pathfinding process (default is 0.0f).
     */
    void findPath(Node* start, Node* end, float speed = 0.0f) override;

    /**
     * @brief Resets the pathfinding algorithm to its initial state.
     */
    void reset() override;

    /**
     * @brief Checks if the search is complete.
     * @return True if the search is complete, false otherwise.
     */
    bool isSearchComplete() override;

private:
    // Queue used for the BFS algorithm.
    std::queue<Node*> _queue;
};


#endif
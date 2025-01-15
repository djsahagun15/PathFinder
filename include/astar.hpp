#ifndef _PATHFINDER_ASTAR_HPP_
#define _PATHFINDER_ASTAR_HPP_

#include <queue>

#include "pathfinding_algorithm.hpp"

/**
 * @class AStar
 * @brief Implements the A* pathfinding algorithm.
 */
class AStar : public PathfindingAlgorithm {
public:
    /**
     * @brief Constructs an AStar object with a given grid.
     * @param grid A shared pointer to the grid on which the pathfinding will be performed.
     */
    AStar(std::shared_ptr<Grid> grid);

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
    // The set of nodes to be evaluated.
    std::vector<Node*> _openSet;
};


#endif
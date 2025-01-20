#ifndef _PATHFINDER_BIDIRECTIONAL_BFS_HPP_
#define _PATHFINDER_BIDIRECTIONAL_BFS_HPP_

#include <queue>
#include <unordered_map>

#include "pathfinding_algorithm.hpp"

/**
 * @class BiDirectionalBFS
 * @brief Implements the Bi-Directional Breadth-First Search algorithm for pathfinding.
 */
class BiDirectionalBFS : public PathfindingAlgorithm {
public:
    /**
     * @brief Constructs a BiDirectionalBFS object with a given grid.
     * @param grid A shared pointer to the grid on which the pathfinding will be performed.
     */
    BiDirectionalBFS(std::shared_ptr<Grid> grid);

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
    void tracePath(Node* start, Node* end, Node* mid, std::unordered_map<Node*, Node*>& startVisited, std::unordered_map<Node*, Node*>& endVisited);

    Node* expand(std::queue<Node*>& currentQueue, std::unordered_map<Node*, Node*>& currentVisited, 
                const std::unordered_map<Node*, Node*>& otherVisited, int& addedCounter);

    // Queue used for the BiDirectionalBFS algorithm.
    std::queue<Node*> _startQueue;
    std::queue<Node*> _endQueue;
};


#endif
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
    /**
     * @brief Traces the path from start node to the end node.
     * 
     * @param start The starting node.
     * @param end The ending node.
     * @param mid The midpoint/intersection node.
     * @param startVisited A map containing the visited node from the start node.
     * @param endVisited A map containing the visited node from the end node.
     */
    void tracePath(Node* start, Node* end, Node* mid, std::unordered_map<Node*, Node*>& startVisited, std::unordered_map<Node*, Node*>& endVisited);

    /**
     * @brief Expand the current queue. This processes the next node in the specified queue and explores its neighbors.
     * @return The intersecting node, if found. Otherwise, it will return `nullptr`.
     * 
     * @param currentQueue The current search direction.
     * @param currentVisited A map containing the visited node from the current search direction.
     * @param otherVisited A map containing the visited node from the opposite search direction.
     * @param addedCounter A reference to the counter for tracking the number of nodes added during this expansion.
     */
    Node* expand(std::queue<Node*>& currentQueue, std::unordered_map<Node*, Node*>& currentVisited, 
                const std::unordered_map<Node*, Node*>& otherVisited, int& addedCounter);

    // Queue used for the BiDirectionalBFS algorithm.
    std::queue<Node*> _startQueue;
    std::queue<Node*> _endQueue;
};


#endif
#ifndef _PATHFINDER_DIJKSTRA_HPP_
#define _PATHFINDER_DIJKSTRA_HPP_

#include <queue>

#include "pathfinding_algorithm.hpp"

/**
 * @class Dijkstra
 * @brief Implements the Dijkstra pathfinding algorithm.
 */
class Dijkstra : public PathfindingAlgorithm {
public:
    /**
     * @brief Constructs a Dijkstra pathfinding algorithm instance.
     * @param grid A shared pointer to the grid on which the algorithm operates.
     */
    Dijkstra(std::shared_ptr<Grid> grid);

    /**
     * @brief Finds the path from the start node to the end node.
     * @param start The starting node.
     * @param end The ending node.
     * @param speed The speed of the pathfinding process (default is 0.0f).
     */
    void findPath(Node* start, Node* end, float speed = 0.0f) override;

    /**
     * @brief Resets the algorithm to its initial state.
     */
    void reset() override;

    /**
     * @brief Checks if the search is complete.
     * @return True if the search is complete, false otherwise.
     */
    bool isSearchComplete() override;

private:
    /**
     * @struct CompareNode
     * @brief Comparator for the priority queue to compare nodes based on their G cost.
     */
    struct CompareNode {
        bool operator()(Node* lhs, Node* rhs) const {
            return lhs->getGCost() > rhs->getGCost();
        }
    };

    // Priority queue to store nodes to be explored, ordered by their G cost.
    std::priority_queue<Node*, std::vector<Node*>, CompareNode> _queue;
};


#endif
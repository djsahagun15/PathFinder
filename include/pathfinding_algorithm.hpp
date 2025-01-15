#ifndef _PATHFINDER_PATHFINDING_ALGORITHM_HPP_
#define _PATHFINDER_PATHFINDING_ALGORITHM_HPP_

#include "grid.hpp"

/**
 * @brief Calculates the Euclidean distance between two points.
 * 
 * @param a The first point.
 * @param b The second point.
 * @return The Euclidean distance between points a and b.
 */
float euclideanDistance(Vector2 a, Vector2 b);

/**
 * @brief Calculates the Manhattan distance between two points.
 * 
 * @param a The first point.
 * @param b The second point.
 * @return The Manhattan distance between points a and b.
 */
float manhattanDistance(Vector2 a, Vector2 b);

/**
 * @brief Abstract base class for pathfinding algorithms.
 */
class PathfindingAlgorithm {
public:
    virtual ~PathfindingAlgorithm() = default;

    /**
     * @brief Finds a path from the start node to the end node.
     * 
     * @param start The starting node.
     * @param end The ending node.
     * @param speed The speed of the pathfinding algorithm (optional).
     */
    virtual void findPath(Node* start, Node* end, float speed = 0.0f) = 0;

    /**
     * @brief Resets the pathfinding algorithm.
     */
    virtual void reset() = 0;

    /**
     * @brief Checks if the search is complete.
     * 
     * @return True if the search is complete, false otherwise.
     */
    virtual bool isSearchComplete() = 0;

protected:
    /**
     * @brief Constructs a PathfindingAlgorithm with a given grid.
     * 
     * @param grid The grid to be used by the pathfinding algorithm.
     */
    PathfindingAlgorithm(std::shared_ptr<Grid> grid);

    /**
     * @brief Gets the neighboring nodes of a given node.
     * 
     * @param node The node for which to find neighbors.
     * @return A vector of neighboring nodes.
     */
    std::vector<Node*> getNeighbors(Node* node) const;

    /**
     * @brief Traces the path from the start node to the end node.
     * 
     * @param start The starting node.
     * @param end The ending node.
     */
    void tracePath(Node* start, Node* end);

    // The grid used by the pathfinding algorithm.
    std::shared_ptr<Grid> _grid;

    // Flag indicating if it is the first iteration of the algorithm.
    bool _isFirstIter;
};


#endif
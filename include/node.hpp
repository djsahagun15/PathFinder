#ifndef _PATHFINDER_NODE_HPP_
#define _PATHFINDER_NODE_HPP_

#include <raylib.h>
#include <memory>

#include <array>

/**
 * @brief Represents the possible states of a node in the pathfinding grid
 */
enum State {
    NONE,
    START,  // Starting node
    END,    // End/target node
    PATH,   // Node is part of the found path
    EMPTY,  // Traversable node
    WALL    // Non-traversable obstacle
};

/**
 * @brief Represents the possible terrain types of a node in the pathfinding grid
 */
enum class TerrainType {
    AIR = 1,     // Default terrain type
    GRASS = 5,      // Grass terrain type
    SAND = 10,      // Sand terrain type
    STONE = 20,     // Forest terrain type
    MOUNTAIN = 50,  // Mountain terrain type
    WATER = 100,    // Water terrain type
};

constexpr std::array<TerrainType, 6> TERRAIN_TYPES = {
    TerrainType::AIR,
    TerrainType::GRASS,
    TerrainType::SAND,
    TerrainType::STONE,
    TerrainType::MOUNTAIN,
    TerrainType::WATER
};

/**
 * @brief Represents a single node in the pathfinding grid
 * 
 * This class implements functionality for A* pathfinding algorithm nodes,
 * including position, state, and cost calculations.
 */
class Node {
public:
    /**
     * @brief Constructs a node with given rectangle and grid coordinates
     * @param rect Rectangle defining node's position and size
     * @param x Grid x-coordinate
     * @param y Grid y-coordinate
     */
    Node(Rectangle rect, int x, int y);

    /**
     * @brief Updates the node's rectangle
     * @param rect New rectangle dimensions
     */
    void setRect(Rectangle rect);

    /**
     * @brief Calculates Euclidean distance to another node
     * @param other Target node to calculate distance to
     * @return Float distance between nodes
     */
    float getDistance(Node* other) const;

    /**
     * @brief Gets current state of the node
     * @return Current State enum value
     */
    State getState() const;

    /**
     * @brief Checks if node has been visited during pathfinding
     * @return True if visited, false otherwise
     */
    bool isVisited() const;

    /**
     * @brief Sets node state and visited flag
     * @param newState New state to set
     */
    void setState(State newState);

    /**
     * @brief Gets weight of the node based on terrain type
     * @return Float weight value
     */
    float getWeight() const;

    /**
     * @brief Sets terrain type of the node
     * @param terrain New terrain type
     */
    void setTerrain(TerrainType terrain);

    /**
     * @brief Gets terrain type of the node
     * @return TerrainType enum value
     */
    TerrainType getTerrain() const { return this->_terrain; }

    /**
     * @brief Sets visited flag for pathfinding
     * @param visited New visited flag value
     */
    void setVisited(bool visited);

    /**
     * @brief Gets node's x-coordinate in grid
     * @return X-coordinate
     */
    unsigned int getX() const;

    /**
     * @brief Gets node's y-coordinate in grid
     * @return Y-coordinate
     */
    unsigned int getY() const;

    /**
     * @brief Gets node's G cost (distance from start)
     * @return G cost value
     */
    float getGCost() const;

    /**
     * @brief Sets node's G cost
     * @param gCost New G cost value
     */
    void setGCost(float gCost);

    /**
     * @brief Gets node's H cost (heuristic distance to end)
     * @return H cost value
     */
    float getHCost() const;

    /**
     * @brief Sets node's H cost directly
     * @param hCost New H cost value
     */
    void setHCost(float hCost);

    /**
     * @brief Calculates and sets H cost based on end node
     * @param endNode Target end node
     */
    void setHCost(Node* endNode);

    /**
     * @brief Gets node's F cost (G cost + H cost)
     * @return F cost value
     */
    float getFCost() const;

    /**
     * @brief Gets node's parent in the path
     * @return Pointer to parent node
     */
    Node* getParent() const;

    /**
     * @brief Sets node's parent
     * @param newParent Pointer to new parent node
     */
    void setParent(Node* newParent);

    /**
     * @brief Draws the node using raylib
     */
    void draw() const;

private:
    // Center point of node
    Vector2 _center;
    
    // Rectangle defining node boundaries
    Rectangle _rect;
    
    // Grid coordinates
    int _x, _y;


    // Current node state
    State _state;

    // Terrain type of the node
    TerrainType _terrain;

    // Visited flag for pathfinding
    bool _isVisited;
    

    // Cost from start node to this node
    float _gCost;

    // Heuristic cost from this node to end node
    float _hCost;

    // Total cost (G cost + H cost)
    float _fCost;


    // Parent node in the path
    Node* _parent;

    // Color of the node for drawing
    std::unique_ptr<Color> _color;
};


#endif
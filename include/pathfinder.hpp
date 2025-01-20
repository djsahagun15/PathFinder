#ifndef _PATHFINDER_HPP_
#define _PATHFINDER_HPP_

#include "grid.hpp"
#include "pathfinding_algorithm.hpp"
#include "control_panel.hpp"

#include <functional>
#include <vector>

/**
 * @class PathFinder
 * @brief Manages the pathfinding process, including grid management and algorithm selection.
 */
class PathFinder {
public:
    /**
     * @brief Constructs a PathFinder object with the specified number of columns and rows.
     * @param cols Number of columns in the grid.
     * @param rows Number of rows in the grid.
     */
    PathFinder(unsigned int cols, unsigned int rows);

    /**
     * @brief Destructor for the PathFinder object.
     */
    ~PathFinder();

    /**
     * @brief Starts the pathfinding solver with the specified algorithm.
     * @param algorithm Index of the algorithm to use.
     */
    void startSolver(int algorithm);

    /**
     * @brief Toggles the solver between paused and running states.
     */
    void toggleSolver();

    /**
     * @brief Resizes the grid to the specified number of columns and rows.
     * @param cols New number of columns.
     * @param rows New number of rows.
     */
    void resize(unsigned int cols, unsigned int rows);

    /**
     * @brief Resets the grid and solver state.
     */
    void reset();

    /**
     * @brief Clears the current path from the grid.
     */
    void clearPath();

    /**
     * @brief Checks if the solver is currently searching for a path.
     * @return True if searching, false otherwise.
     */
    bool isSearching() const;

    /**
     * @brief Checks if the solver is currently paused.
     * @return True if paused, false otherwise.
     */
    bool isSearchPaused() const;

    /**
     * @brief Gets the number of columns in the grid.
     * @return Number of columns.
     */
    unsigned int getCols() const;

    /**
     * @brief Gets the number of rows in the grid.
     * @return Number of rows.
     */
    unsigned int getRows() const;

    void moveGridRect();

    /**
     * @brief Runs the pathfinding process.
     */
    void run();

private:
    /**
     * @brief Updates the state of the pathfinding process.
     */
    void update();

    /**
     * @brief Draws the current state of the grid and pathfinding process.
     */
    void draw() const;

    // Pointer to the grid object
    std::shared_ptr<Grid> _grid;

    // List of available pathfinding algorithms
    std::vector<std::shared_ptr<PathfindingAlgorithm>> _algorithms;

    // Currently selected pathfinding algorithm
    std::shared_ptr<PathfindingAlgorithm> _selectedAlgorithm;

    // Flag indicating if the solver is paused
    bool _isPaused;
    
    // Flag indicating if the solver is currently searching for a path
    bool _isSearching;
    
    // Flag indicating if the path has been solved at least once
    bool _isSolvedOnce;

    // Pointer to the control panel object
    std::unique_ptr<ControlPanel> _panel;
};


#endif
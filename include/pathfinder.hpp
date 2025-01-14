#ifndef _PATHFINDER_HPP_
#define _PATHFINDER_HPP_

#include "grid.hpp"
#include "pathfinding_algorithm.hpp"
#include "control_panel.hpp"

#include <functional>
#include <vector>


class PathFinder {
public:
    PathFinder(unsigned int cols, unsigned int rows);
    ~PathFinder();

    void startSolver(int algorithm);
    void toggleSolver();

    void resize(unsigned int cols, unsigned int rows);

    void reset();
    void clearPath();

    bool isSearching() const;
    bool isSearchPaused() const;

    unsigned int getCols() const;
    unsigned int getRows() const;

    void run();

private:
    void update();
    void draw() const;

    std::shared_ptr<Grid> _grid;

    std::vector<std::shared_ptr<PathfindingAlgorithm>> _algorithms;

    std::shared_ptr<PathfindingAlgorithm> _selectedAlgorithm;

    bool _isPaused;
    bool _isSearching;
    bool _isSolvedOnce;

    std::unique_ptr<ControlPanel> _panel;
};


#endif
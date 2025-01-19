#include "pathfinder.hpp"
#include "camera.hpp"
#include "bfs.hpp"
#include "dijkstra.hpp"
#include "astar.hpp"
#include "gbs.hpp"

#include "control_panel.hpp"


// Initialize the camera controller
CameraController cameraController;

const Color BACKGROUND = (Color){ 52, 73, 94, 255 };


// Constructor for PathFinder class
PathFinder::PathFinder(unsigned int cols, unsigned int rows) {
    InitWindow(1280, 720, "PathFinder"); // Initialize the window
    SetTargetFPS(60); // Set the target FPS

    this->_grid = std::make_shared<Grid>(cols, rows); // Create the grid

    // Add pathfinding algorithms to the list
    this->_algorithms.emplace_back(std::make_shared<BFS>(this->_grid));
    this->_algorithms.emplace_back(std::make_shared<Dijkstra>(this->_grid));
    this->_algorithms.emplace_back(std::make_shared<AStar>(this->_grid));
    this->_algorithms.emplace_back(std::make_shared<GBS>(this->_grid));

    // Initialize state variables
    this->_isSearching = false;
    this->_isSolvedOnce = false;
    this->_isPaused = false;

    // Create the control panel
    this->_panel = std::make_unique<ControlPanel>(this);
}


// Destructor for PathFinder class
PathFinder::~PathFinder() {
    CloseWindow(); // Close the window
}


// Resize the grid and reset the pathfinder
void PathFinder::resize(unsigned int cols, unsigned int rows) {
    this->_grid->resize(cols, rows);
    this->reset();
}


// Start the pathfinding solver with the selected algorithm
void PathFinder::startSolver(int algorithm) {
    if (this->_isSearching) return; // If already searching, do nothing

    this->clearPath(); // Clear the current path

    this->_selectedAlgorithm = this->_algorithms[algorithm]; // Select the algorithm
    this->_isSearching = true; // Set searching state to true
    this->_isPaused = false; // Unpause the search

    this->_isSolvedOnce = false; // Reset solved state
}


// Toggle the solver's paused state
void PathFinder::toggleSolver() { this->_isPaused ^= true; }


// Check if the solver is currently searching
bool PathFinder::isSearching() const { return this->_isSearching; }


// Check if the solver is currently paused
bool PathFinder::isSearchPaused() const { return this->_isPaused; }


// Get the number of columns in the grid
unsigned int PathFinder::getCols() const { return this->_grid->getColCount(); }


// Get the number of rows in the grid
unsigned int PathFinder::getRows() const { return this->_grid->getRowCount(); }


// Main run loop for the pathfinder
void PathFinder::run() {
    static bool shouldUpdateCamera = false;

    #if defined(PLATFORM_WEB)
        this->update();

        // Check if the mouse is within the control panel rectangle
        // And update only if the mouse is not in the control panel
        bool mouseRight = IsMouseButtonDown(MOUSE_BUTTON_RIGHT);
        float wheelMove = GetMouseWheelMove();

        if ((!shouldUpdateCamera && mouseRight || wheelMove != 0)) shouldUpdateCamera = !this->_panel->isMouseInRect();
        else if (!mouseRight && wheelMove == 0) shouldUpdateCamera = false;

        if (shouldUpdateCamera) cameraController.update(this->_grid.get());

        BeginDrawing();
            ClearBackground(BACKGROUND);
            this->draw();
        EndDrawing();
    #else
        while (!WindowShouldClose()) {
            this->update();

            // Check if the mouse is within the control panel rectangle
            // And update only if the mouse is not in the control panel
            bool mouseRight = IsMouseButtonDown(MOUSE_BUTTON_RIGHT);
            float wheelMove = GetMouseWheelMove();

            if ((!shouldUpdateCamera && mouseRight || wheelMove != 0)) shouldUpdateCamera = !this->_panel->isMouseInRect();
            else if (!mouseRight && wheelMove == 0) shouldUpdateCamera = false;

            if (shouldUpdateCamera) cameraController.update(this->_grid.get());
            
            BeginDrawing();
                ClearBackground(BACKGROUND);
                this->draw();
            EndDrawing();
        }
    #endif
}


// Reset the grid and the selected algorithm
void PathFinder::reset() {
    this->_grid->reset();
    if (this->_selectedAlgorithm) {
        this->_selectedAlgorithm->reset();
    }
    this->_isSearching = false;
    this->_isSolvedOnce = false;
    this->_isPaused = false;
}


// Clear the current path and reset the selected algorithm
void PathFinder::clearPath() {
    this->_grid->clearPath();
    if (this->_selectedAlgorithm) {
        this->_selectedAlgorithm->reset();
    }
    this->_isSearching = false;
    this->_isSolvedOnce = false;
    this->_isPaused = false;
}


// Update the pathfinder state
void PathFinder::update() {
    this->_grid->_selectedNodeType = static_cast<TerrainType>(this->_panel->getSelectedNodeType());

    if (IsKeyPressed(KEY_R)) this->reset();
    else if (IsKeyPressed(KEY_C)) this->clearPath();

    // Retrace the path if the grid is already solved and is updated
    if (this->_isSolvedOnce && this->_grid->_shouldUpdatePath) {
        this->clearPath();
        this->_selectedAlgorithm->findPath(this->_grid->_startNode, this->_grid->_endNode);
        this->_isSolvedOnce = true;
    }

    // Only update the grid if an algorithm is not currently running
    if (!this->_isSearching && !this->_isPaused) this->_grid->update();

    // Visualize the pathfinding algorithm
    else if (!this->_isPaused) {
        this->_selectedAlgorithm->findPath(this->_grid->_startNode, this->_grid->_endNode, this->_panel->getAnimSpeed());

        if (this->_selectedAlgorithm->isSearchComplete()) {
            this->_isSearching = false;
            this->_isSolvedOnce = true;
            this->_isPaused = false;
        }
    }
}


// Draw the grid and the control panel
void PathFinder::draw() const {
    this->_grid->draw();
    this->_panel->draw();
}
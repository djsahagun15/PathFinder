#include "pathfinder.hpp"
#include "camera.hpp"
#include "bfs.hpp"
#include "dijkstra.hpp"
#include "astar.hpp"

#include "control_panel.hpp"


CameraController cameraController;


PathFinder::PathFinder(unsigned int cols, unsigned int rows) {
    InitWindow(1280, 720, "PathFinder");
    SetTargetFPS(60);

    this->_grid = std::make_shared<Grid>(cols, rows);

    this->_algorithms.emplace_back(std::make_shared<BFS>(this->_grid));
    this->_algorithms.emplace_back(std::make_shared<Dijkstra>(this->_grid));
    this->_algorithms.emplace_back(std::make_shared<AStar>(this->_grid));

    this->_isSearching = false;
    this->_isSolvedOnce = false;
    this->_isPaused = false;

    this->_panel = std::make_unique<ControlPanel>(this);
}


PathFinder::~PathFinder() {
    CloseWindow();
}


void PathFinder::resize(unsigned int cols, unsigned int rows) {
    this->_grid->resize(cols, rows);
    this->reset();
}


void PathFinder::startSolver(int algorithm) {
    if (this->_isSearching) return;

    this->clearPath();

    this->_selectedAlgorithm = this->_algorithms[algorithm];
    this->_isSearching = true;
    this->_isPaused = false;

    this->_isSolvedOnce = false;
}


void PathFinder::toggleSolver() { this->_isPaused ^= true; }


bool PathFinder::isSearching() const { return this->_isSearching; }


bool PathFinder::isSearchPaused() const { return this->_isPaused; }


unsigned int PathFinder::getCols() const { return this->_grid->getColCount(); }


unsigned int PathFinder::getRows() const { return this->_grid->getRowCount(); }


void PathFinder::run() {
    #if defined(PLATFORM_WEB)
        this->update();

        cameraController.update(this->_grid.get());

        BeginDrawing();
            ClearBackground(LIGHTGRAY);
            this->draw();
        EndDrawing();
    #else
        while (!WindowShouldClose()) {
            this->update();

            // static bool shouldUpdateCamera = false;
            // if ((!shouldUpdateCamera && IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) || GetMouseWheelMove() != 0) {
            //     shouldUpdateCamera = !this->_panel->isMouseInRect();
            // }
            // else if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT)) shouldUpdateCamera = false;

            // if (shouldUpdateCamera) 
            cameraController.update(this->_grid.get());
            
            BeginDrawing();
                ClearBackground(LIGHTGRAY);
                this->draw();
            EndDrawing();
        }
    #endif
}


void PathFinder::reset() {
    this->_grid->reset();
    if (this->_selectedAlgorithm) {
        this->_selectedAlgorithm->reset();
    }
    this->_isSearching = false;
    this->_isSolvedOnce = false;
    this->_isPaused = false;
}


void PathFinder::clearPath() {
    this->_grid->clearPath();
    if (this->_selectedAlgorithm) {
        this->_selectedAlgorithm->reset();
    }
    this->_isSearching = false;
    this->_isPaused = false;
}


void PathFinder::update() {
    if (IsKeyPressed(KEY_R)) this->reset();
    else if (IsKeyPressed(KEY_C)) this->clearPath();

    if (this->_isSolvedOnce && this->_grid->_shouldUpdatePath) {
        this->clearPath();
        this->_selectedAlgorithm->findPath(this->_grid->_startNode, this->_grid->_endNode);
    }

    if (!this->_isSearching && !this->_isPaused) this->_grid->update();
    else if (!this->_isPaused) {
        this->_selectedAlgorithm->findPath(this->_grid->_startNode, this->_grid->_endNode, this->_panel->getAnimSpeed());

        if (this->_selectedAlgorithm->isSearchComplete()) {
            this->_isSearching = false;
            this->_isSolvedOnce = true;
            this->_isPaused = false;
        }
    }
}


void PathFinder::draw() const {
    this->_grid->draw();
    this->_panel->draw();
}
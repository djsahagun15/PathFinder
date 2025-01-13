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

    this->_isCurrentlySearching = false;

    this->_panel = std::make_unique<ControlPanel>(this);
}


PathFinder::~PathFinder() {
    CloseWindow();
}


void PathFinder::startSolver(int algorithm) {
    if (this->_isCurrentlySearching) return;

    this->clearPath();

    this->_selectedAlgorithm = this->_algorithms[algorithm];
    this->_isCurrentlySearching = true;

    this->_isSolvedOnce = false;
}


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
    if (this->_selectedAlgorithm && this->_isCurrentlySearching) {
        this->_selectedAlgorithm->reset();
    }
    this->_selectedAlgorithm = nullptr;
    this->_isCurrentlySearching = false;
}


void PathFinder::clearPath() {
    this->_grid->clearPath();
    this->_isCurrentlySearching = false;
}


void PathFinder::update() {
    if (IsKeyPressed(KEY_R)) {
        this->reset();
        
        this->_isSolvedOnce = false;
    } else if (IsKeyPressed(KEY_C)) {
        this->clearPath();
        
        this->_isSolvedOnce = false;
    }

    if (this->_isSolvedOnce && this->_grid->_shouldUpdatePath) {
        this->clearPath();
        this->_selectedAlgorithm->findPath(this->_grid->_startNode, this->_grid->_endNode);
    }

    if (!this->_isCurrentlySearching) this->_grid->update();
    else {
        this->_selectedAlgorithm->findPath(this->_grid->_startNode, this->_grid->_endNode, this->_panel->getAnimSpeed());

        if (this->_selectedAlgorithm->isSearchComplete()) {
            this->_isCurrentlySearching = false;

            this->_isSolvedOnce = true;
        }
    }
}


void PathFinder::draw() const {
    this->_grid->draw();
    this->_panel->draw();
}
#include "pathfinder.hpp"
#include "camera.hpp"
#include "bfs.hpp"
#include "dijkstra.hpp"
#include "astar.hpp"


CameraController cameraController;


PathFinder::PathFinder(unsigned int cols, unsigned int rows) {
    InitWindow(700, 700, "PathFinder");
    SetTargetFPS(60);

    this->_grid = std::make_shared<Grid>(cols, rows);

    this->_BFS = std::make_shared<BFS>(this->_grid);
    this->_Dijkstra = std::make_shared<Dijkstra>(this->_grid);
    this->_AStar = std::make_shared<AStar>(this->_grid);

    this->_isCurrentlySearching = false;
}


PathFinder::~PathFinder() {
    CloseWindow();
}


void PathFinder::run() {
    #if defined(PLATFORM_WEB)
        this->update();

        cameraController.update();

        BeginDrawing();
            ClearBackground(LIGHTGRAY);
            this->draw();
        EndDrawing();
    #else
        while (!WindowShouldClose()) {
            this->update();

            cameraController.update();
            
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
    static bool isSolvedOnce = false;

    if (IsKeyPressed(KEY_R)) {
        this->reset();
        
        isSolvedOnce = false;
    } else if (IsKeyPressed(KEY_C)) {
        this->clearPath();
        
        isSolvedOnce = false;
    }

    if (isSolvedOnce && this->_grid->_shouldUpdatePath) {
        this->clearPath();
        this->_selectedAlgorithm->findPath(this->_grid->_startNode, this->_grid->_endNode);
    }

    if (!this->_isCurrentlySearching) {
        this->_grid->update();

        if (IsKeyPressed(KEY_ONE)) {
            this->clearPath();
            
            this->_selectedAlgorithm = this->_BFS;
            this->_isCurrentlySearching = true;

            isSolvedOnce = false;
        } else if (IsKeyPressed(KEY_TWO)) {
            this->clearPath();

            this->_selectedAlgorithm = this->_Dijkstra;
            this->_isCurrentlySearching = true;

            isSolvedOnce = false;
        } else if (IsKeyPressed(KEY_THREE)) {
            this->clearPath();

            this->_selectedAlgorithm = this->_AStar;
            this->_isCurrentlySearching = true;

            isSolvedOnce = false;
        }
    } else {
        this->_selectedAlgorithm->findPath(this->_grid->_startNode, this->_grid->_endNode, 1.0f);

        if (this->_selectedAlgorithm->isSearchComplete()) {
            this->_isCurrentlySearching = false;

            isSolvedOnce = true;
        }
    }
}


void PathFinder::draw() const {
    this->_grid->draw();
}
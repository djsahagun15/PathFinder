#include "pathfinder.hpp"
#include "camera.hpp"
#include "bfs.hpp"


CameraController cameraController;


PathFinder::PathFinder(unsigned int cols, unsigned int rows) {
    InitWindow(700, 700, "PathFinder");
    SetTargetFPS(60);

    this->_grid = std::make_shared<Grid>(cols, rows);

    this->_BFS = std::make_unique<BFS>(this->_grid);
    // this->_Dijkstra = std::make_unique<Dijkstra>(this->_grid);
    // this->_AStar = std::make_unique<AStar>(this->_grid);
}


PathFinder::~PathFinder() {
    CloseWindow();
}


void PathFinder::run() {
    while (!WindowShouldClose()) {
        this->update();

        cameraController.update();
        
        BeginDrawing();
            ClearBackground(LIGHTGRAY);
            this->draw();
        EndDrawing();
    }
}


void PathFinder::reset() {
    this->_grid->reset();
}


void PathFinder::clearPath() {
    this->_grid->clearPath();
}


void PathFinder::update() {
    static bool isSolvedOnce = false;

    this->_grid->update();

    if (IsKeyPressed(KEY_R)) {
        this->reset();
        isSolvedOnce = false;
    } else if (IsKeyPressed(KEY_C)) {
        this->clearPath();
        isSolvedOnce = false;
    }

    if (isSolvedOnce && this->_grid->_shouldUpdatePath) {
        this->clearPath();
        this->_BFS->findPath(this->_grid->_startNode, this->_grid->_endNode);
    }
    
    if (IsKeyPressed(KEY_SPACE)) {
        this->clearPath();

        this->_BFS->findPath(this->_grid->_startNode, this->_grid->_endNode);

        isSolvedOnce = true;
    }
}


void PathFinder::draw() const {
    this->_grid->draw();
}
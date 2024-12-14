#include "pathfinder.hpp"
#include "camera.hpp"
#include "bfs.hpp"


CameraController cameraController;


PathFinder::PathFinder(unsigned int cols, unsigned int rows) {
    InitWindow(700, 700, "PathFinder");
    SetTargetFPS(60);

    this->_grid = std::make_shared<Grid>(cols, rows);
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


void PathFinder::update() {
    this->_grid->update();

    if (IsKeyPressed(KEY_SPACE)) {
        std::shared_ptr<PathfindingAlgorithm> algorithm = std::make_shared<BFS>(this->_grid);
        algorithm->findPath(this->_grid->_startNode, this->_grid->_endNode);
    }
}


void PathFinder::draw() const {
    this->_grid->draw();
}
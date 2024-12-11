#include "pathfinder.hpp"
#include "camera.hpp"


CameraController cameraController;


PathFinder::PathFinder(unsigned int cols, unsigned int rows) {
    InitWindow(0, 0, "PathFinder");
    SetTargetFPS(60);

    this->_grid = std::make_unique<Grid>(cols, rows);
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
}


void PathFinder::draw() const {
    this->_grid->draw();
}
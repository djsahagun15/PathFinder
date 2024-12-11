#include <raylib.h>

#include "pathfinder.hpp"


PathFinder::PathFinder(unsigned int cols, unsigned int rows) : _grid(std::make_unique<Grid>(cols, rows)) {
    InitWindow(0, 0, "PathFinder");
    ToggleFullscreen();
    SetTargetFPS(60);
}


PathFinder::~PathFinder() {
    CloseWindow();
}


void PathFinder::run() {
    while (!WindowShouldClose()) {
        this->update();
        BeginDrawing();
            ClearBackground(WHITE);
            this->draw();
        EndDrawing();
    }
}


void PathFinder::update() {}


void PathFinder::draw() const {
    this->_grid->draw();
}
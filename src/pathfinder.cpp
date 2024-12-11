#include "pathfinder.hpp"


PathFinder::PathFinder(unsigned int cols, unsigned int rows) : _grid(std::make_unique<Grid>(cols, rows)) {
    InitWindow(700, 700, "PathFinder");
    SetTargetFPS(60);
}


PathFinder::~PathFinder() {
    CloseWindow();
}


void PathFinder::run() {
    while (!WindowShouldClose()) {
        this->update();
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
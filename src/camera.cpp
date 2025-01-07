#include <cmath>
#include <algorithm>
#include <iostream>

#include "camera.hpp"
#include "grid.hpp"


float lerp(float a, float b, float t) {
    return (1 - t) * a + t * b;
}


Vector2 lerp(Vector2 a, Vector2 b, float t) {
    return (Vector2){
        lerp(a.x, b.x, t),
        lerp(a.y, b.y, t)
    };
}


CameraController::CameraController() {
    this->offset = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
    this->target = this->offset;
    this->rotation = 0.0f;
    this->zoom = 1.0f;
}


Vector2 CameraController::getMouseWorldPos() const {
    return GetScreenToWorld2D(GetMousePosition(), *this);
}


Camera2D CameraController::get() const {
    return *this;
}


void CameraController::update(const Grid* grid) {
    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
        Vector2 delta = GetMouseDelta();
        delta.x /= -this->zoom;
        delta.y /= -this->zoom;

        this->target.x += delta.x;
        this->target.y += delta.y;
    }

    float wheel = GetMouseWheelMove() * 0.1f * this->zoom;
    if (wheel != 0) {
        Vector2 mouseWorldPos = this->getMouseWorldPos();

        this->offset = GetMousePosition();
        this->target = mouseWorldPos;

        this->zoom += wheel;

        const float scaleFactor = 0.1f;
        const float maxZoom = std::min(
            GetScreenWidth() / (grid->getWidth() / grid->getColCount()) * scaleFactor, 
            GetScreenHeight() / (grid->getHeight() / grid->getRowCount()) * scaleFactor
        );
        this->zoom = std::clamp(this->zoom, 1.0f, maxZoom);
        
        if (this->zoom == 1.0f) {
            this->offset = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
            this->target = this->offset;
        }
    }
}
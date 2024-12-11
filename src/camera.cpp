#include <cmath>

#include "camera.hpp"


CameraController::CameraController() {
    this->offset = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
    this->target = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
    this->rotation = 0.0f;
    this->zoom = 1.0f;
}


Vector2 CameraController::getMouseWorldPos() const {
    return GetScreenToWorld2D(GetMousePosition(), *this);
}


Camera2D CameraController::get() const {
    return *this;
}


void CameraController::update() {
    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
        Vector2 delta = GetMouseDelta();
        delta.x *= -1.0f / this->zoom;
        delta.y *= -1.0f / this->zoom;

        this->target.x += delta.x;
        this->target.y += delta.y;
    }

    float wheel = GetMouseWheelMove() * 0.1f;
    if (wheel != 0) {
        Vector2 mouseWorldPos = this->getMouseWorldPos();

        this->offset = GetMousePosition();
        this->target = mouseWorldPos;

        this->zoom += wheel;
        if (this->zoom < 0.8f) this->zoom = 0.8f;
    }
}
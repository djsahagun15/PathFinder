#include <cmath>
#include <algorithm>

#include "camera.hpp"
#include "grid.hpp"

// Constructor for CameraController
CameraController::CameraController() {
    this->offset = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
    this->target = this->offset;
    this->rotation = 0.0f;
    this->zoom = 1.0f;
}

// Get the mouse position in the world
Vector2 CameraController::getMouseWorldPos() const {
    return GetScreenToWorld2D(GetMousePosition(), *this);
}

// Get the current camera state
Camera2D CameraController::get() const {
    return *this;
}

// Update the camera state based on user input and grid constraints
void CameraController::update(const Grid* grid) {
    // Pan the camera with right mouse button
    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
        Vector2 delta = GetMouseDelta();
        delta.x /= -this->zoom;
        delta.y /= -this->zoom;

        this->target.x += delta.x;
        this->target.y += delta.y;
    }

    // Zoom the camera with mouse wheel
    float wheel = GetMouseWheelMove() * 0.1f * this->zoom;
    if (wheel != 0) {
        Vector2 mouseWorldPos = this->getMouseWorldPos();

        this->offset = GetMousePosition();
        this->target = mouseWorldPos;

        this->zoom += wheel;

        // Calculate the maximum zoom level based on grid size
        const float scaleFactor = 0.1f;
        const float maxZoom = std::min(
            GetScreenWidth() / (grid->getWidth() / grid->getColCount()) * scaleFactor, 
            GetScreenHeight() / (grid->getHeight() / grid->getRowCount()) * scaleFactor
        );
        this->zoom = std::clamp(this->zoom, 1.0f, maxZoom);
        
        // Reset the camera if zoomed out completely
        if (this->zoom == 1.0f) {
            this->offset = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
            this->target = this->offset;
        }
    }
}
#ifndef _PATHFINDER_CAMERA_HPP_
#define _PATHFINDER_CAMERA_HPP_

#include <raylib.h>

class Grid;

/**
 * @class CameraController
 * @brief A controller for managing a 2D camera in the PathFinder application.
 */
class CameraController : Camera2D {
public:
    /**
     * @brief Constructs a new CameraController object.
     */
    CameraController();

    /**
     * @brief Gets the mouse position in the world coordinates.
     * @return The mouse position as a Vector2 in world coordinates.
     */
    Vector2 getMouseWorldPos() const;

    /**
     * @brief Gets the current camera settings.
     * @return The current Camera2D settings.
     */
    Camera2D get() const;

    /**
     * @brief Updates the camera based on the provided grid.
     * @param grid A pointer to the Grid object used to update the camera.
     */
    void update(const Grid* grid);
};


#endif
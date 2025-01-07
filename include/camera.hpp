#ifndef _PATHFINDER_CAMERA_HPP_
#define _PATHFINDER_CAMERA_HPP_

#include <raylib.h>

class Grid;

class CameraController : Camera2D {
public:
    CameraController();

    Vector2 getMouseWorldPos() const;
    Camera2D get() const;

    void update(const Grid* grid);
};


#endif
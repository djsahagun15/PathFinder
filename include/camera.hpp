#ifndef __PATHFINDER_CAMERA_HPP__
#define __PATHFINDER_CAMERA_HPP__

#include <raylib.h>


class CameraController : Camera2D {
public:
    CameraController();

    Vector2 getMouseWorldPos() const;
    Camera2D get() const;

    void update();
};


#endif
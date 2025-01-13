#ifndef _PATHFINDER_CONTROL_PANEL_HPP_
#define _PATHFINDER_CONTROL_PANEL_HPP_


#include <raylib.h>
#include <memory>


class PathFinder;

class ControlPanel {
public:
    ControlPanel(PathFinder* pf);

    float getAnimSpeed() const;

    bool isMouseInRect() const;

    void draw() const;

private:
    Rectangle _rect;

    static float _animationSpeed;

    PathFinder* _pf;
};


#endif
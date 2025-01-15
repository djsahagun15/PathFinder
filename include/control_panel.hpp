#ifndef _PATHFINDER_CONTROL_PANEL_HPP_
#define _PATHFINDER_CONTROL_PANEL_HPP_


#include <raylib.h>
#include <memory>


class PathFinder;

/**
 * @class ControlPanel
 * @brief Manages the control panel interface for the PathFinder application.
 */
class ControlPanel {
public:
    /**
     * @brief Constructs a ControlPanel object.
     * @param pf Pointer to the PathFinder instance.
     */
    ControlPanel(PathFinder* pf);

    /**
     * @brief Gets the current animation speed.
     * @return The animation speed as a float.
     */
    float getAnimSpeed() const;

    /**
     * @brief Checks if the mouse is within the control panel rectangle.
     * @return True if the mouse is within the rectangle, false otherwise.
     */
    bool isMouseInRect() const;

    /**
     * @brief Draws the control panel on the screen.
     */
    void draw() const;

private:
    // The rectangle representing the control panel area.
    Rectangle _rect;

    // The speed of the animation.
    static float _animationSpeed;

    // Pointer to the PathFinder instance.
    PathFinder* _pf;
};


#endif
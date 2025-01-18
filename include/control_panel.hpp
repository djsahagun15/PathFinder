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
     * @brief Gets the currently selected node type.
     * @return The selected node type as an integer. Possible values are: 
     * 0 : WALL,
     * 1 : AIR,
     * 5 : GRASS,
     * 10 : SAND,
     * 20 : STONE,
     * 50 : MOUNTAIN,
     * 100 : WATER
     */
    int getSelectedNodeType() const;

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

    static int _selectedNodeType;

    // Pointer to the PathFinder instance.
    PathFinder* _pf;
};


#endif
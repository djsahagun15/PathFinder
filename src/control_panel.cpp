#include "control_panel.hpp"
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

#include <string>
#include <sstream>
#include <iomanip>

#include "pathfinder.hpp"


float ControlPanel::_animationSpeed = 0.0f;


ControlPanel::ControlPanel(PathFinder* pf) : _pf(pf) {
    this->_rect = {
        static_cast<float>(GetScreenWidth() - 395.0f), 5.0f,
        390.0f, 180.0f
    };
}


float ControlPanel::getAnimSpeed() const {
    if (ControlPanel::_animationSpeed == 0.0f) return 0.0f;

    return 1.1f - ControlPanel::_animationSpeed;
}


bool ControlPanel::isMouseInRect() const {
    Vector2 mouse = GetMousePosition();
    return mouse.x > this->_rect.x && mouse.x < this->_rect.x + this->_rect.width &&
           mouse.y > this->_rect.y && mouse.y < this->_rect.y + this->_rect.height;
}


void ControlPanel::draw() const {
    GuiLoadStyleDefault();

    GuiPanel(this->_rect, "#140#PathFinder Controller");

    static int selectedAlgo = 0;
    static bool algoSelectionEditMode = false;

    if (algoSelectionEditMode) GuiLock();
    else GuiUnlock();

    GuiDrawText("Pathfinding Algorithm", (Rectangle){ this->_rect.x + 10.0f, this->_rect.y + 30.0f, 380.0f, 30.0f }, TEXT_ALIGN_CENTER, BLACK);

    if (GuiButton((Rectangle){ this->_rect.x + 300.0f, this->_rect.y + 60.0f, 70.0f, 25.0f }, "Solve")) {
        this->_pf->startSolver(selectedAlgo);
    }

    static bool isChecked = false;
    GuiCheckBox((Rectangle){ this->_rect.x + 25.0f, this->_rect.y + 110.0f, 15.0f, 15.0f }, "Animation Speed", &isChecked);


    static float speedSliderMinValue = 0.0f;
    static float speedSliderMaxValue = 1.0f;

    static float speedSliderPrevValue = ControlPanel::_animationSpeed;

    if (isChecked) {
        GuiSetState(STATE_NORMAL);
        ControlPanel::_animationSpeed = speedSliderPrevValue;
    } else {
        GuiSetState(STATE_DISABLED);
        ControlPanel::_animationSpeed = speedSliderMinValue;
    }

    static std::string speedValueText;
    int valueChanged = GuiSlider(
        (Rectangle){ this->_rect.x + 20.0f, this->_rect.y + 130.0f, 280.0f, 25.0f }, 
        nullptr, 
        (ControlPanel::_animationSpeed > 0) ? speedValueText.c_str() : "No animation", 
        &ControlPanel::_animationSpeed, 
        speedSliderMinValue, 
        speedSliderMaxValue
    );

    ControlPanel::_animationSpeed = std::round(ControlPanel::_animationSpeed * 10.0f) / 10.0f;

    if (valueChanged) {
        speedSliderPrevValue = ControlPanel::_animationSpeed;

        speedValueText = std::to_string(static_cast<int>((1.1f - ControlPanel::_animationSpeed) * 100)) + "\% speed";
    }


    GuiSetState(STATE_NORMAL);
    if (GuiDropdownBox((Rectangle){ this->_rect.x + 20.0f, this->_rect.y + 60.0f, 275.0f, 25.0f }, 
        "Breadth-First Search;Dijkstra's Algorithm; A* Algorithm", &selectedAlgo, algoSelectionEditMode)) algoSelectionEditMode = !algoSelectionEditMode;
}
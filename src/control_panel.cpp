#include "control_panel.hpp"
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

#include <string>
#include <sstream>
#include <iomanip>

#include "pathfinder.hpp"


float ControlPanel::_animationSpeed = 0.0f;


ControlPanel::ControlPanel(PathFinder* pf) : _pf(pf) {
    // Initialize the control panel rectangle
    this->_rect = {
        static_cast<float>(GetScreenWidth() - 395.0f), 5.0f,
        390.0f, 320.0f
    };
}


float ControlPanel::getAnimSpeed() const {
    // Return the animation speed, adjusted if necessary
    if (ControlPanel::_animationSpeed == 0.0f) return 0.0f;

    return 1.1f - ControlPanel::_animationSpeed;
}


bool ControlPanel::isMouseInRect() const {
    // Check if the mouse is within the control panel rectangle
    Vector2 mouse = GetMousePosition();
    return mouse.x > this->_rect.x && mouse.x < this->_rect.x + this->_rect.width &&
           mouse.y > this->_rect.y && mouse.y < this->_rect.y + this->_rect.height;
}


void ControlPanel::draw() const {
    // Load the default GUI style
    GuiLoadStyleDefault();

    // Draw the control panel
    GuiPanel(this->_rect, "#140#PathFinder Controller");

    static int selectedAlgo = 0;
    static bool algoSelectionEditMode = false;

    // Lock or unlock the GUI based on edit mode
    if (algoSelectionEditMode) GuiLock();
    else GuiUnlock();

    // Draw the pathfinding algorithm label
    GuiDrawText("Pathfinding Algorithm", (Rectangle){ this->_rect.x + 10.0f, this->_rect.y + 30.0f, 380.0f, 30.0f }, TEXT_ALIGN_CENTER, BLACK);

    // Check if the pathfinder is searching or paused
    bool isSearching = this->_pf->isSearching();
    bool isPaused = this->_pf->isSearchPaused();

    // Draw the solve/resume/pause button based on the state
    if (!isSearching && !isPaused) {
        if (GuiButton((Rectangle){ this->_rect.x + 300.0f, this->_rect.y + 60.0f, 70.0f, 25.0f }, "#131#Solve")) {
            this->_pf->startSolver(selectedAlgo);
        }
    } else {
        if (GuiButton((Rectangle){ this->_rect.x + 300.0f, this->_rect.y + 60.0f, 70.0f, 25.0f }, isPaused ? "#131#Resume" : "#132#Pause")) {
            this->_pf->toggleSolver();
        }
    }

    static bool isChecked = false;
    // Draw the animation speed checkbox
    GuiCheckBox((Rectangle){ this->_rect.x + 25.0f, this->_rect.y + 110.0f, 15.0f, 15.0f }, "Animation Speed", &isChecked);


    static float speedSliderMinValue = 0.0f;
    static float speedSliderMaxValue = 1.0f;

    static float speedSliderPrevValue = ControlPanel::_animationSpeed;

    // Enable or disable the speed slider based on the checkbox
    if (isChecked) {
        GuiSetState(STATE_NORMAL);
        ControlPanel::_animationSpeed = speedSliderPrevValue;
    } else {
        GuiSetState(STATE_DISABLED);
        ControlPanel::_animationSpeed = speedSliderMinValue;
    }

    static std::string speedValueText;
    // Draw the speed slider
    int valueChanged = GuiSlider(
        (Rectangle){ this->_rect.x + 20.0f, this->_rect.y + 130.0f, 280.0f, 25.0f }, 
        nullptr, 
        (ControlPanel::_animationSpeed > 0) ? speedValueText.c_str() : "No animation", 
        &ControlPanel::_animationSpeed, 
        speedSliderMinValue, 
        speedSliderMaxValue
    );

    // Round the animation speed to one decimal place
    ControlPanel::_animationSpeed = std::round(ControlPanel::_animationSpeed * 10.0f) / 10.0f;

    // Update the speed value text if the slider value changed
    if (valueChanged) {
        speedSliderPrevValue = ControlPanel::_animationSpeed;

        speedValueText = std::to_string(static_cast<int>((1.1f - ControlPanel::_animationSpeed) * 100)) + "\% speed";
    }

    // Reset the GUI state to normal
    GuiSetState(STATE_NORMAL);

    // Draw the clear path and reset buttons
    if (GuiButton((Rectangle){ this->_rect.x + 30.0f, this->_rect.y + 180.0f, 160.0f, 30.0f }, "#113#Clear Path")) this->_pf->clearPath();
    if (GuiButton((Rectangle){ this->_rect.x + 200.0f, this->_rect.y + 180.0f, 160.0f, 30.0f }, "#211#Reset")) this->_pf->reset();


    static int cols = static_cast<int>(this->_pf->getCols());
    static int rows = static_cast<int>(this->_pf->getRows());

    static int currentCols = cols;
    static int currentRows = rows;

    static bool gridResizeEditMode1 = false;
    static bool gridResizeEditMode2 = false;
    
    // Draw the grid size label
    GuiDrawText("Grid Size", (Rectangle){ this->_rect.x + 10.0f, this->_rect.y + 240.0f, 370.0f, 30.0f }, TEXT_ALIGN_CENTER, BLACK);

    // Draw the columns value box and handle resizing
    if (GuiValueBox((Rectangle){ this->_rect.x + 106.0f, this->_rect.y + 270.0f, 80.0f, 30.0f }, nullptr, &cols, 10, 100, gridResizeEditMode1)) {
        gridResizeEditMode1 = !gridResizeEditMode1;
        if (cols != currentCols) {
            this->_pf->resize(cols, rows);
            currentCols = cols;
        }
    }

    // Draw the rows value box and handle resizing
    if (GuiValueBox((Rectangle){ this->_rect.x + 202.0f, this->_rect.y + 270.0f, 80.0f, 30.0f }, "X ", &rows, 10, 100, gridResizeEditMode2)) {
        gridResizeEditMode2 = !gridResizeEditMode2;
        if (rows != currentRows) {
            this->_pf->resize(cols, rows);
            currentRows = rows;
        }
    }

    // Draw the algorithm selection dropdown box
    if (GuiDropdownBox((Rectangle){ this->_rect.x + 20.0f, this->_rect.y + 60.0f, 275.0f, 25.0f }, 
        "Breadth-First Search;Dijkstra's Algorithm; A* Algorithm", &selectedAlgo, algoSelectionEditMode)) algoSelectionEditMode = !algoSelectionEditMode;
}

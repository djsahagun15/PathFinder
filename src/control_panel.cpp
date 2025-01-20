#include "control_panel.hpp"
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

#include <string>
#include <sstream>
#include <iomanip>
#include <format>

#include "pathfinder.hpp"


float ControlPanel::_animationSpeed = 0.0f;

int ControlPanel::_selectedNodeType = 0;


extern int selectedDistanceFormula;

extern bool isDiagonalMovementAllowed;


ControlPanel::ControlPanel(PathFinder* pf) : _pf(pf) {
    // Initialize the control panel rectangle
    this->_rect = {
        static_cast<float>(GetScreenWidth() - 445.0f), 5.0f,
        440.0f, 480.0f
    };
}


int ControlPanel::getSelectedNodeType() const {
    if (ControlPanel::_selectedNodeType == 0) return 0;
    return static_cast<int>(TERRAIN_TYPES[ControlPanel::_selectedNodeType - 1]);
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
    GuiSetStyle(DEFAULT, TEXT_SIZE, 14);

    // Draw the control panel
    GuiPanel(this->_rect, "#140#PathFinder Controller");

    static int selectedAlgo = 0;
    static bool algoSelectionEditMode = false;

    static bool nodeTypeSelectionEditMode = false;

    static bool distanceFormulaEditMode = false;

    // Lock or unlock the GUI based on edit mode
    if (algoSelectionEditMode || nodeTypeSelectionEditMode || distanceFormulaEditMode) GuiLock();
    else GuiUnlock();

    // Draw the pathfinding algorithm label
    GuiDrawText("Pathfinding Algorithm", (Rectangle){ this->_rect.x + 10.0f, this->_rect.y + 30.0f, this->_rect.width - 20.0f, 30.0f }, TEXT_ALIGN_CENTER, BLACK);

    // Check if the pathfinder is searching or paused
    bool isSearching = this->_pf->isSearching();
    bool isPaused = this->_pf->isSearchPaused();

    // Draw the solve/resume/pause button based on the state
    if (!isSearching && !isPaused) {
        if (GuiButton((Rectangle){ this->_rect.x + 345.0f, this->_rect.y + 60.0f, 75.0f, 30.0f }, "#131#Solve")) {
            this->_pf->startSolver(selectedAlgo);
        }
    } else {
        if (GuiButton((Rectangle){ this->_rect.x + 345.0f, this->_rect.y + 60.0f, 75.0f, 30.0f }, isPaused ? "#131#Resume" : "#132#Pause")) {
            this->_pf->toggleSolver();
        }
    }

    GuiCheckBox((Rectangle){ this->_rect.x + 25.0f, this->_rect.y + 170.0f, 15.0f, 15.0f }, "Allow Diagonal Movement", &isDiagonalMovementAllowed);

    static bool isChecked = false;
    // Draw the animation speed checkbox
    GuiCheckBox((Rectangle){ this->_rect.x + 25.0f, this->_rect.y + 200.0f, 15.0f, 15.0f }, "Animation Speed", &isChecked);


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
        (Rectangle){ this->_rect.x + 20.0f, this->_rect.y + 230.0f, 280.0f, 25.0f }, 
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

    // Draw the grid properties label
    GuiDrawText("Grid Properties", (Rectangle){ this->_rect.x + 10.0f, this->_rect.y + 275.0f, this->_rect.width - 20.0f, 30.0f }, TEXT_ALIGN_CENTER, BLACK);
    
    static int cols = static_cast<int>(this->_pf->getCols());
    static int rows = static_cast<int>(this->_pf->getRows());

    static int currentCols = cols;
    static int currentRows = rows;

    static bool gridResizeEditMode1 = false;
    static bool gridResizeEditMode2 = false;

    // Draw the columns value box and handle resizing
    if (GuiValueBox((Rectangle){ this->_rect.x + 135.0f, this->_rect.y + 370.0f, 80.0f, 30.0f }, "Columns: ", &cols, 10, 100, gridResizeEditMode1)) {
        gridResizeEditMode1 = !gridResizeEditMode1;
        if (cols != currentCols) {
            this->_pf->resize(cols, rows);
            currentCols = cols;
        }
    }

    // Draw the rows value box and handle resizing
    if (GuiValueBox((Rectangle){ this->_rect.x + 285.0f, this->_rect.y + 370.0f, 80.0f, 30.0f }, "Rows: ", &rows, 10, 100, gridResizeEditMode2)) {
        gridResizeEditMode2 = !gridResizeEditMode2;
        if (rows != currentRows) {
            this->_pf->resize(cols, rows);
            currentRows = rows;
        }
    }
    
    // Draw the clear path and reset buttons
    if (GuiButton((Rectangle){ this->_rect.x + 65.0f, this->_rect.y + 430.0f, 150.0f, 30.0f }, "#113#Clear Path")) this->_pf->clearPath();
    if (GuiButton((Rectangle){ this->_rect.x + 235.0f, this->_rect.y + 430.0f, 150.0f, 30.0f }, "#211#Reset")) this->_pf->reset();

    std::string nodeTypeText = std::format(
        "WALL (INFINITY);AIR ({});GRASS ({});SAND ({});STONE ({});MOUNTAIN ({});WATER ({})", 
        static_cast<int>(TerrainType::AIR), 
        static_cast<int>(TerrainType::GRASS), 
        static_cast<int>(TerrainType::SAND), 
        static_cast<int>(TerrainType::STONE), 
        static_cast<int>(TerrainType::MOUNTAIN), 
        static_cast<int>(TerrainType::WATER)
    );

    // Draw the node type selection dropdown box
    GuiLabel((Rectangle){ this->_rect.x + 55.0f, this->_rect.y + 315.0f, 100.0f, 30.0f }, "Node Type:");
    if (GuiDropdownBox((Rectangle){ this->_rect.x + 145.0f, this->_rect.y + 315.0f, 250.0f, 30.0f }, 
        nodeTypeText.c_str(), &_selectedNodeType, nodeTypeSelectionEditMode)) nodeTypeSelectionEditMode = !nodeTypeSelectionEditMode;
    
    if (this->_pf->isSearching()) GuiLock();
    GuiLabel((Rectangle){ this->_rect.x + 30.0f, this->_rect.y + 115.0f, 150.0f, 30.0f }, "Distance Formula:");
    if (GuiDropdownBox((Rectangle){ this->_rect.x + 155.0f, this->_rect.y + 115.0f, 250.0f, 30.0f }, 
        "Manhattan Distance;Euclidean Distance;Chebyshev Distance", &selectedDistanceFormula, distanceFormulaEditMode)) distanceFormulaEditMode = !distanceFormulaEditMode;
    GuiUnlock();

    // Draw the algorithm selection dropdown box
    if (GuiDropdownBox((Rectangle){ this->_rect.x + 20.0f, this->_rect.y + 60.0f, 320.0f, 30.0f }, 
        "Breadth-First Search;Dijkstra's Algorithm; A* Algorithm;Greedy Best-First Search;Bidirectional Breadth-First Search", &selectedAlgo, algoSelectionEditMode)) algoSelectionEditMode = !algoSelectionEditMode;
}

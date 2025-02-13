#include <algorithm>
#include <limits>
#include <cmath>

#include "grid.hpp"
#include "camera.hpp"

// Linear interpolation between two vectors
Vector2 lerp(Vector2 a, Vector2 b, float t) {
    return Vector2 {
        std::lerp(a.x, b.x, t),
        std::lerp(a.y, b.y, t)
    };
}

// External camera controller
extern CameraController cameraController;

// Constructor for Grid class
Grid::Grid(unsigned int cols, unsigned int rows) : _cols(0), _rows(0), _shouldUpdatePath(false) {
    this->resize(cols, rows);
    
    this->_startNode = this->_matrix[0][0].get();
    this->_startNode->setState(State::START);

    this->_endNode = this->_matrix[cols - 1][rows - 1].get();
    this->_endNode->setState(State::END);
}

// Resize the grid
void Grid::resize(unsigned int cols, unsigned int rows) {
    if (cols == this->_cols && rows == this->_rows) return;

    const int WINW = GetScreenWidth() - 450, WINH = GetScreenHeight();
    
    this->_nodeSize = std::min(static_cast<float>(WINW / cols - 1), 
                               static_cast<float>(WINH / rows - 1));
    
    Vector2 offset {
        (WINW - cols * this->_nodeSize) / 2.0f,
        (WINH - rows * this->_nodeSize) / 2.0f
    };
    
    this->_rect = {
        offset.x + 1.0f,
        offset.y + 1.0f,
        cols * this->_nodeSize + 1.0f,
        rows * this->_nodeSize + 1.0f
    };

    // Resize the matrix and update node rectangles
    if (cols > this->_matrix.size() || rows > this->_matrix[0].size()) {
        this->_matrix.resize(cols);
        for (int col = 0; col < cols; col++) {
            this->_matrix[col].resize(rows);
            for (int row = 0; row < rows; row++) {
                Rectangle nRect {
                    offset.x + col * this->_nodeSize + 1.0f,
                    offset.y + row * this->_nodeSize + 1.0f,
                    this->_nodeSize + 1.0f,
                    this->_nodeSize + 1.0f
                };

                if (col >= this->_cols || row >= this->_rows) this->_matrix[col][row] = std::make_unique<Node>(nRect, col, row);
                else this->_matrix[col][row]->setRect(nRect);
            }
        }
    } else {
        for (int col = 0; col < cols; col++) {
            for (int row = 0; row < rows; row++) {
                Rectangle nRect {
                    offset.x + col * this->_nodeSize + 1.0f,
                    offset.y + row * this->_nodeSize + 1.0f,
                    this->_nodeSize + 1.0f,
                    this->_nodeSize + 1.0f
                };

                this->_matrix[col][row]->setRect(nRect);
            }
        }
    }

    this->_cols = cols;
    this->_rows = rows;
}

// Check if mouse is within the grid rectangle
bool Grid::isMouseInRect(Vector2 mouse) const {
    return mouse.x > this->_rect.x && mouse.x < this->_rect.x + this->_rect.width &&
           mouse.y > this->_rect.y && mouse.y < this->_rect.y + this->_rect.height;
}

// Get the node at the mouse position
Node* Grid::getNode(Vector2 mouse) const {
    mouse.x -= this->_rect.x;
    mouse.y -= this->_rect.y;
    
    unsigned int x = mouse.x / this->_nodeSize;
    unsigned int y = mouse.y / this->_nodeSize;

    x = std::clamp(x, 0U, this->_cols - 1);
    y = std::clamp(y, 0U, this->_rows - 1);
    
    return this->_matrix[x][y].get();
}

void Grid::setNodeType(int type) { this->_selectedNodeType = static_cast<TerrainType>(type); }

// Get grid width
float Grid::getWidth() const { return this->_rect.width; };

// Get grid height
float Grid::getHeight() const { return this->_rect.height; };

// Get number of columns
unsigned int Grid::getColCount() const { return this->_cols; };

// Get number of rows
unsigned int Grid::getRowCount() const { return this->_rows; };

// Get total number of nodes
unsigned int Grid::getColRowCount() const { return this->_cols * this->_rows; };

// Get neighboring nodes
bool isDiagonalMovementAllowed = false;
std::vector<Node*> Grid::getNeighbors(Node* node) const {
    std::vector<Node*> neighbors;
    
    unsigned int x = node->getX();
    unsigned int y = node->getY();

    if (x > 0) neighbors.push_back(this->_matrix[x - 1][y].get());
    if (x < this->_cols - 1) neighbors.push_back(this->_matrix[x + 1][y].get());
    if (y > 0) neighbors.push_back(this->_matrix[x][y - 1].get());
    if (y < this->_rows - 1) neighbors.push_back(this->_matrix[x][y + 1].get());

    if (isDiagonalMovementAllowed) {
        if ((x > 0 && y > 0) && (this->_matrix[x - 1][y]->getState() != State::WALL && this->_matrix[x][y - 1]->getState() != State::WALL))
            neighbors.push_back(this->_matrix[x - 1][y - 1].get());

        if ((x < this->_cols - 1 && y > 0) && (this->_matrix[x + 1][y]->getState() != State::WALL && this->_matrix[x][y - 1]->getState() != State::WALL))
            neighbors.push_back(this->_matrix[x + 1][y - 1].get());

        if ((x > 0 && y < this->_rows - 1) && (this->_matrix[x - 1][y]->getState() != State::WALL && this->_matrix[x][y + 1]->getState() != State::WALL))
            neighbors.push_back(this->_matrix[x - 1][y + 1].get());

        if ((x < this->_cols - 1 && y < this->_rows - 1) && (this->_matrix[x + 1][y]->getState() != State::WALL && this->_matrix[x][y + 1]->getState() != State::WALL))
            neighbors.push_back(this->_matrix[x + 1][y + 1].get());
    }

    return neighbors;
}

// Check if path should be updated
bool Grid::shouldUpdatePath() const { return this->_shouldUpdatePath; }

// Reset the flag for updating path
void Grid::resetShouldUpdatePathFlag() { this->_shouldUpdatePath = false; }

// Clear the path
void Grid::clearPath() {
    float MAX = std::numeric_limits<float>::max();
    
    for (const auto& col : this->_matrix) {
        for (const auto& node : col) {
            State nodeState = node->getState();

            if (nodeState == State::PATH) nodeState = State::EMPTY;

            node->setState(nodeState);
            node->setVisited(false);
            node->setParent(nullptr);
            node->setGCost(MAX);
            node->setHCost(0.0);
        }
    }

    this->_shouldUpdatePath = false;
}

// Reset the grid
void Grid::reset() {
    float MAX = std::numeric_limits<float>::max();
    
    for (const auto& col : this->_matrix) {
        for (const auto& node : col) {
            node->setState(State::EMPTY);
            node->setTerrain(TerrainType::AIR);
            node->setVisited(false);
            node->setParent(nullptr);
            node->setGCost(MAX);
            node->setHCost(0.0);
        }
    }

    this->_startNode = this->_matrix[0][0].get();
    this->_startNode->setState(State::START);

    this->_endNode = this->_matrix[this->_cols - 1][this->_rows - 1].get();
    this->_endNode->setState(State::END);

    this->_shouldUpdatePath = false;
}

bool isControlPanelVisible = true;
void Grid::moveRect() {
    int WINW = GetScreenWidth(), WINH = GetScreenHeight();
    if (isControlPanelVisible) WINW -= 450;
    
    this->_nodeSize = std::min(static_cast<float>(WINW / this->_cols - 1), 
                               static_cast<float>(WINH / this->_rows - 1));
    
    Vector2 offset {
        (WINW - this->_cols * this->_nodeSize) / 2.0f,
        (WINH - this->_rows * this->_nodeSize) / 2.0f
    };
    
    this->_rect = {
        offset.x + 1.0f,
        offset.y + 1.0f,
        this->_cols * this->_nodeSize + 1.0f,
        this->_rows * this->_nodeSize + 1.0f
    };

    for (int x = 0; x < this->_cols; x++) {
        for (int y = 0; y < this->_rows; y++) {
            Rectangle nRect {
                offset.x + x * this->_nodeSize + 1.0f,
                offset.y + y * this->_nodeSize + 1.0f,
                this->_nodeSize + 1.0f,
                this->_nodeSize + 1.0f
            };
            
            this->_matrix[x][y]->setRect(nRect);
        }
    }
}


// Update the grid based on mouse input
void Grid::update() {
    static State selectedState = State::NONE;
    static Node* prevSelectedNode = nullptr;
    
    Vector2 mouse = cameraController.getMouseWorldPos();
    static Vector2 prevMouse = mouse;
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && isMouseInRect(mouse)) {
        Node* selectedNode = this->getNode(mouse);

        if (selectedNode == prevSelectedNode) return;
        
        if (selectedState == State::NONE) selectedState = selectedNode->getState();

        if (selectedState == State::START) {
            if (selectedNode != this->_endNode) {
                this->_startNode->setState(State::EMPTY);
                selectedNode->setState(State::START);

                this->_startNode = selectedNode;
            }
        }
        else if (selectedState == State::END) {
            if (selectedNode != this->_startNode) {
                this->_endNode->setState(State::EMPTY);
                selectedNode->setState(State::END);

                this->_endNode = selectedNode;
            }
        }
        else if (selectedNode != this->_startNode && selectedNode != this->_endNode) {
            Vector2 d = { mouse.x - prevMouse.x, mouse.y - prevMouse.y };
            float dist = std::sqrt(d.x * d.x + d.y * d.y);

            unsigned int maxIter = static_cast<unsigned int>(dist / this->_nodeSize) + 1;
            for (int i = 0; i < maxIter; i++) {
                Vector2 interpolatedPoint = lerp(mouse, prevMouse, static_cast<float>(i) / maxIter);

                interpolatedPoint.x = std::clamp(interpolatedPoint.x, this->_rect.x, this->_rect.x + this->_rect.width);
                interpolatedPoint.y = std::clamp(interpolatedPoint.y, this->_rect.y, this->_rect.y + this->_rect.height);

                Node* interpolatedNode = this->getNode(interpolatedPoint);
                State interpolatedState = interpolatedNode->getState();

                if (interpolatedState == State::START || interpolatedState == State::END) continue;

                interpolatedNode->setTerrain(this->_selectedNodeType);
            }
        }

        this->_shouldUpdatePath = true;
        
        prevSelectedNode = selectedNode;
    } else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
        selectedState = State::NONE;
        prevSelectedNode = nullptr;
    }

    prevMouse = mouse;
}

// Draw the grid
void Grid::draw() const {
    BeginMode2D(cameraController.get());
        for (int col = 0; col < this->_cols; col++) {
            for (int row = 0; row < this->_rows; row++) {
                this->_matrix[col][row]->draw();
            }
        }
    EndMode2D();
}
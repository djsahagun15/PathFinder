#include <algorithm>
#include <limits>

#include "grid.hpp"
#include "camera.hpp"


extern CameraController cameraController;


Grid::Grid(unsigned int cols, unsigned int rows) : _cols(cols), _rows(rows), _shouldUpdatePath(false) {
    const int WINW = GetScreenWidth() - 400, WINH = GetScreenHeight();
    
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
            this->_matrix[col][row] = std::make_unique<Node>(nRect, col, row);
        }
    }
    
    this->_startNode = this->_matrix[0][0].get();
    this->_startNode->setState(State::START);

    this->_endNode = this->_matrix[cols - 1][rows - 1].get();
    this->_endNode->setState(State::END);
}


bool Grid::isMouseInRect(Vector2 mouse) const {
    return mouse.x > this->_rect.x && mouse.x < this->_rect.x + this->_rect.width &&
           mouse.y > this->_rect.y && mouse.y < this->_rect.y + this->_rect.height;
}


Node* Grid::getNode(Vector2 mouse) const {
    mouse.x -= this->_rect.x;
    mouse.y -= this->_rect.y;
    
    unsigned int x = mouse.x / this->_nodeSize;
    unsigned int y = mouse.y / this->_nodeSize;

    x = std::clamp(x, 0U, this->_cols - 1);
    y = std::clamp(y, 0U, this->_rows - 1);
    
    return this->_matrix[x][y].get();
}


float Grid::getWidth() const { return this->_rect.width; };
float Grid::getHeight() const { return this->_rect.height; };

unsigned int Grid::getColCount() const { return this->_cols; };
unsigned int Grid::getRowCount() const { return this->_rows; };
unsigned int Grid::getColRowCount() const { return this->_cols * this->_rows; };


std::vector<Node*> Grid::getNeighbors(Node* node) const {
    std::vector<Node*> neighbors;
    
    unsigned int x = node->getX();
    unsigned int y = node->getY();

    if (x > 0) neighbors.push_back(this->_matrix[x - 1][y].get());
    if (x < this->_cols - 1) neighbors.push_back(this->_matrix[x + 1][y].get());
    if (y > 0) neighbors.push_back(this->_matrix[x][y - 1].get());
    if (y < this->_rows - 1) neighbors.push_back(this->_matrix[x][y + 1].get());

    return neighbors;
}


bool Grid::shouldUpdatePath() const { return this->_shouldUpdatePath; }


void Grid::resetShouldUpdatePathFlag() { this->_shouldUpdatePath = false; }


void Grid::clearPath() {
    float MAX = std::numeric_limits<float>::max();
    
    for (const auto& col : this->_matrix) {
        for (const auto& node : col) {
            State nodeState = node->getState();

            if (nodeState == State::PATH) nodeState = State::EMPTY;

            node->setState(nodeState);
            node->setParent(nullptr);
            node->setGCost(MAX);
            node->setHCost(0.0);
        }
    }

    this->_shouldUpdatePath = false;
}


void Grid::reset() {
    float MAX = std::numeric_limits<float>::max();
    
    for (const auto& col : this->_matrix) {
        for (const auto& node : col) {
            node->setState(State::EMPTY);
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


void Grid::update() {
    static State selectedState = State::NONE;
    static Node* prevSelectedNode = nullptr;
    
    Vector2 mouse = cameraController.getMouseWorldPos();
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
            selectedNode->setState((State)(State::EMPTY + State::WALL - selectedState), selectedNode->isVisited());
        }

        this->_shouldUpdatePath = true;
        
        prevSelectedNode = selectedNode;
    } else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
        selectedState = State::NONE;
        prevSelectedNode = nullptr;
    }
}


void Grid::draw() const {
    BeginMode2D(cameraController.get());
        for (const auto& col : this->_matrix) {
            for (const auto& node : col) node->draw();
        }
    EndMode2D();
}
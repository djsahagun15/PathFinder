#include <algorithm>
#include <limits>

#include "grid.hpp"
#include "camera.hpp"


extern CameraController cameraController;


Grid::Grid(unsigned int cols, unsigned int rows) : _cols(cols), _rows(rows), _shouldUpdatePath(false) {
    Vector2 offset {
        (GetScreenWidth() - cols * NODE_SIZE) / 2.0f,
        (GetScreenHeight() - rows * NODE_SIZE) / 2.0f
    };
    
    this->_rect = {
        offset.x + 1.0f,
        offset.y + 1.0f,
        cols * NODE_SIZE + 1.0f,
        rows * NODE_SIZE + 1.0f
    };
    
    this->_matrix.resize(rows);
    for (int row = 0; row < rows; row++) {
        this->_matrix[row].resize(cols);
        for (int col = 0; col < cols; col++) {
            Rectangle nRect {
                offset.x + col * NODE_SIZE + 1.0f,
                offset.y + row * NODE_SIZE + 1.0f,
                NODE_SIZE + 1.0f, 
                NODE_SIZE + 1.0f
            };
            this->_matrix[row][col] = std::make_unique<Node>(nRect, col, row);
        }
    }
    
    this->_startNode = this->_matrix[0][0].get();
    this->_startNode->setState(State::START);

    this->_endNode = this->_matrix[rows - 1][cols - 1].get();
    this->_endNode->setState(State::END);
}


bool Grid::isMouseInRect(Vector2 mouse) const {
    return mouse.x > this->_rect.x && mouse.x < this->_rect.x + this->_rect.width &&
           mouse.y > this->_rect.y && mouse.y < this->_rect.y + this->_rect.height;
}


Node* Grid::getNode(Vector2 mouse) const {
    Vector2 offset {
        (GetScreenWidth() - this->_cols * NODE_SIZE) / 2.0f + 1,
        (GetScreenHeight() - this->_rows * NODE_SIZE) / 2.0f + 1
    };
    mouse.x -= offset.x;
    mouse.y -= offset.y;
    
    unsigned int x = mouse.x / NODE_SIZE;
    unsigned int y = mouse.y / NODE_SIZE;

    x = std::max(std::min(x, this->_cols - 1), 0U);
    y = std::max(std::min(y, this->_rows - 1), 0U);
    
    return this->_matrix[y][x].get();
}


float Grid::getWidth() const { return this->_rect.width; };
float Grid::getHeight() const { return this->_rect.height; };

unsigned int Grid::getCols() const { return this->_cols; };
unsigned int Grid::getRows() const { return this->_rows; };


std::vector<Node*> Grid::getNeighbors(Node* node) const {
    std::vector<Node*> neighbors;
    
    unsigned int x = node->getColIndex();
    unsigned int y = node->getRowIndex();

    if (x > 0) neighbors.push_back(this->_matrix[y][x - 1].get());
    if (x < this->_cols - 1) neighbors.push_back(this->_matrix[y][x + 1].get());
    if (y > 0) neighbors.push_back(this->_matrix[y - 1][x].get());
    if (y < this->_rows - 1) neighbors.push_back(this->_matrix[y + 1][x].get());

    return neighbors;
}


bool Grid::shouldUpdatePath() const { return this->_shouldUpdatePath; }


void Grid::resetShouldUpdatePathFlag() { this->_shouldUpdatePath = false; }


void Grid::clearPath() {
    float MAX = std::numeric_limits<float>::max();
    
    for (const auto& row : this->_matrix) {
        for (const auto& node : row) {
            State nodeState = node->getState();

            if (nodeState == State::PATH) nodeState = State::EMPTY;

            node->setState(nodeState);
            node->setParent(nullptr);
            node->setGCost(MAX);
            node->setHCost(MAX);
        }
    }

    this->_shouldUpdatePath = false;
}


void Grid::reset() {
    float MAX = std::numeric_limits<float>::max();
    
    for (const auto& row : this->_matrix) {
        for (const auto& node : row) {
            node->setState(State::EMPTY);
            node->setParent(nullptr);
            node->setGCost(MAX);
            node->setHCost(MAX);
        }
    }

    this->_startNode = this->_matrix[0][0].get();
    this->_startNode->setState(State::START);

    this->_endNode = this->_matrix[this->_rows - 1][this->_cols - 1].get();
    this->_endNode->setState(State::END);

    this->_shouldUpdatePath = false;
}


void Grid::update() {
    static State selectedState = State::NONE;
    static Node* prevSelectedNode = nullptr;
    
    Vector2 mouse = cameraController.getMouseWorldPos();
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && this->isMouseInRect(mouse)) {
        Node* selectedNode = this->getNode(mouse);
        
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
            selectedNode->setState((State)(State::EMPTY + State::WALL - selectedState));
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
        for (auto& row : this->_matrix) {
            for (auto& node : row) node->draw();
        }
    EndMode2D();
}
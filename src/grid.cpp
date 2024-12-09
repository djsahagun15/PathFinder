#include <algorithm>
#include <iostream>

#include "grid.hpp"
#include "camera.hpp"


extern CameraController cameraController;


Grid::Grid(unsigned int cols, unsigned int rows) : _cols(cols), _rows(rows) {
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
    this->_startNode->changeState(State::START);

    this->_endNode = this->_matrix[rows - 1][cols - 1].get();
    this->_endNode->changeState(State::END);
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
    
    unsigned int x = mouse.x / 20;
    unsigned int y = mouse.y / 20;

    x = std::max(std::min(x, this->_cols - 1), 0U);
    y = std::max(std::min(y, this->_rows - 1), 0U);
    
    return this->_matrix[y][x].get();
}


float Grid::getWidth() const { return this->_rect.width; };
float Grid::getHeight() const { return this->_rect.height; };

unsigned int Grid::getCols() const { return this->_cols; };
unsigned int Grid::getRows() const { return this->_rows; };


void Grid::update() {
    static State nodeNewState = State::NONE;
    static Node* prevSelectedNode = nullptr;
    
    Vector2 mouse = cameraController.getMouseWorldPos();
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && isMouseInRect(mouse)) {
        Node* selectedNode = this->getNode(mouse);
        
        if (nodeNewState == State::NONE) nodeNewState = selectedNode->getState();

        if (nodeNewState == State::START) {
            if (prevSelectedNode && prevSelectedNode != selectedNode) {
                prevSelectedNode->changeState(State::EMPTY);
                selectedNode->changeState(State::START);
            }
        }
        else if (nodeNewState == State::END) {
            if (prevSelectedNode && prevSelectedNode != selectedNode) {
                prevSelectedNode->changeState(State::EMPTY);
                selectedNode->changeState(State::END);
            }
        }
        else {
            selectedNode->changeState((State)(State::EMPTY + State::WALL - nodeNewState));
        }
        

        prevSelectedNode = selectedNode;
    } else {
        nodeNewState = State::NONE;
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
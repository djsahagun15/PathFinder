#include <algorithm>

#include "grid.hpp"


Grid::Grid(unsigned int cols, unsigned int rows) : _cols(cols), _rows(rows) {
    this->_matrix.resize(rows);
    for (int row = 0; row < rows; row++) {
        this->_matrix[row].resize(cols);
        for (int col = 0; col < cols; col++) {
            this->_matrix[row][col] = std::make_unique<Node>(col, row);
        }
    }

    this->_rect = {
        1, 1, 
        this->_matrix[0].size() * NODE_SIZE + 1, 
        this->_matrix.size() * NODE_SIZE + 1
    };
}


bool Grid::isMouseInRect(Vector2 mouse) const {
    return mouse.x > this->_rect.x && mouse.x < this->_rect.x + this->_rect.width &&
           mouse.y > this->_rect.y && mouse.y < this->_rect.y + this->_rect.height;
}


Node* Grid::getNode(Vector2 mouse) const {
    unsigned int x = mouse.x / 20;
    unsigned int y = mouse.y / 20;

    x = std::max(std::min(x, this->_cols), 0U);
    y = std::max(std::min(y, this->_rows), 0U);
    
    return this->_matrix[y][x].get();
}


void Grid::update() {
    Vector2 mouse = GetMousePosition();
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && isMouseInRect(mouse)) {
        Node* selectedNode = this->getNode(mouse);
        selectedNode->changeState(WALL);
    }
}


void Grid::draw() const {
    for (auto& row : this->_matrix) {
        for (auto& node : row) node->draw();
    }
}
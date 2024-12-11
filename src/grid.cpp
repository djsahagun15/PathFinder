#include <raylib.h>

#include "grid.hpp"


Grid::Grid(unsigned int cols, unsigned int rows) : _cols(cols), _rows(rows) {
    this->_matrix.resize(rows);
    for (int row = 0; row < rows; row++) {
        this->_matrix[row].resize(cols);
        for (int col = 0; col < cols; col++) {
            this->_matrix[row][col] = std::make_unique<Node>(col, row);
        }
    }
}


void Grid::draw() const {
    for (auto& row : this->_matrix) {
        for (auto& node : row) node->draw();
    }
}
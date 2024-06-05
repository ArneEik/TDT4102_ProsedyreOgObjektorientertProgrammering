#include "matrix.h"
#include <iostream>
#include <cassert>

Matrix::Matrix(int nRows, int nCols) : rows{nRows}, cols{nCols}{
    assert(cols>=1);
    assert(rows>=1);
    matrix = new double*[rows];
    for (int row = 0; row<rows; row++){
        matrix[row] = new double[cols];
        for(int col = 0; col<cols; col++){
            matrix[row][col] = 0.0;
        }
    }
}
Matrix::Matrix(int nRows) : Matrix(nRows, nRows) {
    for (int i = 0; i < rows; i++){
        matrix[i][i] = 1.0;
    }
}
Matrix::Matrix(const Matrix & rhs) : Matrix(rhs.getRows(),rhs.getCols()) {
    for(int row = 0; row<rows; row++){
        for(int col = 0; col<cols; col++){
            matrix[row][col] = rhs.get(rows,col);
        }
    }
}
Matrix & Matrix::operator=(Matrix rhs)
{
    std::swap(this->rows, rhs.rows);
    std::swap(this->cols, rhs.cols);
    std::swap(this->matrix, rhs.matrix);
    return *this;
}
Matrix::~Matrix(){
    for(int row = 0; row<rows; row++){
        delete[] matrix[row];
        matrix[row] = nullptr;
    }
    delete[] matrix;
    matrix = nullptr;

    rows = 0;
    cols = 0;
}
double Matrix::get(int row, int col) const{   
    assert(row>=0 && row<rows);
    assert(col>=0 && col<cols); 
    return matrix[row][col];
}
void Matrix::set(int row, int col, double value){
    assert(row>=0 && row<rows);
    assert(col>=0 && col<cols); 
    matrix[row][col] = value; 
}
double* Matrix::operator[](int row){
    assert(row>=0 && row<rows);
    return matrix[row];
}
std::ostream & operator<<(std::ostream &os, const Matrix &matrix)
{
    for(int row = 0; row < matrix.getRows(); row++){
        os<<"|\t";
        for(int col = 0; col< matrix.getCols(); col++){
            os << matrix.get(row,col) <<"\t";
        }
        os<<"|\n";
    }os<<"|\n";
    return os;
}
Matrix& Matrix::operator+=(Matrix & rhs){
    assert(this->getRows() == rhs.getRows() && this->getColumns() == rhs.getColumns());
    for (int row = 0; row<this->rows; row++){
        for (int col = 0; col<this->cols; col++){
            this->matrix[row][col] = this->matrix[row][col] + rhs.matrix[row][col];
        }
    }
    return *this;
}
Matrix Matrix::operator+(Matrix & rhs){
    assert(this->cols == rhs.cols && this->rows == rhs.cols);
    return Matrix{*this} += rhs;
}
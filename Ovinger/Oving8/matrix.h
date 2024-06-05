#pragma once
#include <iostream>
#include <utility>

class Matrix {
private:
    int rows;
    int cols;
    double** matrix;

public:
    Matrix(int rows, int cols);
    explicit Matrix(int nRows);
    ~Matrix();
    Matrix(const Matrix& rhs);

    double get(int row, int col) const;
    void set(int row, int col, double value);
    double* operator[](int row); 

    int getRows() const{return rows;}
    int getCols() const{return cols;}
    friend std::ostream &operator<<(std::ostream &os, const Matrix &matrix);
    Matrix& operator=(Matrix rhs);
    Matrix& operator+=(Matrix & rhs);
    Matrix operator+(Matrix & rhs);


};
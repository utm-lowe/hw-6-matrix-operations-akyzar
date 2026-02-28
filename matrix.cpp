/**
 * @file matrix.cpp
 * @author Aaron Kyzar
 * @brief 
 * @version 1.0
 * @date 2026-02-??
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#include "matrix.h"

using namespace std;

Matrix::Matrix(unsigned int rows, unsigned int cols)
{
    this->m = rows; this->n = cols;
    this->ar = new double*[m];
    for (int i = 0; i < this->m; i++)
        this->ar[i] = new double[n];
    
}

Matrix::Matrix(const Matrix &rhs)
{
    *this = rhs;
}

Matrix::~Matrix()
{
    for (int i = 0; i < this->n; i++)
        delete[] this->ar[i];
    
    delete[] this->ar;
}

int Matrix::getRows() const
{
    return this->m;
}

int Matrix::getCols() const
{
    return this->n;
}

Matrix& Matrix::operator=(const Matrix& rhs)
{
    this->m = rhs.m;
    this->n = rhs.n;
    this->ar = new double*[m];

    for (int i = 0; i < this->m; i++)
    {
        this->ar[i] = new double[n];
        for (int j = 0; j < this->n; j++)
            this->at(i,j) = rhs.at(i,j);

    }

// Thank you Geeks! https://www.geeksforgeeks.org/cpp/cpp-assignment-operator-overloading/
    return *this;
}

double& Matrix::at(unsigned int row, unsigned int col)
{
    return this->ar[row][col];
}

const double& Matrix::at(unsigned int row, unsigned int col) const
{
    return this->ar[row][col];
}

std::ostream& operator<<(std::ostream& os, const Matrix& m)
{
    unsigned int cols = m.getCols();
    unsigned int rows = m.getRows();

    for(int j = 0; j < rows; j++)
    {
        for(int i = 0; i < cols; i++)
        {
            os << setw(10) << m.at(i, j);
        }
        if (j != rows - 1) os << endl;
    }

    return os;
}

std::istream& operator>>(std::istream& is, Matrix& m)
{
    unsigned int cols = m.getCols();
    unsigned int rows = m.getRows();

    for(int j = 0; j < rows; j++)
    {
        for(int i = 0; i < cols; i++)
        {
            is >> m.at(i, j);
        }
    }

    return is;
}

Matrix operator+(const Matrix& m1, const Matrix& m2)
{
    unsigned int cols = m1.getCols();
    if (cols != m2.getCols()) abort();
    
    unsigned int rows = m1.getRows();
    if (rows != m2.getRows()) abort();

    Matrix m3{rows, cols};

    for(int j = 0; j < rows; j++)
    {
        for(int i = 0; i < cols; i++)
        {
            m3.at(i, j) = m1.at(i, j) + m2.at(i, j);
        }
    }

    return m3;
}

Matrix operator-(const Matrix& m1, const Matrix& m2)
{
    unsigned int cols = m1.getCols();
    if (cols != m2.getCols()) abort();

    unsigned int rows = m1.getRows();
    if (rows != m2.getRows()) abort();

    Matrix m3{2, 2};

    for(int j = 0; j < rows; j++)
    {
        for(int i = 0; i < cols; i++)
        {
            m3.at(i, j) = m1.at(i, j) - m2.at(i, j);
        }
    }

    return m3;
}

Matrix operator*(const Matrix& m1, const Matrix& m2)
{
    unsigned int cols = m1.getCols();
    if (cols != m2.getRows()) abort();

    unsigned int rows = m1.getRows();



}


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

    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            os << setw(10) << m.at(i, j);
        }
        if (i != rows - 1) os << endl;
    }

    return os;
}

std::istream& operator>>(std::istream& is, Matrix& m)
{
    unsigned int cols = m.getCols();
    unsigned int rows = m.getRows();

    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            is >> m.at(i, j);
        }
    }

    return is;
}

Matrix operator+(const Matrix& m1, const Matrix& m2)
{
    // Must have same number of columns and rows in order to add.
    unsigned int cols = m1.getCols();
    if (cols != m2.getCols()) abort();
    
    unsigned int rows = m1.getRows();
    if (rows != m2.getRows()) abort();

    Matrix output{rows, cols};

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            output.at(i, j) = m1.at(i, j) + m2.at(i, j);
        }
    }

    return output;
}

Matrix operator-(const Matrix& m1, const Matrix& m2)
{
    // Must have same number of columns and rows in order to subtract.
    unsigned int cols = m1.getCols();
    if (cols != m2.getCols()) abort();

    unsigned int rows = m1.getRows();
    if (rows != m2.getRows()) abort();

    Matrix output{rows, cols};

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            output.at(i, j) = m1.at(i, j) - m2.at(i, j);
        }
    }

    return output;
}

Matrix operator*(const Matrix& m1, const Matrix& m2)
{
    unsigned int cols1 = m1.getCols();
    unsigned int cols2 = m2.getCols();

    unsigned int rows1 = m1.getRows();
    unsigned int rows2 = m2.getRows();

    // Undefined if m1 doesn't have the same # columns as m2 has rows.
    if (cols1 != rows2) abort();

    Matrix output{rows2, cols2};

    // m3(i,j) = m1(j,1)*m2(1,i) + m1(i,2)*m2(2,j) + ... + m1(i,n)*m2(n,j)
    // Where n is the number of columns in the left-hand side matrix,
    // i is the number of rows in the right-hand side matrix,
    // and j is the number of columns in the right-hand side matrix.
    
    for (int i = 0; i < rows2; i++)
    {
        for (int j = 0; j < cols2; j++)
        {
            double sum = 0;

            for (int n = 0; n < cols1; n++)
            {
                sum += m1.at(j,n) * m2.at(n,i);
            }

            output.at(i,j) = sum;
        }
    }

    return output;
}

Matrix operator*(double scalar, const Matrix& m)
{
    unsigned int cols = m.getCols();
    unsigned int rows = m.getRows();

    Matrix output{rows, cols};

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            output.at(i,j) = m.at(i,j)*scalar;
        }
    }

    return output;
}

Matrix operator*(const Matrix& m, double scalar)
{
    return scalar*m;
}
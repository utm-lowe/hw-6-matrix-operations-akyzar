/**
 * @file affine.cpp
 * @author Aaron Kyzar
 * @brief Perform affine transformations on 2D points.
 * @version 1.0
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#include "matrix.h"
#include <iostream>
#include <cmath>

using namespace std;

// Transformation Matrix Creation Functions

/**
 * @brief Create a 3x3 identity matrix.
 * 
 * @return Matrix 
 */
Matrix transIdent();

/**
 * @brief Rotate about an angle in degrees
 * 
 * @param angle 
 * @return Matrix 
 */
Matrix transRotate(double angle);


/**
 * @brief Scale by factors sx and sy
 * 
 * @param sx 
 * @param sy 
 * @return Matrix 
 */
Matrix transScale(double sx, double sy);

/**
 * @brief Translate by tx and ty
 * 
 * @param tx 
 * @param ty 
 * @return Matrix 
 */
Matrix translate(double tx, double ty);

/**
 * @brief Prompt the user for transformations, return the resultant matrix.
 * 
 * @return Matrix 
 */
Matrix transformMenu();

/**
 * @brief Get the 3 element column vector affine point from the user.
 * 
 * @return Matrix 
 */
Matrix getPoint();

int main() 
{
    Matrix transform = transformMenu();

    // Display the transformation matrix
    cout << "Transformation Matrix: " << endl;
    cout << transform << endl;
    cout << endl;

    // transform points
    while(cin) {
        Matrix point = getPoint();

        point = transform * point;

        // If we have a new point, display it.
        if(cin) {
            cout << "Transformed Point: (" 
                 << point.at(0,0) << ", " << point.at(1,0) << ")" << endl;
        }
    }
}


// build an identity matrix
Matrix transIdent()
{
    Matrix output{3,3};
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (i == j) output.at(i,j) = 1;
            else        output.at(i,j) = 0;
        }
    }

    return output;
}


// build a rotation matrix
Matrix transRotate(double angle)
{
    double rotateMatrix[3][3] = {{cos(angle), -sin(angle), 0},
                                 {sin(angle),  cos(angle), 0},
                                 {         0,           0, 1}};

    Matrix output{3,3};
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            output.at(i,j) = rotateMatrix[i][j];
        }
    }


    return output;
}

// build a scaling matrix
Matrix transScale(double sx, double sy) 
{
    double scaleMatrix[3][3] = {{sx, 0, 0},
                                {0, sy, 0},
                                {0, 0, 1}};

    Matrix output{3,3};
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            output.at(i,j) = scaleMatrix[i][j];
        }
    }

    return output;
}

// build a translation matrix
Matrix translate(double tx, double ty) 
{
    double translateMatrix[3][3] = {{1, 0, tx},
                                    {0, 1, ty},
                                    {0, 0, 1}};

    Matrix output{3,3};
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            output.at(i,j) = translateMatrix[i][j];
        }
    }

    return output;
}

// do the transformation menu
Matrix transformMenu()
{
    Matrix result = transIdent();
    double x,y,angle;
    char choice;

    do {
        // get the choice
        cout << "(T)ranslate, (R)otate, (S)cale, or (D)one? ";
        cin >> choice;
        choice = toupper(choice);

        switch (choice)
        {
            case 'T':
                cout << "Enter the x and y translation: ";
                cin >> x >> y;
                result = translate(x,y) * result;
                break;

            case 'R':
                cout << "Enter the angle of rotation (degrees): ";
                cin >> angle;
                
                angle *= double(M_PI); // Convert degrees to radians
                angle /= 180.0;

                result = transRotate(angle) * result;
                break;

            case 'S':
                cout << "Enter the x and y scaling factors: ";
                cin >> x >> y;

                result = transScale(x,y) * result;
                break;

            default:
                cout << "Invalid choice. Please try again." << endl;
            case 'D':
                break;
        };

    }while(choice != 'D');

    return result;
}


// get the point from the user 
Matrix getPoint() 
{
    double x, y;

    Matrix output{3,1};
    cout << "Enter x and y: ";
    cin >> x >> y;

    output.at(0,0) = x;
    output.at(1,0) = y;
    output.at(2,0) = 1;

    return output;
}
#include <iostream>
#include <string>
#include "Base.h"
#include "QR_Decompo.h"
#include <math.h>

using namespace std;

int main()
{
    Base::resetLog();                                                                                         // Delete log file
    Base::appendLog("QR Decomposition using Householder Transformation project is started...!");              // Project start

    // Create an object of the Matrix class
    QR_HHT myMatrix;

    // Input values for the matrix
    myMatrix.inputMatrix();

    // Display the matrix
    myMatrix.displayMatrix();

    //the calculations
    myMatrix.calculation();

    //logging the Data
    myMatrix.ListData();

    Base::appendLog("QR Decomposition using Householder Transformation project project is finished...!");     // Project end
    return 0;
}

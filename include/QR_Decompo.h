#ifndef QR_HHT_H
#define QR_HHT_H
#include <Base.h>
#include <iostream>
#include <string>

using namespace std;

class QR_HHT : public Base
{
    public:
        QR_HHT();
        virtual ~QR_HHT();
        //methods
        void ListData();      //list the data of the matrices
        void inputMatrix(); // Member function to input matrix values
        void displayMatrix(); // Member function to display matrix
        void calculation(); //calculations

    protected:

    private:
        int rows;
        int cols;
        double** matrix;
        double** check;
        double** tempCheck;
        double** A;
        double** R;
        double** tempR;
        double** I;
        double** Q;
        double** tempQ;
        double* a_red;
        double a_red1;
        int sum = 0;
        double a_norm = 0;
        double gamma = 0;
        double* e;
        double* h_vector;
        double h_norm = 0;
        double beta = 0;
        double* unit_e;
        double** H_sub;
        double** e_D_e;
};

#endif // QR_HHT_H

#include "QR_Decompo.h"
#include <iostream>
#include <math.h>
#include <iomanip>
#include <Base.h>

QR_HHT::QR_HHT()
{
    // Ask user for matrix dimensions
    std::cout << "Enter the number of rows: ";
    std::cin >> rows;

    std::cout << "Enter the number of columns: ";
    std::cin >> cols;

    if (rows != cols) {
        std::cout << "Error: The matrix must be square." << std::endl;
        exit(1);  // Terminate the program
    }

    // Allocate memory for the 2D arrays
    matrix = new double*[rows];
    R      = new double*[rows];
    I      = new double*[rows];
    Q      = new double*[rows];
    H_sub  = new double*[rows];
    e_D_e  = new double*[rows];
    A      = new double*[rows];
    tempR  = new double*[rows];
    tempQ  = new double*[rows];
    check  = new double*[rows];
    tempCheck= new double*[rows];

    for (int i = 0; i < rows; ++i) {
        matrix[i] = new double[cols];
        R[i]      = new double[cols];
        I[i]      = new double[cols];
        Q[i]      = new double[cols];
        H_sub[i]  = new double[cols];
        e_D_e[i]  = new double[cols];
        A[i]      = new double[cols];
        tempR[i]  = new double[cols];
        tempQ[i]  = new double[cols];
        check[i]  = new double[cols];
        tempCheck[i]= new double[cols];

    }
}


QR_HHT::~QR_HHT()
{
    // Deallocate memory for the matrix
    for (int i = 0; i < rows; ++i) {
        delete[] matrix[i];
        delete[] R[i];
        delete[] I[i];
        delete[] Q[i];
        delete[] H_sub[i];
        delete[] e_D_e[i];
        delete[] A[i];
        delete[] tempR[i];
        delete[] tempQ[i];
        delete[] check[i];
        delete[] tempCheck[i];

    }
    delete[] matrix;
    delete[] R;
    delete[] I;
    delete[] Q;
    delete[] H_sub;
    delete[] e_D_e;
    delete[] A;
    delete[] tempR;
    delete[] tempQ;
    delete[] check;
    delete[] tempCheck;

}

void QR_HHT::inputMatrix() {
    std::cout << "Enter the matrix values:" << std::endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << "Element (" << i + 1 << ", " << j + 1 << "): ";
            std::cin >> matrix[i][j];
        }
    }
}
void QR_HHT::displayMatrix() {
    std::cout << "A:" << std::endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout <<matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }

}

void QR_HHT::ListData()
{
    sprintf(msg,"Matrix A :");
    appendLog(msg);
    for(int i = 0 ; i < rows ; ++i)
    {
        for(int j = 0 ; j < cols ; ++j)
        {
            sprintf(msg, "  %6.6f", matrix[i][j] );
            appendLog(msg);
        }
    }
    std::cout<<std::endl;
    sprintf(msg,"Matrix R :");
    appendLog(msg);
    for(int i = 0 ; i < rows ; ++i)
    {
        for(int j = 0 ; j < cols ; ++j)
        {
            sprintf(msg, "  %6.6f", R[i][j] );
            appendLog(msg);
        }
    }
    std::cout<<std::endl;
    sprintf(msg,"Matrix Q :");
    appendLog(msg);
    for(int i = 0 ; i < rows ; ++i)
    {
        for(int j = 0 ; j < cols ; ++j)
        {
            sprintf(msg, " %6.6f", Q[i][j] );
            appendLog(msg);
        }
    }

}

void QR_HHT::calculation()
{

    // Initialize A matrix
    for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < rows; ++j)
            {
                A[i][j] = matrix[i][j];
            }
        }


    //initializing R0, which equals to A
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            R[i][j]=A[i][j];
        }
    }

    //initializing the identity matrix
    for (int i = 0; i < rows; ++i)
    {
        for(int j = 0; j<cols; ++j)
        {
            if (i==j)
            {
                I[i][j] = 1;
            }
            else
            {
                I[i][j] = 0;
            }
        }
    }

    //initializing Q0 which is equal to the Identity Matrix
    for (int i = 0; i< rows; ++i)
    {
        for (int j = 0; j<cols; ++j)
        {
            Q[i][j] = I[i][j];
        }
    }

    //now the calculations start

    //assigning row amount of arrays to these vectors
    a_red = new double[rows];
    e = new double[rows];
    h_vector = new double[rows];
    unit_e = new double[rows];



    for ( sum = 0; sum < rows; sum++)
    {
        //we  need to make these values zero in the beginning of every loop and the reason is they have the value of the previous loop in them
        gamma = 0;
        a_norm = 0;
        h_norm = 0;
        beta = 0;
        for (int i = 0 ; i < rows ; ++i)
        {
            unit_e[i] = 0;
            for(int j = 0 ; j < rows ; ++j)
            {
                e_D_e[i][j] = 0;
                H_sub[i][j] = 0;
                tempR[i][j] = 0;
                tempQ[i][j] = 0;
            }
        }

        //reduced column vector of our original matrix and the first element
        std::cout<<"reduced column vector: "<<std::endl;
        for(int i = sum; i < rows; i++)
        {
            a_red[i] = matrix[i][sum];
            a_red1 = a_red[sum];
            std::cout<<a_red[i]<<std::endl;
        }
        std::cout<<std::endl;

        //the condition here will determine the sign of our h_vector equation and we also use it to find the norm of our a_red vector
        if (a_red1 >= 0)
        {
            for(int i = sum; i < rows; i++)
                {
                    a_norm = a_norm + (a_red[i]*a_red[i]);
                }
            gamma = sqrt(a_norm);
            std::cout<<"norm is: "<<gamma<<std::endl;
        }
        else
        {
            for(int i = sum; i < rows; i++)
                {
                    a_norm = a_norm + (a_red[i]*a_red[i]);
                }
            gamma = -sqrt(a_norm);
            std::cout<<"norm is: "<<gamma<<std::endl;
        }
        std::cout<<std::endl;

        //e is the unit vector, which looks like the reduced column vector of Identity so we use the same approach we had with a_red
        for(int i = sum; i < rows; i++)
        {
            e[i] = I[i][sum];
        }

        //we find the h_vector = (a_red)+(gamma*e)
        std::cout<<"h_vector : "<<std::endl;
        for (int i = sum; i < rows; i++)
        {
            h_vector[i] = a_red[i] + (gamma*e[i]);
            std::cout<<h_vector[i]<<endl;
        }
        std::cout<<std::endl;

        //next step is finding beta, which is the norm of h_vector so we use the same method for finding the norm of a_red
        for(int i = sum; i < rows; i++)
                {
                    h_norm = h_norm + (h_vector[i]*h_vector[i]);
                }
        beta = sqrt(h_norm);
        std::cout<<"norm of h_vector is: "<<beta<<std::endl;

        //finding the unit vector e = h_vector / beta
        std::cout<<"unit vector e"<<std::endl;
        for(int i = sum; i < rows; ++i)
        {
            unit_e[i] = h_vector[i]/beta;
            std::cout<<unit_e[i]<<std::endl;
        }
        std::cout<<std::endl;

        //finding e (dyadic) e
        std::cout<<"e dyadic e is:  "<<std::endl;
        for(int i = sum ; i < rows ; ++i)
        {
            for(int j = sum; j < rows ; ++j)
            {
                e_D_e[i][j]=unit_e[i]*unit_e[j];
                std::cout<<e_D_e[i][j]<<"   ";
            }
            std::cout<<std::endl;
        }
        std::cout<<std::endl;

        //now for finding h_sub = Identity - 2*e_D_e but since H is gonna be H_sub and the rest of the matrix should be filled with identity, i do both of those step here
        std::cout<<"Matrix H is:  "<<std::endl;
        for (int i = 0 ; i < rows ; ++i)
        {
            for (int j = 0 ; j < rows ; ++j)
            {
                H_sub[i][j] = I[i][j] - (2*e_D_e[i][j]);
                if(H_sub[i][j]>0)
                {
                    if(H_sub[i][j]<1e-5)
                        {
                            H_sub[i][j]=0;
                        }
                }
                if(H_sub[i][j]<0)
                {
                    if(H_sub[i][j]>-0.0001)
                        {
                            H_sub[i][j]=0;
                        }
                }

                std::cout << H_sub[i][j] << "      ";
            }
            std::cout<<std::endl;
        }
        std::cout<<std::endl;

        //finding R by updating it according to R=H*R
        std::cout<<"updated R"<<std::endl;
        for (int i = 0 ; i < rows; ++i)
        {
            for (int j = 0 ; j < rows ; ++j)
            {
                for (int k = 0 ; k < rows ; ++k)
                {
                    tempR[i][j] = tempR[i][j] + (H_sub[i][k] * R[k][j]);

                }
                std::cout<<tempR[i][j]<<"     ";
            }
            std::cout<<std::endl;
        }
        std::cout<<std::endl;

        //updating R
        for (int i = 0 ; i < rows ; ++i)
        {
            for(int j = 0 ; j< rows ; ++j)
            {
                R[i][j] = tempR[i][j];
            }
        }


        //finding Q by updating according to Q=Q.H(transpose)
        std::cout<<"updated Q"<<std::endl;
        for (int i = 0 ; i < rows ; ++i)
        {
            for (int j = 0 ; j < rows ; ++j)
            {
                for ( int k = 0 ; k < rows ; ++k)
                {
                    tempQ[i][j] = tempQ[i][j] + (Q[i][k] * H_sub[j][k]);

                }
                std::cout<<tempQ[i][j]<<"      ";
            }
            std::cout<<std::endl;
        }
        std::cout<<std::endl;

        //updating Q
        for (int i = 0 ; i < rows ; ++i)
        {
            for(int j = 0 ; j< rows ; ++j)
            {
                Q[i][j] = tempQ[i][j];
            }
        }
    }
    for ( sum = 0; sum < rows; sum++)
       {
        for (int i = 0 ; i < rows ; ++i)
            {
                    for(int j = 0 ; j < rows ; ++j)
                    {
                            tempCheck[i][j] = 0;
                    }
                }

        for (int i = 0 ; i < rows ; ++i)
            {
                    for (int j = 0 ; j < rows ; ++j)
                        {
                                for ( int k = 0 ; k < rows ; ++k)
                                {
                                        tempCheck[i][j] = tempCheck[i][j] + (Q[i][k] * R[k][j]);
                                }
                        }
            }

    for (int i = 0 ; i < rows ; ++i)
            {
                    for(int j = 0 ; j< rows ; ++j)
                    {
                            check[i][j] = tempCheck[i][j];
                    }
            }
        }
     std::cout<<"Q*R will be:"<<std::endl;
     for ( int i = 0 ; i < rows ; i++ )
    {
        for (int j = 0 ; j < cols ; j++)
          {
               std::cout<<check[i][j]<<"         ";
          }
        std::cout<<std::endl;
    }
}

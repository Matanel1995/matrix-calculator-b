//#include "sources/Matrix.hpp"
#include "sources/Matrix.cpp"
#include <iostream>
#include <sstream>

using namespace std;
using namespace zich;

// function to create the new matrixes

void setMat(Matrix &mat){
    while (true)
    {
        try{
            cin >> mat;
            break;
        }
        catch (exception & e){
            cout << e.what() << " Try again with the givex syntax!";
        }
    }
}

int main(){
    Matrix mat1;
    Matrix mat2;
    int oprtr;
    //print intructions for the client
    cout << "Please enter 2 Matrixes by the following syntax: \n (1)Make sure you entered space between 2 values in the same row.\n (2)if you want to start new row type ',' and the space!." << endl;
    cout << " Enter values to the first Matrix!" << endl;
    cout << " Enter values to the second Matrix!" << endl;
    setMat(mat1);
    setMat(mat2);
    // ask the user for the operation he want to make 
    cout << "Choose what operation you want to do on those matrix." << endl;
    cout << "You can choose +,-,*,'/'." << endl;
    cout << "You can also compare between the matrixes." << endl;
    cout << "Choose 1 for Matrix addition." << endl;
    cout << "Choose 2 for Matrix substraction." << endl;
    cout << "Choose 3 for Matrix multiplaction." << endl;
    cout << "Choose 4 to check if mat1 is bigger then mat 2." << endl;
    cout << "Choose 5 to exit the program." << endl;
    cin >> oprtr;
    while(true){
        switch (oprtr){
            case 1: // For + operator
                cout << (mat1 + mat2) << endl;
                break;
            case 2:
                cout << (mat1 - mat2) << endl;
                break;
            case 3:
                cout << (mat1 * mat2) << endl;
                break;
            case 4:
                if(mat1 > mat2){
                    cout << "Mat1 is bigger then Mat2" << endl;
                }
                else{
                    cout << "Mat1 is not bigger then Mat2" << endl;
                }
                break;
            case 5:
                exit(1);
            default:
            cout << "Chosse number between 1 to 4!" << endl;
                break;
        }
        cin >> oprtr;
    }
}

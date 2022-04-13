#include <iostream>
#include <string>
#include <vector>
using namespace std;
namespace zich{
    class Matrix{
        private:
            int row;
            int col;
            vector <double> matrix;
        public:
            Matrix(vector<double> matrix, int row, int col);
            Matrix(const Matrix&mat);
            ~Matrix(); // defult destractor

            //Plus operators
            Matrix operator + (const Matrix&mat);
            Matrix& operator += (const Matrix&mat1);
            Matrix operator + ();
            Matrix operator ++ ();
            Matrix operator ++(int);


            //Minus operators
            Matrix operator - (const Matrix&mat);
            Matrix&  operator -= (const Matrix&mat1);
            Matrix operator - ();
            Matrix operator -- ();
            Matrix operator --(int);

            //Multiplaction operators
            Matrix operator * (const Matrix&mat);
            Matrix operator * (double num);
            friend Matrix operator * (int num, Matrix mat);
            friend Matrix operator * (double num, Matrix mat);
            Matrix operator * (int num);
            Matrix operator *= (int scalar);
            Matrix operator *= (double scalar);
            Matrix& operator *= (const Matrix&mat1);

            //Comperations operators
            bool operator > (Matrix&mat1);
            bool operator >= (Matrix&mat1);
            bool operator < (Matrix&mat1);
            bool operator <= (Matrix&mat1);
            bool operator != (Matrix&mat1);
            bool operator == (const Matrix &mat1);
            friend bool operator == (const Matrix &mat1, const Matrix &mat2);

            //Input and Output operators
            friend ostream& operator << (ostream &out ,Matrix const &matrix);
            friend istream& operator >> (istream &in ,Matrix  &matrix);

            //Getters functions
            int getRows() const {return this->row; }
            int getCols() const {return this->col; }
            double getAt(unsigned int pos){return this->getMatrix().at(pos); }
            vector<double> getMatrix() const {return this->matrix;}

            //Seters functions
            void setIndexAt(unsigned int pos, double value);

            //input check
            bool isGood(const Matrix &mat) const;

            //Sum function to sum all the matrix values
            double CalcSum();
    };
}
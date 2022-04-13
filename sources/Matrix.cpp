#include <iostream>
#include <string>
#include "Matrix.hpp"
#include<vector>
using namespace zich;
using namespace std;

zich::Matrix::Matrix(vector<double> matrix, int row, int col){
    if (row < 0 || col < 0){
        throw std::invalid_argument{"Row or Col cant be nrgative!"};
    }
    if (row * col != matrix.size()){
        throw std::invalid_argument{"Vector and matrix not the same size!"};
    }
    this->row = row;
    this->col = col;
    this->matrix = std::move(matrix);
}
zich::Matrix::Matrix(const Matrix&mat){
    matrix = mat.matrix;
    row = mat.row;
    col = mat.col;
}

zich::Matrix::~Matrix(){}

//****************************************************************//
//Seters functions
void Matrix::setIndexAt(unsigned int pos , double value){
    if(pos < 0 || pos >= this->col*this->row){
        throw std::invalid_argument{"Index is out of range"};
    }
    this->matrix.at(pos) = value;
}
//****************************************************************//

//****************************************************************//
//Plus operators
Matrix Matrix::operator + (const Matrix&mat){
    if(this->getCols() !=  mat.getCols() || this->getRows() != mat.getRows()){
        throw std::invalid_argument{"Matrix are not the same size!"};
    }
    Matrix ans (this->matrix, this->row, this->col);
    for(int i=0; i < this->getRows() ; i++){
        for(int j = 0 ; j<this->getCols() ; j++){
            unsigned int index = (unsigned int)((i*this->getCols()) + j);
            ans.setIndexAt(index, ans.getAt(index) + mat.matrix.at(index));
        }
    }
    return ans;
}

Matrix& Matrix::operator += (const Matrix&mat1){
    *this = *this + mat1;
    return *this;

}
Matrix Matrix::operator + (){
    return *this;
}

Matrix Matrix::operator ++ (){
    for(int i=0; i < this->getRows() ; i++){
        for(int j = 0 ; j<this->getCols() ; j++){
            unsigned int index = (unsigned int)((i*this->getCols()) + j);
                this->setIndexAt(index , this->getAt(index) + 1);
        }
    }
    return *this;
}
Matrix Matrix::operator ++(int){
    Matrix returnedAns = *this;
    for(int i=0; i < this->getRows() ; i++){
        for(int j = 0 ; j<this->getCols() ; j++){
            unsigned int index = (unsigned int)((i*this->getCols()) + j);
                this->setIndexAt(index , this->getAt(index) + 1);
        }
    }
    return returnedAns;
}
//****************************************************************//

//****************************************************************//
//Minus operators
Matrix Matrix::operator - (const Matrix&mat){
    if(this->getCols() !=  mat.getCols() || this->getRows() != mat.getRows()){
        throw std::invalid_argument{"Matrix are not the same size!"};
    }
    Matrix ans (this->matrix, this->row, this->col);
    for(int i=0; i < this->getRows() ; i++){
        for(int j = 0 ; j<this->getCols() ; j++){
            unsigned int index = (unsigned int)((i*this->getCols()) + j);
            ans.setIndexAt(index, ans.getAt(index) - mat.matrix.at(index));
        }
    }
    return ans;
}
Matrix& Matrix::operator -= (const Matrix&mat1){
    return (*this = *this - mat1);
}
Matrix Matrix::operator - (){
    for(int i=0; i < this->getRows() ; i++){
        for(int j = 0 ; j<this->getCols() ; j++){
            unsigned int index = (unsigned int)((i*this->getCols()) + j);
            if(this->getAt(index) != 0){
                this->setIndexAt(index , this->getAt(index)* -1);
            }
        }
    }
    return *this;
}
Matrix Matrix::operator -- (){
    for(int i=0; i < this->getRows() ; i++){
        for(int j = 0 ; j<this->getCols() ; j++){
            unsigned int index = (unsigned int)((i*this->getCols()) + j);
                this->setIndexAt(index , this->getAt(index) - 1);
        }
    }
    return *this;
}
Matrix Matrix::operator --(int){
    Matrix returnedAns = *this;
    for(int i=0; i < this->getRows() ; i++){
        for(int j = 0 ; j<this->getCols() ; j++){
            unsigned int index = (unsigned int)((i*this->getCols()) + j);
                this->setIndexAt(index , this->getAt(index) - 1);
        }
    }
    return returnedAns;
}
//****************************************************************//

//****************************************************************//
//Multiplaction operators
Matrix Matrix::operator * (const Matrix&mat){
    double temp = 0;
    unsigned int newMatValue = 0;
    unsigned long vectorSize = (unsigned int)(this->getRows() * mat.getCols());
    if(this->getCols() != mat.getRows()){
        throw std::invalid_argument{"Matrix cant be muliplied!"};
    }
    std::vector<double> vectorTemp(vectorSize);
    Matrix ans (vectorTemp, this->getRows(), mat.getCols());
    for(int i=0; i< this->getRows();i++){
        for(int j=0; j<mat.getCols(); j++){
            for(int k=0; k<this->getCols();k++){
                unsigned int indexThis = (unsigned int)((i * this->getCols()) + k);
                unsigned int indexMat = (unsigned int)((k * mat.getCols()) + j);
                temp += this->getAt(indexThis) * mat.matrix.at(indexMat);
            }
            ans.setIndexAt(newMatValue++, temp);
            temp = 0;
        }
    }
    return ans;
}

Matrix Matrix:: operator * (double num){
    for(int i=0; i < this->getRows() ; i++){
        for(int j = 0 ; j<this->getCols() ; j++){
            unsigned int index = (unsigned int)((i*this->getCols()) + j);
            if(this->getAt(index) != 0){
                this->setIndexAt(index , this->getAt(index)*num);
            }
        }
    }
    return *this;
}
Matrix Matrix:: operator * (int num){
    Matrix tempAns = *this;
    for(int i=0; i < this->getRows() ; i++){
        for(int j = 0 ; j<this->getCols() ; j++){
            unsigned int index = (unsigned int)((i*this->getCols()) + j);
            if(this->getAt(index) != 0){
                double temp = this->getAt(index) * num;
                tempAns.matrix.at(index) = temp;
                // this->setIndexAt(index , this->getAt(index)*num);
            }
        }
    }
    return tempAns;
}
Matrix zich::operator * (int num, Matrix mat){
    for(int i=0; i < mat.getRows() ; i++){
        for(int j = 0 ; j<mat.getCols() ; j++){
            unsigned int index = (unsigned int)((i*mat.getCols()) + j);
            if(mat.getAt(index) != 0){
                mat.setIndexAt(index , mat.getAt(index)*num);
            }
        }
    }
    return mat;
}
Matrix zich::operator * (double num, Matrix mat){
    for(int i=0; i < mat.getRows() ; i++){
        for(int j = 0 ; j<mat.getCols() ; j++){
            unsigned int index = (unsigned int)((i*mat.getCols()) + j);
            if(mat.getAt(index) != 0){
                mat.setIndexAt(index , mat.getAt(index)*num);
            }
        }
    }
    return mat;
}
Matrix Matrix::operator *= (int scalar){
    *this = *this * scalar;
    return (*this);
    }
Matrix Matrix::operator *= (double scalar){
    *this = *this * scalar;
    return (*this);
}
Matrix& Matrix::operator *= (const Matrix&mat1){
    return (*this = *this * mat1);
}
//****************************************************************//

//****************************************************************//
//Comperations operators
bool Matrix::operator > (Matrix&mat1){
    if(this->getRows() != mat1.getRows() || this->getCols() != mat1.getCols()){
        throw std::invalid_argument{"Matrix not same size!"};
    }
    if(this->CalcSum() > mat1.CalcSum()){
        return bool(1);
    }
    return bool(0);
}

bool Matrix::operator >= (Matrix&mat1){
    if(*this > mat1 || !(*this > mat1 || *this < mat1)){
        return bool(1);
    }
    return bool(0);
    }

bool Matrix::operator < (Matrix&mat1){
    if(this->getRows() != mat1.getRows() || this->getCols() != mat1.getCols()){
        throw std::invalid_argument{"Matrix not same size!"};
    }
    if(this->CalcSum() < mat1.CalcSum()){
        return bool(1);
    }
    return bool(0);
    }

bool Matrix::operator <= (Matrix&mat1){
    if(*this < mat1 || !(*this > mat1 || *this < mat1)){
        return bool(1);
    }
    return false;
}

bool Matrix::operator != (Matrix&mat1){
    return !this->operator==(mat1);
    }

bool Matrix::operator == (const Matrix&mat1){
    if(this->isGood(mat1)){
        for(int i=0; i < this->getRows() ; i++){
            for(int j = 0 ; j<this->getCols() ; j++){
                unsigned int index = (unsigned int)((i*this->getCols()) + j);
                if(this->getAt(index) != mat1.matrix.at(index)){
                    return false;
                }
            }
        }
    }
    return true;
}

bool zich::operator == (const Matrix &mat1, const Matrix &mat2){
    if(mat1.getCols() == mat2.getCols() && mat1.getRows() == mat2.getRows()){
        for(int i=0; i < mat1.getRows() ; i++){
            for(int j = 0 ; j<mat1.getCols() ; j++){
                unsigned int index = (unsigned int)((i*mat1.getCols()) + j);
                if(mat1.getMatrix().at(index) != mat2.getMatrix().at(index)){
                    return false;
                }
            }
        }
    }
    else{
        throw std::invalid_argument{"Matrix not the same size!"};
    }
    return true;
}
//****************************************************************//

//****************************************************************//
//Input and Output operators
ostream& zich::operator<<(ostream& out , const Matrix& matrix){
    for(int i=0; i<matrix.getRows();i++){
        out<< "[";
        for(int j=0;j<matrix.getCols();j++){
            unsigned int index = (unsigned int)((i*matrix.getCols())+j);
            if(j == matrix.getCols()-1){
                out << matrix.matrix.at(index);    
            }
            else{
                out << matrix.matrix.at(index) << " ";
            }
        }
        if(matrix.getRows()-1 == i){
            out << "]";    
        }
        else{
            out << "]" << endl;
        }
    }
    return out;
}

istream& zich::operator >>(istream& in,Matrix &mat){
    vector<double> vec;
    int row=0;
    int rowLenght = 1;
    int counter = 1;
    char last=' ';
    char beforeLast=',';
    double number = 0;
    bool first = false;
    string tempNum;
    char temp = in.get();
    while(temp!='\n'){
        if(temp==' '){
            number= stod(tempNum);
            vec.push_back(number);
            tempNum="";
            counter++;
        }
        if(temp==','){
            row++;
            if(first&&rowLenght!=counter){
                throw invalid_argument("wrong input for matrix");
            }
            if(!first) {
                rowLenght = counter;
                first= true;
            }
            counter=0;

        }
            if(temp!='['&&temp!=']') {
                tempNum += temp;
            }
            temp = in.get();

        }
    mat.col=rowLenght;
    mat.row = row;
    mat.matrix = vec;
    return in;
}
//****************************************************************//

//****************************************************************//
// Function to check if i can make mathemtics opretaions with the given 2 matrix.
bool Matrix::isGood(const Matrix &mat) const{
    if(this->getCols() <0 || this->getRows() < 0 || this->getCols() != mat.getCols() || this->getRows() != mat.getRows()){
        throw std::logic_error{"The matrixes are NOT the same size!"};
    }
    return true;
}
//****************************************************************//

double Matrix::CalcSum(){
    double ans = 0;
    for(int i=0; i<this->getRows();i++){
        for(int j=0;j<this->getCols();j++){
            unsigned int index = (unsigned int)((i*this->getCols())+j);
            ans += this->getAt(index);
        }
    }
    return ans;
}
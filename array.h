#ifndef ARRAY_H_INCLUDED
#define ARRAY_H_INCLUDED
#include <iostream>
using namespace std;

float** copy2DArrayToPointer(float arr[][5],int rows, int cols){
    float **ptr = new float*[rows];
    for (int i = 0; i < rows; ++i) {
        ptr[i] = new float[cols];
    }
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            ptr[i][j] = arr[i][j];
        }
    }
    return ptr;
}
float** copy2DArrayToPointer(float arr[][4],int rows, int cols){
    float **ptr = new float*[rows];
    for (int i = 0; i < rows; ++i) {
        ptr[i] = new float[cols];
    }
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            ptr[i][j] = arr[i][j];
        }
    }
    return ptr;
}

void print2DArray(float arr[][5],int rows, int cols ){
  cout << endl;
    for(int i = 0;i < rows ;i++){
        for(int j = 0; j < cols; j++){
            cout.width(7);
            cout.precision(4);
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}


void print2DArray( float **arr,  int rows,int cols){
    cout << endl;
    for(int i = 0;i < rows ;i++){
        for(int j = 0; j < cols; j++){
            cout.width(7);
            cout.precision(4);
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}

void delete2Darray(float **ar, int rows){
        for(int i = 0; i < rows; ++i) {
            delete [] ar[i];
        }
        delete [] ar;
}

void swap(float &a, float &b ){
    float temp = a;
    a = b;
    b = temp;

}
void swapRows(float **ar , int numberOfColumns, int row1, int row2){


    for(int j = 0;j < numberOfColumns; j++){
        swap(ar[row1][j],ar[row2][j]);
        }
}
void swapColumns(float **ar,int numberOfRows, int col1, int col2){

    for(int i = 0;i < numberOfRows; i++){
        swap(ar[i][col1],ar[i][col2]);
        }
}

#endif // ARRAY_H_INCLUDED

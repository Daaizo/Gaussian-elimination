#include <iostream>
#include <math.h>
using namespace std;




float** loadData();
void printMatrix(float** arr, int rows, int cols);
void menu();

float** copy2DArrayToPointer(float arr[][5],int rows, int cols);
void delete2DArray(float** arr, int rows);
float* arrayWithCoefficients(float  **arr, int rows,int step);
float* gauss(float** arr,  int rows, int cols);

float numberCloseToZero = 1e-7;

int main(){


    menu();


    return 0;
}

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







void delete2DArray(float** arr, int rows){

    for(int i = 0; i < rows; ++i) {
        delete [] arr[i];
    }
    delete [] arr;
}
void printMatrix( float **arr,  int rows,int cols){
    cout << endl;

    for(int i = 0;i < rows ;i++){
        for(int j = 0; j < cols; j++){
            cout.width(5);
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }

}
float** loadData(){
    cout << " Podaj ilosc niewiadomych :";
    int n ;
    cout << " Podaj ilosc rownan :";
    int r ;
    string equations ;
//    float tab[] ;
    cin >> n;


}



float* arrayWithCoefficients(float  **arr, int rows,int step){
    float *coef = new float[rows-step];
    int startingRow = step;
    cout << "\n tablica wspolczynnikow\n ";
    for(int i = 0 ; i < rows-step; i++){
        coef[i] = (arr[startingRow][step-1])/(arr[step-1][step-1]);
        cout << coef[i] << " ";
        startingRow++;
    }
    return coef;

}

void menu(){
    int choice = 0, example = 0 ;
    float **mainArray;
    cout << "\n1.Gotowy zbior danych\n2.Wprowadzanie danych z klawiatury" << endl;
    cin >> choice;
    float example1[4][5] = { {1,1,0,-3,1}, {1,4,-1,-4,-2},{0.5,0.5,-3,-5.5,1.5} ,{1.5,3,-5,-9,-0.5}};
    float **ptr1 = copy2DArrayToPointer(example1, 4,5);
    float example2[4][5] = {{1,2,-1,2,0} ,{1,0,-2,4,4}, {0,-3,1.5,7,0}, {0,-1,1,6,-1}};
    float **ptr2 = copy2DArrayToPointer(example2, 4,5);
    switch(choice){
        case 1: {

            cout << " Przyklad 1 : wynik poprawny = [-1,-1,1,-1]";
            printMatrix(ptr1, 4, 5);
            cout << " Przyklad 2 : wynik poprawny = [0,-1,-2,0]";
            printMatrix(ptr2, 4, 5);
            cout <<"\n wybierz przyklad : ";
            cin >> example;
            break;
        }
        case 2 : {
            loadData();
            break;
        }
        default:{
            cout << "Zly wybor ";
            exit(4);
        }
    }







    cout << " \n1.Podstawowa elimacja Gaussa\n2.\n0.wyjscie" ;
    do {
        cout << endl;
        cin >> choice;
        switch(choice){
            case 1:{
                gauss(ptr1, 4,5);
                cout << "wynik = ";
                break;
            }

            case 2:{

                break;
            }

            case 0:{
                cout << "wychodzenie " ;
                break;
            }

            default : {
                cout << " wybrano zly numer ";
                break;
            }
        }
    }while(choice != 0);

}
float* gauss(float  **arr,  int rows, int cols){



    int step = 1;
    float *coefficients  = arrayWithCoefficients(arr, rows,step);
    while(step < rows){
        cout << "\n step " << step << endl;
        for(int i = step ; i < rows ; i++){
            for(int j = step-1; j < cols ;j++){

                if(i-1 == j-1 && fabs(arr[i][j]) <= numberCloseToZero){ // wartosc na przekatnej = 0
                    //przesuniecie wierszy ?

                }
                else{ // wartosc na przekatnej != 0

                    arr[i][j] -=   (coefficients[i-1]*arr[step-1][j]);
                }

            }

            printMatrix(arr,rows,cols);
        }
        step++;
        coefficients = arrayWithCoefficients(arr,rows,step);
    }
    /*
    int step = 0;
    while(step < rows){
        cout << "\n step " << step << endl;
        for(int i = step ; i < rows - 1 ; i++){
            for(int j = step; j < cols ;j++){

                if(i == j && fabs(arr[i][j]) <= numberCloseToZero){ // wartosc na przekatnej = 0
                    //przesuniecie wierszy ?

                }
                else{ // wartosc na przekatnej != 0

                    arr[i+1][j] -=   (coefficients[i]*arr[step][j]);
                }

            }

            printMatrix(arr,rows,cols);
        }
        step++;
        coefficients = arrayWithCoefficients(arr,rows,step);
    }
    */

}

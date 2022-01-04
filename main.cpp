#include <iostream>
#include <math.h>
using namespace std;


class Gauss{

private :
    float numberCloseToZero = 1e-7;
    int rows;
    int cols;
    float ** array;

    float* arrayWithCoefficients(int step);
    void printMatrix(float** arr, int rows, int cols);
    float** copy2DArrayToPointer(float arr[][5],int rows, int cols);
    void getPrepared2DArray();
    bool isDiagonalValueEqualZero(int i, int j);
    void pickInput();
    void pickMethod();


    void defaultElimination();
public :


    void menu();


    ~Gauss(){
        for(int i = 0; i < this->rows; ++i) {
            delete [] this->array[i];
        }
        delete [] this->array;
    }
};



float** loadData();





int main(){
    Gauss gauss;
    gauss.menu();


    return 0;
}
void Gauss::pickInput(){
    int choice = 0;
    cout << "\n1.Gotowy zbior danych\n2.Wprowadzanie danych z klawiatury" << endl;
    cin >> choice;
    switch(choice){
        case 1: {

            this->getPrepared2DArray();
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
}
void Gauss::getPrepared2DArray(){
    float example1[4][5] = { {1,1,0,-3,1}, {1,4,-1,-4,-2},{0.5,0.5,-3,-5.5,1.5} ,{1.5,3,-5,-9,-0.5}};
    float example2[4][5] = {{1,2,-1,2,0} ,{1,0,-2,4,4}, {0,-3,1.5,7,0}, {0,-1,1,6,-1}};
    float **ptr1 = copy2DArrayToPointer(example1, 4,5);
    float **ptr2 = copy2DArrayToPointer(example2, 4,5);

    int chooice;
    cout << " Przyklad 1 : wynik poprawny = [-1,-1,1,-1]";
    this->printMatrix(ptr1, 4, 5);
    cout << " Przyklad 2 : wynik poprawny = [0,-1,-2,0]";
    this->printMatrix(ptr2, 4, 5);
    cout <<"\n wybierz przyklad : ";
    cin >> chooice;
    if(chooice == 1) {
        this->rows = 4;
        this->cols = 5;
        this->array = ptr1;
    }
    else if(chooice == 2){
        this->rows = 4;
        this->cols = 5;
        this->array = ptr2;

    }
}
float** Gauss::copy2DArrayToPointer(float arr[][5],int rows, int cols){
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
void Gauss::printMatrix( float **arr,  int rows,int cols){
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



float* Gauss::arrayWithCoefficients(int step){
    int rows = this->rows;
    int startingRow = step;
    float *coef = new float[rows-step];

    cout << "\n tablica wspolczynnikow\n ";
    for(int i = 0 ; i < rows-step; i++){
        coef[i] = (this->array[startingRow][step-1])/(this->array[step-1][step-1]);
        cout << coef[i] << " ";
        startingRow++;
    }
    return coef;
}
void Gauss::pickMethod(){

    int choice = 0;
    cout << " \n1.Podstawowa elimacja Gaussa\n2.Elminacja z wyborem elementu max\n0.wyjscie" ;
    do {
        cout << endl;
        cin >> choice;
        switch(choice){
            case 1:{
                this->defaultElimination();
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
void Gauss::menu(){
    this->pickInput();
    this->pickMethod();

}
void Gauss::defaultElimination(){
    int step = 1;
    int rows = this->rows;
    int cols = this->cols;


    float *coefficients  = arrayWithCoefficients(step);
    while(step < rows){
        cout << "\n step " << step << endl;
        for(int i = step ; i < rows ; i++){
            for(int j = step-1; j < cols ;j++){

                if(this->isDiagonalValueEqualZero(i,j)){ // wartosc na przekatnej = 0
                    //przesuniecie wierszy ?

                }
                else{ // wartosc na przekatnej != 0

                   this->array[i][j] -=   (coefficients[i-1]*this->array[step-1][j]);
                }

            }

            printMatrix(this->array,rows,cols);
        }
        step++;
        coefficients = arrayWithCoefficients(step);
    }

}
bool Gauss::isDiagonalValueEqualZero(int i, int j){
    return i == j && fabs(this->array[i][j]) <= this->numberCloseToZero;
}

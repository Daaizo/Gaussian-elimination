#include <iostream>
#include <math.h>
using namespace std;


class Gauss{

private :
    float numberCloseToZero = 1e-7;
    int rows;
    int cols;
    float ** array;


    void print2DArray(float** arr, int rows, int cols);
    void print2DArray(float ar[][5],int rows, int cols );
    void printEquationFromMatrix();
    float** copy2DArrayToPointer(float arr[][5],int rows, int cols);
    void getPrepared2DArray();
    void pickInput();
    void pickMethod();
    bool isDiagonalValueEqualZero(int i, int j);

    float* arrayWithCoefficients(int step);
    void defaultElimination();
    float* getResultFromRowEchelonForm();  // macierz schodkowa
public :



    void menu();
    ~Gauss(){
        for(int i = 0; i < this->rows; ++i) {
            delete [] this->array[i];
        }
        delete [] this->array;
    }
};









int main(){
    Gauss gauss;
    gauss.menu();


    return 0;
}

void Gauss::menu(){
    this->pickInput();
    this->pickMethod();

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
            //loaddata here
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
    float example3[4][5] = { {9,10,7,-21,-33}, {-3,-7.5,6.5,0,17},{-6.25,-12.5,0.25,5.25,24.25},{2.25,-2.5,4,-5.25,-1}};


    int chooice;
    cout << " Przyklad 1 : wynik poprawny  [-1,-1,1,-1]";
    this->print2DArray(example1, 4, 5);
    cout << " Przyklad 2 : wynik poprawny  [0,-1,-2,0]";
    this->print2DArray(example2, 4, 5);
    cout << " Przyklad 3 : wynik poprawny  x4=1 x3=1 x2=-1 x1=-1";
    this->print2DArray(example3, 4, 5);
    cout <<"\n wybierz przyklad : ";
    cin >> chooice;
    if(chooice == 1) {

        this->rows = 4;
        this->cols = 5;
        float **ptr = copy2DArrayToPointer(example1,4,5);
        this->array = ptr;
    }
    else if(chooice == 2){
        this->rows = 4;
        this->cols = 5;
        float **ptr = copy2DArrayToPointer(example2,4,5);
        this->array = ptr;

    }
    else if(chooice == 3){
        this->rows = 4;
        this->cols = 5;
        float **ptr = copy2DArrayToPointer(example3,4,5);
        this->array = ptr;

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

void Gauss::print2DArray(float arr[][5],int rows, int cols ){
  cout << endl;

    for(int i = 0;i < rows ;i++){
        for(int j = 0; j < cols; j++){
            cout.width(5);
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }


}


void Gauss::print2DArray( float **arr,  int rows,int cols){
    cout << endl;

    for(int i = 0;i < rows ;i++){
        for(int j = 0; j < cols; j++){
            cout.width(5);
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }

}

void Gauss::printEquationFromMatrix(){


}
float* Gauss::getResultFromRowEchelonForm(){

    int rows = this->rows;
    float **ar = this->array;
    int lastColumn = this->cols -1 ;
    float *result = new float[rows];
    float temp = 0;
    rows--;
    result[rows] = (ar[rows][lastColumn])/(ar[rows][rows]);
    print2DArray(ar,4,5);
    cout << "x"<<rows+1<< "=" << result[rows]<< "\t" ;
    for(int i = rows -1 ;i >= 0 ; i--){ // start od przedostatniego wiersza
        temp = 0 ;
        for(int j = i + 1 ; j <= rows ; j++){
            temp -= result[j]*ar[i][j];
            //cout << "\n i = " << i << " j= " << j;
            //cout << "\n wartosc  = " << temp ;
            //cout << " ostatnia kolumna : " << ar[i][lastColumn];
        }
        temp += ar[i][lastColumn];
        //cout << " temp po dodaniu : " << temp;
        result[i]  = temp / (ar[i][i]);
        cout << "x"<<i+1<< "=" <<result[i] <<  "\t" ;

    }
    delete [] result;



}

float* Gauss::arrayWithCoefficients(int step){
    int rows = this->rows;
    int startingRow = step;
    float *coef = new float[rows];


    cout << "\n tablica wspolczynnikow\n ";
    for(int i = startingRow , j = step - 1; i < rows; i++){
        coef[i] = (this->array[i][j])/(this->array[j][j]);

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
                this->getResultFromRowEchelonForm();
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

void Gauss::defaultElimination(){
    int step = 1;
    int rows = this->rows;
    int cols = this->cols;

//TODO sprwadzicz czy 1 element nie jest rowny zero i jak tak to zamienic wiersze
    float *coefficients  = arrayWithCoefficients(step);
    while(step < rows){
        cout << "\n step " << step << endl;
        for(int i = step ; i < rows ; i++){
            for(int j = step-1; j < cols ;j++){

                if(this->isDiagonalValueEqualZero(i,j)){ // wartosc na przekatnej = 0
                    //przesuniecie wierszy ?

                }
                else{ // wartosc na przekatnej != 0

                   this->array[i][j] -=   (coefficients[i]*this->array[step-1][j]);
                }

            }

            print2DArray(this->array,rows,cols);
        }
        step++;
        coefficients = arrayWithCoefficients(step);
    }

}
bool Gauss::isDiagonalValueEqualZero(int i, int j){
    return i == j && fabs(this->array[i][j]) <= this->numberCloseToZero;
}

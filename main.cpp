#include <iostream>
#include <math.h>
#include "array.h"
using namespace std;


class Gauss{

private :
    float numberCloseToZero = 1e-7;
    float **array = nullptr;
    float *orderOfColumns = nullptr;
    int rows;
    int cols;
    bool areColumnsSwapped = false;

    void pickInput();
    void pickMethod();
    void getPrepared2DArray();
    void setArray(float ** ar, int r, int c);
    void loadDataFromUser();

    float* arrayWithCoefficients(int step);
    float* getResultFromRowEchelonForm();  // macierz schodkowa
    void createArrayWithOrderOfColumns();
    float* fixResult(float *result);
    void defaultElimination(int typeOfElimantion);
    void findMaxElementAndSwapItToTheDiagonal(float **ar, int start);
    void swapWithRowsUnderCurrentRow(int step);
    void swapRowsEveryPossibleWay();
    bool isElementEqualZero(int i, int j);
    bool isEquationSolvable();
public :

    ~Gauss(){
        delete2Darray(this->array, this->rows);
        delete [] orderOfColumns;
        }
    void menu();

};




int main(){
    Gauss gauss;
    gauss.menu();


    return 0;
}

void Gauss::menu(){
    pickInput();
    pickMethod();

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
            this->loadDataFromUser();
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
    float example2[4][5] = {{0,2,-1,2,0} ,{0,0,-2,4,4}, {0,-3,1.5,7,0}, {1,-1,1,6,-1}};
    float example3[4][5] = { {2.25,-2.5,4,-5.25,-1}, {-3,-7.5,6.5,0,17},{-6.25,-12.5,0.25,5.25,24.25},{9,10,7,-21,-33}};
    //float example4[3][4] = { {1,2,-1,-1},{-1,0,3,4},{-2,-3,1,-1}};
    float example4[3][4] = { {0,2,-1,0},{1,0,-2,4},{10,0,3,0}};

    int chooice;
    cout << "\nPrzyklad 1 : wynik poprawny  x4=-1 x3=1 x2=-1 x1=-1";
    print2DArray(example1, 4, 5);
    cout << "\nPrzyklad 2 : wynik poprawny  x4=0 x3=-2 x2=-1 x1=0";
    print2DArray(example2, 4, 5);
    cout << "\nPrzyklad 3 : wynik poprawny  x4=1 x3=1 x2=-1 x1=-1";
    print2DArray(example3, 4, 5);
    cout << "\nPrzyklad 4 : wynik poprawny   x3=-1.739 x2=-0.8696 x1=0.5217";
    float ** tempP = copy2DArrayToPointer(example4, 3,4);
    print2DArray(tempP, 3, 4);
    delete2Darray(tempP, 3);
    cout <<"\n wybierz przyklad : ";
    cin >> chooice;
    if(chooice == 1) {
        float **ptr = copy2DArrayToPointer(example1,4,5);
        this->setArray(ptr, 4,5);
    }
    else if(chooice == 2){
        float **ptr = copy2DArrayToPointer(example2,4,5);
        this->setArray(ptr, 4,5);
    }
    else if(chooice == 3){
        float **ptr = copy2DArrayToPointer(example3,4,5);
        this->setArray(ptr, 4,5);
    }
    else if(chooice == 4){
        float **ptr = copy2DArrayToPointer(example4,3,4);
        this->setArray(ptr, 3,4);
    }
    else{
        cout << " wybrano zly numer przykladu";
        exit(0);
    }
}


void  Gauss::loadDataFromUser(){
    int rows, cols;
    cout << " podaj ilosc niewiadomych : " ;
    cin >> cols;
    cout << " podaj ilosc rownan : ";
    cin >> rows;
    float **ar = create2DArray(rows,cols);
    for(int i = 0; i <rows; i++){
        cout << " rownanie " << i + 1 << " \n";
        for(int j = 0; j <cols; j++){
            if(j<cols -1) cout << "x" << j +1 << "  = ";
            else cout << "wyraz wolny = ";
            cin >> ar[i][j];

            }
    }
    this->setArray(ar,rows,cols);
}

void Gauss::pickMethod(){

    int choice = 0,temp = 0;
    cout << " \n1.Podstawowa elimacja Gaussa\n2.Elminacja z wyborem elementu max w kolumnie\n3.Elminacja z pelnym wyborem elementu max " ;
    cout << endl;
    cin >> choice;

    cout << " czy wystwetlac rozwiazanie krok po kroku ? 1 - tak, 2 - nie ";
    cin >> temp;
    if(temp == 1 ){
        cout << "\nMacierz wspolczynnikow powiekszona o wektor wyrazow wolnych :";
        print2DArray(this->array,this->rows, this->cols);
    }
    else {
        cout.setstate(ios_base::failbit); // 'wylaczenie' cout
    }
    if(choice > 0 && choice < 4){
        defaultElimination(choice);
        cout.clear(); // 'wlaczanie' cout

        if(isEquationSolvable()){
            if(this->areColumnsSwapped){
                createArrayWithOrderOfColumns();
                fixResult(float *result);
            }
            float* result = getResultFromRowEchelonForm();
            for(int i =0 ;i <  this->cols -1;i++){
            cout << result[i] << " ";
       // co z tymi zamienionymi kolumnami ?
            }

        }
    }
    else{
        cout << " wybrano zly numer metody";
        exit(0);
    }




}
float* Gauss::getResultFromRowEchelonForm(){

    int rows = this->rows;
    float **ar = this->array;
    int lastColumn = this->cols -1 ;
    float *result = new float[lastColumn-1];
    float temp = 0;
    rows--;
    result[lastColumn-1] = (ar[rows][lastColumn])/(ar[rows][rows]);
    cout << "x"<<rows+1<< "=" << result[rows]<< "\t" ;
    for(int i = rows -1 ;i >= 0 ; i--){ // start od przedostatniego wiersza
        temp = 0 ;
        for(int j = i + 1 ; j <= rows ; j++){
            temp -= result[j]*ar[i][j];
        }
        temp += ar[i][lastColumn];
        result[i]  = temp / (ar[i][i]);
        cout << "x"<<i+1<< "=" <<result[i] <<  "\t" ;

    }
    return result;
}

void Gauss::createArrayWithOrderOfColumns(){
    for(int i = 0; i < this->cols - 1;i++ ){
            this->orderOfColumns[i] = i;
            }
}

float* Gauss::arrayWithCoefficients(int step){
    int rows = this->rows;
    int startingRow = step;
    float *coef = new float[rows];
    for(int i = startingRow , j = step - 1; i < rows; i++){
        coef[i] = (this->array[i][j])/(this->array[j][j]);
        if(coef[i]) cout << " wspolczynnik dla wiersza nr " << i + 1 << " = " << coef[i] << endl;
        startingRow++;
    }

    return coef;
}
void Gauss::fixResult(float *result){
    for(int i =0;i < this->cols -1 ; i++){
        if( result[i] != i){
            swap(result[i])
        }
    }
}

void Gauss::defaultElimination(int typeOfElimination){
    int step = 1;
    int rows = this->rows;
    int cols = this->cols;
    float *coefficients ;

    if(isElementEqualZero(0,0)){
        swapRowsEveryPossibleWay();
    }

    while(step < rows){

        if(isElementEqualZero(step,step)){
            swapWithRowsUnderCurrentRow(step);
        }
        cout << endl << string(100,'-') << " \n\tkrok " << step << endl <<  string(100,'-') <<  endl;
        if(typeOfElimination == 3){     // elimanacja z pelnym wyborem elementu max
             findMaxElementAndSwapItToTheDiagonal(this->array ,step - 1);
        }
        else if(typeOfElimination == 2){    // elimanacja z wyborem elementu max w kolumnie
            //metoda srednia
        }
        coefficients = arrayWithCoefficients(step);
        for(int i = step ; i < rows ; i++){
            for(int j = step-1; j < cols ;j++){
                if(coefficients[i]){
                    this->array[i][j] -= (coefficients[i]*this->array[step-1][j]);
                }
                else{
                    cout << " wspolczynnik dla wiersza nr " << i + 1 << " = 0, wartosci w tym wierszu nie zmienia sie ";
                    j = cols -1;
                }
            }
        }
        cout << "\nmacierz po obliczeniu nowych wartosci : ";
        print2DArray(this->array,rows,cols);
        step++;
    }
}


void Gauss::findMaxElementAndSwapItToTheDiagonal(float **ar, int start){
    float max = fabs(ar[start][start]);
    int row = 0;
    int column = 0 ;


    for(int i = start; i < this->rows ; i++){
        for(int j = start; j < this->cols - 1; j++){
            if(fabs(ar[i][j]) >= max){
                max = fabs(ar[i][j]);
                row = i;
                column = j;
            }
        }
    }
    cout << "\nmaksymalny element co do wartosci bezwglednej to : " << max
        << " znajduje sie on na pozycji " << "[" << row +1 << "]"<< " [" << column +1<< "]";
    if(start != row ) {
        swapRows(ar,this->cols,start,row);

        cout << "\n zamiana wiersza " << start +1<< " z wierszem " << row + 1;
        print2DArray(this->array, this->rows, this->cols);
    }
    else cout << "\n element znajduje sie w odpowiednim wierszu";
    if(start != column ){
        swapColumns(ar,this->rows,start,column);
        cout << "\n zamiana kolumny "<< start + 1 <<" z kolumna " << column + 1 ;

        print2DArray(this->array, this->rows, this->cols);
        this->areColumnsSwapped = true;
        //odnotowac zamiane kolumn i zamienic po ustaleniu x'ow
    }
    else cout << "\n element znajduje sie w odpowiedniej kolumnie\n";
}

void Gauss::swapWithRowsUnderCurrentRow(int step){
    cout << "\n elemnt na przekatnej = 0, zamiana wierszy  ";
    int temp = step + 1;
    while(temp < this->rows || isElementEqualZero(step,step)){
        swapRows(this->array,this->cols, step, temp );
        print2DArray(this->array,this->rows,this->cols);
        temp++;
    }
    if(isElementEqualZero(step,step)){
        cout.clear(); // 'wlaczanie' cout
        cout << "element na przekatnej = 0 w kazdym ukladzie wierszy, dana metoda gaussa nie moze byc kontynuowana";
        exit(3);
        }

}
float* Gauss::fixResult(float *result){
    for(int i =0;i < this->cols-1 ; i++){
        if( this->orderOfColumns[i] !=i ){
            temp = order[i];
            swap(result[temp], result[i]);
            swap(this->orderOfColumns[temp], this->orderOfColumns[i]);
            i = 0;
        }
    }
    return result;
}
void Gauss::swapRowsEveryPossibleWay(){
    int temp = 1;
    while(isElementEqualZero(0,0)){
        if(temp == rows){
            cout << "ukladu ma nieskonczenie wiele rozwiazan";
            exit(15);
        }
        swapRows(this->array, this->cols, 0, temp);
        cout << "\n pierwszy element = 0, zamiana wierszy ";
        print2DArray(this->array,this->rows,this->cols);
        temp++;
    }

}


void Gauss::setArray(float ** ar, int r, int c){
        this->array = ar;
        this->rows = r;
        this->cols = c;
    }

bool Gauss::isEquationSolvable(){
    cout.clear(); // 'wlaczanie' cout
    int lastColumn = this->cols - 1;
    int lastRow = this->rows - 1;
    if(isElementEqualZero(lastRow,lastColumn - 1) && isElementEqualZero(lastRow,lastColumn) ){
        cout << "Uklad rownan ma nieskonczenie wiele rozwiazan ";
        return false;
    }
    else if(isElementEqualZero(lastRow,lastColumn - 1) && !isElementEqualZero(lastRow,lastColumn)){
        cout << "Uklad sprzeczny - nie ma zadnego rozwiazania ";
        return false;
    }
    return true;

}

bool Gauss::isElementEqualZero(int i, int j){
    return  fabs(this->array[i][j]) <= this->numberCloseToZero;
}

#include <iostream>
#include <math.h>
#include "array.h"
using namespace std;


class Gauss{

private :
    float numberCloseToZero = 1e-5;
    float **array = nullptr;
    float *orderOfColumns = nullptr;
    int rows;
    int cols;
    bool areColumnsSwapped = false;

    void pickInput();
    int pickMethod();
    void getPrepared2DArray();
    void setArray(float ** ar, int r, int c);
    void loadDataFromUser();

    float* arrayWithCoefficients(int step);
    float* getResultFromRowEchelonForm();  // macierz schodkowa
    void createArrayWithOrderOfColumns();
    float* fixResult(float *result);
    void printResultAndDeleteArray(float *result);
    void findMaxValueInColumnAndSwapItToTheDiagonal(int start);
    void findMaxElementAndSwapItToTheDiagonal(int start);
    void swapWithRowsUnderCurrentRow(int step);
    void swapRowsEveryPossibleWay();
    bool isElementEqualZero(int i, int j);
    bool isEquationSolvable();
    bool isEmpty(float *ar);

public :
    ~Gauss();
    int menu();
    void elimination(int typeOfElimantion);
    void finalResults();
};


int main(){
    int numberOfMethod = 1;
    while(numberOfMethod != 0 ){
        Gauss gauss;
        numberOfMethod = gauss.menu();
        gauss.elimination(numberOfMethod);
        gauss.finalResults();
    }
    return 0;
}


int Gauss::menu(){
    pickInput();
    int choice = pickMethod();
    return choice;
}

void Gauss::pickInput(){
    int choice = 0;
    cout << "\n1.Gotowy zbior danych\n2.Wprowadzanie danych z klawiatury\n0.wyjscie z programu" << endl;
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
        case 0 :{
            exit(0);
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
    float example4[3][4] = { {0,2,-1,0},{1,0,-2,4},{10,0,3,0}};

    int choice;
    cout << "\nPrzyklad 1 : wynik poprawny   x1=-1 x2=-1 x3=1 x4=-1" ;
    print2DArray(example1, 4, 5);
    cout << "\nPrzyklad 2 : wynik poprawny   x1=0 x2=-1 x3=-2 x4=0";
    print2DArray(example2, 4, 5);
    cout << "\nPrzyklad 3 : wynik poprawny  x1=-1 x2=-1 x3=1 x4=1";
    print2DArray(example3, 4, 5);
    cout << "\nPrzyklad 4 : wynik poprawny  x1=0.5217 x2=-0.8696 x3=-1.739";
    print2DArray(example4, 3, 4);
    cout <<"\n wybierz przyklad : ";
    cin >> choice;
    if(choice == 1) {
        float **ptr = copy2DArrayToPointer(example1,4,5);
        this->setArray(ptr, 4,5);
    }
    else if(choice == 2){
        float **ptr = copy2DArrayToPointer(example2,4,5);
        this->setArray(ptr, 4,5);
    }
    else if(choice == 3){
        float **ptr = copy2DArrayToPointer(example3,4,5);
        this->setArray(ptr, 4,5);
    }
    else if(choice == 4){
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
    cols++;
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

int Gauss::pickMethod(){

    int choice = 0,temp = 0;
    cout << " \n1.Podstawowa elimacja Gaussa\n2.Elminacja z wyborem elementu max w kolumnie\n3.Elminacja z pelnym wyborem elementu max " ;
    cout << endl;
    cin >> choice;
    if(choice <= 0 || choice >= 4){
        cout << " wybrano zly numer metody";
        exit(0);
    }

    cout << " czy wystwetlac rozwiazanie krok po kroku ? 1 - tak, 2 - nie ";
    cin >> temp;
    if(temp == 1 ){
        cout << "\nMacierz wspolczynnikow powiekszona o wektor wyrazow wolnych :";
        print2DArray(this->array,this->rows, this->cols);
    }
    else {
        cout.setstate(ios_base::failbit); // 'wylaczenie' cout
    }
    return choice;
}

void Gauss::finalResults(){
    cout.clear(); // 'wlaczanie' cout
    if(isEquationSolvable()){
        float* result = getResultFromRowEchelonForm();
        if(!isEmpty(this->orderOfColumns)){
            float* finalResult = fixResult(result);
            result = finalResult;
        }
        printResultAndDeleteArray(result);
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
    for(int i = rows -1 ;i >= 0 ; i--){ // start od przedostatniego wiersza
        temp = 0 ;
        for(int j = i + 1 ; j <= rows ; j++){
            temp -= result[j]*ar[i][j];
        }
        temp += ar[i][lastColumn];
        result[i]  = temp / (ar[i][i]);
    }
    return result;
}

void Gauss::createArrayWithOrderOfColumns(){
    this->orderOfColumns = new float[ this->cols - 1];
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
        if(coef[i]) cout << "wspolczynnik dla wiersza nr " << i + 1 << " = " << coef[i] << endl;
        startingRow++;
    }
    return coef;
}


void Gauss::elimination(int typeOfElimination){
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
             findMaxElementAndSwapItToTheDiagonal(step - 1);
        }
        else if(typeOfElimination == 2){    // elimanacja z wyborem elementu max w kolumnie
            findMaxValueInColumnAndSwapItToTheDiagonal(step -1);
        }
        coefficients = arrayWithCoefficients(step);
        for(int i = step ; i < rows ; i++){
            for(int j = step-1; j < cols ;j++){
                if(coefficients[i]){
                    this->array[i][j] -= (coefficients[i]*this->array[step-1][j]);
                }
                else{
                    cout << "wspolczynnik dla wiersza nr " << i + 1 << " = 0, wartosci w tym wierszu nie zmienia sie\n";
                    j = cols -1;
                }
            }
        }
        cout << "\nmacierz po obliczeniu nowych wartosci : ";
        print2DArray(this->array,rows,cols);
        step++;
    }
    delete [] coefficients;
}


void Gauss::findMaxValueInColumnAndSwapItToTheDiagonal(int start){
    float **ar = this->array;
    float max = fabs(ar[start][start]);
    int row = 0 ;
    for(int i = start; i < this->rows; i++){
            if(fabs(ar[i][start]) >= max){
                max = fabs(ar[i][start]);
                row = i;
            }
    }
    cout << "\nmaksymalny element dla danego kroku co do wartosci bezwglednej to : " << max
        << " znajduje sie on na pozycji " << "[" << row +1 << "]";

    if(start != row ) {
        swapRows(ar,this->cols,start,row);
        cout << "\n macierz po zamianie wiersza " << start +1<< " z wierszem " << row + 1;
        print2DArray(this->array, this->rows, this->cols);

    }
    else cout << "\n element juz znajduje sie w odpowiednim wierszu";
    cout << endl;
}

void Gauss::findMaxElementAndSwapItToTheDiagonal(int start){
    float **ar = this->array;
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
    cout << "\nmaksymalny element dla danego kroku co do wartosci bezwglednej to : " << max
        << " znajduje sie on na pozycji " << "[" << row +1 << "]"<< " [" << column +1<< "]";

    if(start != row ) {
        swapRows(ar,this->cols,start,row);
        cout << "\n macierz po zamianie wiersza " << start +1<< " z wierszem " << row + 1;
        print2DArray(this->array, this->rows, this->cols);
    }
    else cout << "\n element znajduje sie juz w odpowiednim wierszu";

    if(start != column ){
        swapColumns(ar,this->rows,start,column);
        cout << "\n macierz po zamianie kolumny "<< start + 1 <<" z kolumna " << column + 1 ;
        print2DArray(this->array, this->rows, this->cols);

        if(this->orderOfColumns == nullptr){
            createArrayWithOrderOfColumns();
        }
        swap(this->orderOfColumns[start],this->orderOfColumns[column]);

    }
    else cout << "\n element znajduje sie juz w odpowiedniej kolumnie";
    cout << endl;
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
    int temp = -1;
    for(int i =0;i < this->cols-1 ; i++){
        if( this->orderOfColumns[i] !=i ){
            temp = this->orderOfColumns[i];
            swap(result[temp], result[i]);
            swap(this->orderOfColumns[temp], this->orderOfColumns[i]);
            i = 0;
        }
    }
    return result;
}
void Gauss::printResultAndDeleteArray(float *result){
    cout << endl << " Koniec eliminacji Gaussa, uklad ma dokladnie jedno rozwiazanie :\n";
    for(int i =0 ;i < this->cols - 1;i++){
        cout << " x" << i+1 << "=" << result[i];
    }
    delete [] result;


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
Gauss::~Gauss(){
    delete2Darray(this->array, this->rows);
    if(!isEmpty(orderOfColumns)) delete [] orderOfColumns;
    this->array = nullptr;
    this->orderOfColumns = nullptr;
    }

bool Gauss::isElementEqualZero(int i, int j){
    return  fabs(this->array[i][j]) <= this->numberCloseToZero;
}
bool Gauss::isEmpty(float *ar){
    return ar == nullptr ? true : false;
}

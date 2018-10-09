#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

struct matrix
{
  int** data;
  int row, col;
};

void createMatrix  ( int row , int col , int num[] , matrix& mat );
void createMatrix  ( int row , int col , int val   , matrix& mat );
void createMatrix  ( int row , int col , matrix& mat );
void releaseMemory ( vector < matrix > sm );

matrix operator+ ( matrix mat1 , matrix mat2 );
matrix operator- ( matrix mat1 , matrix mat2 );
matrix operator* ( matrix mat1 , matrix mat2 );
matrix operator+ ( matrix mat1 , int value );
matrix operator- ( matrix mat1 , int value );
matrix operator* ( matrix mat1 , int value );

matrix operator+= ( matrix& mat1, matrix mat2 );
matrix operator-= ( matrix& mat1, matrix mat2 );
matrix operator+= ( matrix& mat1, int value );
matrix operator-= ( matrix& mat1, int value );

matrix operator++ ( matrix& mat );
matrix operator-- ( matrix& mat );

bool operator== ( matrix mat1 , matrix mat2 );
bool operator!= ( matrix mat1 , matrix mat2 );

istream& operator>> ( istream& in , matrix& mat );
ostream& operator<< ( ostream& out , matrix mat );

bool   isSquare   ( matrix mat );
bool   isSymetric ( matrix mat );
bool   isIdentity ( matrix mat );
matrix transpose  ( matrix mat );

vector < matrix > selected_memory;

const int setwValue = 4;

int main()
{
    //freopen( "input.c"    , "r" , stdin  );
    //freopen( "output.txt" , "w" , stdout );
    cout << fixed;

    int data1 [] = { 1  , 2   , 3  , 4   , 5  , 6   , 7  , 8   };
    int data2 [] = { 13 , 233 , 3  , 4   , 5  , 6 };
    int data3 [] = { 10 , 100 , 10 , 100 , 10 , 100 , 10 , 100 };

    matrix mat1, mat2, mat3;
    createMatrix ( 4 , 2 , data1 , mat1 );
    createMatrix ( 2 , 3 , data2 , mat2 );
    createMatrix ( 4 , 2 , data3 , mat3 );


    /*cout << mat1 << endl << mat2 << endl << mat3 << endl;

    cout << mat1 + mat3 << endl;
    cout << mat3 + mat3 << endl;

    ++mat1;
    cout << mat1 << endl;

    mat1 += mat3 += mat3;
    cout << mat1 << endl << mat3 << endl;
    */

    // multiplication
    matrix mat4 , mat5 , mat6;
    createMatrix( 3 , 2 , mat4 );
    createMatrix( 2 , 3 , mat5 );
    createMatrix( 3 , 3 , mat6 );

    cin >> mat4 >> mat5;
    mat6 = mat4 * mat5;

    cout << mat6 << endl;

    releaseMemory( selected_memory );

    return 0;
}

void createMatrix  (int row, int col, int num[], matrix& mat)
{
    mat.row = row;
    mat.col = col;

    mat.data = new int* [row];
    for ( int i = 0; i < row; i++ ) mat.data[ i ] = new int [col];

    int index = 0;
    for ( int i = 0; i < row; i++ )
    {
        for ( int j = 0; j < col; j++ ) mat.data[i][j] = num[ index++ ];
    }

    selected_memory.push_back( mat );
}

void createMatrix  (int row, int col, int val  , matrix& mat)
{
    mat.row = row;
    mat.col = col;

    mat.data = new int* [row];
    for ( int i = 0; i < row; i++ ) mat.data[ i ] = new int [col];

    for ( int i = 0; i < row; i++ )
    {
        for ( int j = 0; j < col; j++ ) mat.data[i][j] = val;
    }

    selected_memory.push_back( mat );
}
void createMatrix  (int row, int col, matrix& mat)
{
    mat.row = row;
    mat.col = col;

    mat.data = new int* [row];
    for ( int i = 0; i < row; i++ ) mat.data[ i ] = new int [col];

    selected_memory.push_back( mat );
}

matrix operator+ ( matrix mat1 , matrix mat2 )
{
    matrix mat3;
    createMatrix( mat1.row , mat1.col , mat3 );

    for ( int i = 0; i < mat3.row; i++ )
        for ( int j = 0; j < mat3.col; j++ ) mat3.data[i][j] = mat1.data[i][j] + mat2.data[i][j];

    return mat3;
}

matrix operator- ( matrix mat1 , matrix mat2 )
{
    matrix mat3;
    createMatrix( mat1.row , mat1.col , mat3 );

    for ( int i = 0; i < mat3.row; i++ )
        for ( int j = 0; j < mat3.col; j++ ) mat3.data[i][j] = mat1.data[i][j] - mat2.data[i][j];

    return mat3;
}

matrix operator* ( matrix mat1 , matrix mat2 )
{
    int val = 0 , mul = 1;

    matrix res;
    createMatrix ( mat1.row , mat2.col , res );

    for ( int i = 0; i < mat1.row; i++ )
    {
        for ( int rep = 0; rep < mat2.col; rep++ )
        {
            val = 0;
            for ( int j = 0; j < mat1.col; j++ ) mul = mat1.data[i][j] * mat2.data[j][rep] , val += mul;
            res.data[ i ][ rep ] = val;
        }
    }

    return res;
}

matrix operator+ ( matrix mat1 , int value )
{
    matrix mat3;
    createMatrix( mat1.row , mat1.col , mat3 );

    for ( int i = 0; i < mat3.row; i++ )
        for ( int j = 0; j < mat3.col; j++ ) mat3.data[i][j] = mat1.data[i][j] + value;

    return mat3;
}

matrix operator- ( matrix mat1 , int value )
{
    matrix mat3;
    createMatrix( mat1.row , mat1.col , mat3 );

    for ( int i = 0; i < mat3.row; i++ )
        for ( int j = 0; j < mat3.col; j++ ) mat3.data[i][j] = mat1.data[i][j] - value;

    return mat3;
}

matrix operator* ( matrix mat1 , int value )
{
    matrix mat3;
    createMatrix( mat1.row , mat1.col , mat3 );

    for ( int i = 0; i < mat3.row; i++ )
        for ( int j = 0; j < mat3.col; j++ ) mat3.data[i][j] = mat1.data[i][j] * value;

    return mat3;
}

matrix operator+= ( matrix& mat1, matrix mat2 )
{
    for ( int i = 0; i < mat1.row; i++ )
        for ( int j = 0; j < mat1.col; j++ ) mat1.data[i][j] += mat2.data[i][j];

    return mat1;
}
matrix operator-= ( matrix& mat1, matrix mat2 )
{
    for ( int i = 0; i < mat1.row; i++ )
        for ( int j = 0; j < mat1.col; j++ ) mat1.data[i][j] -= mat2.data[i][j];

    return mat1;
}
matrix operator+= ( matrix& mat1, int value )
{
    for ( int i = 0; i < mat1.row; i++ )
        for ( int j = 0; j < mat1.col; j++ ) mat1.data[i][j] += value;

    return mat1;
}
matrix operator-= ( matrix& mat1, int value )
{
    for ( int i = 0; i < mat1.row; i++ )
        for ( int j = 0; j < mat1.col; j++ ) mat1.data[i][j] -= value;

    return mat1;
}

matrix operator++ ( matrix& mat )
{
    for ( int i = 0; i < mat.row; i++ )
        for ( int j = 0; j < mat.col; j++ ) mat.data[i][j]++;

    return mat;
}

matrix operator-- ( matrix& mat )
{
    for ( int i = 0; i < mat.row; i++ )
        for ( int j = 0; j < mat.col; j++ ) mat.data[i][j]--;

    return mat;
}

bool operator== ( matrix mat1 , matrix mat2 )
{
    bool output = 1;

    for ( int i = 0; i < mat1.row; i++ )
        for ( int j = 0; j < mat1.col; j++ ) ( mat1.data[i][j] != mat2.data[i][j] ) ?  output = 0 : 0;

    return output;
}
bool operator!= ( matrix mat1 , matrix mat2 )
{
    bool output = 1;

    for ( int i = 0; i < mat1.row; i++ )
        for ( int j = 0; j < mat1.col; j++ ) ( mat1.data[i][j] == mat2.data[i][j] ) ? output = 0 : 0;

    return output;
}

istream& operator>> ( istream& in , matrix& mat )
{
    for ( int i = 0; i < mat.row; i++ )
        for ( int j = 0; j < mat.col; j++ ) in >> mat.data[i][j];
    return in;
}

ostream& operator<< ( ostream& out , matrix mat )
{
    out << setw( setwValue );
    for ( int i = 0; i < mat.row; i++ )
    {
        for ( int j = 0; j < mat.col; j++ ) out << mat.data[i][j] << setw( setwValue );
        out << endl;
    }
    return out;
}

bool   isSquare   ( matrix mat )
{
    return ( mat.row == mat.col );
}
bool   isSymetric ( matrix mat )
{
    bool res = 1;
    for ( int i = 0 , j = mat.row - 1; i < mat.row; i++,j-- )
    {
        for ( int ii = 0 , jj = mat.col-1; ii < mat.col; ii++,jj-- )
        {
            if ( i != ii && j != jj && ( mat.data[i][ii] != mat.data[ii][i] || mat.data[j][jj] != mat.data[jj][j] ) )
            {
                res = 0;
            }
        }
    }
    return res;
}
bool   isIdentity ( matrix mat )
{
    bool res = 1;
    for ( int i = 0; i < mat.row; i++ )
    {
        for ( int j = 0; j < mat.col; j++ )
        {
            if ( i == j && mat.data[i][j] != 1 ) res = 0;
            if ( i != j && mat.data[i][j] != 0 ) res = 0;
        }
    }
    return res;
}
matrix transpose  ( matrix mat )
{
    matrix trans; createMatrix( mat.row , mat.col , trans );

    for ( int i = 0; i < trans.row; i++ )
        for ( int j = 0; j < trans.col; j++ ) trans.data[j][i] = mat.data[i][j];

    return trans;
}

void releaseMemory ( vector < matrix > sm )
{
    for ( int i = 0; i < sm.size(); i++ )
    {
        for ( int row = 0; row < sm[i].row; row++ ) delete[] sm[i].data[row];
        delete[] sm[i].data;
    }
}



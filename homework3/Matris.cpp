#include <iostream>
using namespace std;

void printMat(int mat[4][4]) {
    // چاپ ماتریس
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
}

void sumMat(int matA[4][4], int matB[4][4]) {
    int sumMat[4][4] = { {0,0,0,0}, {0,0,0,0}, {0,0,0,0} , {0,0,0,0} };
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            sumMat[i][j] = matA[i][j] + matB[i][j];
        }
    }
    printMat(sumMat);
}

void subMat(int matA[4][4], int matB[4][4]) {
    int subMat[4][4] = { {0,0,0,0}, {0,0,0,0}, {0,0,0,0} , {0,0,0,0} };
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            subMat[i][j] = matA[i][j] - matB[i][j];
        }
    }
    printMat(subMat);
}

void mulMat(int matA[4][4], int matB[4][4]) {
    int mulMat[4][4] = { {0,0,0,0}, {0,0,0,0}, {0,0,0,0} , {0,0,0,0} };
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            mulMat[i][j] = 0;
            for (int k = 0; k < 4; k++) {
                mulMat[i][j] += (matA[i][k] * matB[k][j]);
            }
        }
    }
    printMat(mulMat);
}

void taranahade(int matA[4][4]) {
    int tMat[4][4] = { {0,0,0,0}, {0,0,0,0}, {0,0,0,0} , {0,0,0,0} };
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            tMat[i][j] = matA[j][i];
        }
    }
    printMat(tMat);

}

int determinan(int matA[4][4]) {
    int det = 0;
    for (int i = 0; i < 4; i++) {
        det += (matA[0][i] * (matA[1][(i + 1) % 3] * matA[2][(i + 2) % 3] - matA[1][(i + 2) % 3] * matA[2][(i + 1) % 3]));
    }
    return det;
}

int main() {
    int matrixA[4][4] = { {7, 6, 5 , 9}, {8, 2 , 5 , 5}, {6 , 6 , 9 , 1} , {4 , 0 , 8 ,3} };
    int matrixB[4][4] = { {8, 5, 65 , 2}, {2, 6 , 4 , 4}, {5 , 8 , 4 , 5} , {9 , 9 , 4 ,5} };

    //چاپ کردن دو ماتریس
    cout << "matris A : " << endl;
    printMat(matrixA);

    cout << "matris B: " << endl;
    printMat(matrixB);

    // جمع دو ماتریس
    cout << "sum : " << endl;
    sumMat(matrixA, matrixB);

    // منهای دو ماتریس
    cout << "minus : " << endl;
    subMat(matrixA, matrixB);

   

    // دترمینان مارتیس
    cout << "determinan :  " << endl;
    cout << determinan(matrixA) << endl;

    // ترانهاده ی ماتریس
    cout << " taranahadeh :  " << endl;
    taranahade(matrixA);

    // ضرب دو ماتریس
    cout << "multiplication : " << endl;
    mulMat(matrixA, matrixB);

    return 0;
}


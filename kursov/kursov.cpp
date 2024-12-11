#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

// Тип для представления матрицы
typedef vector<vector<int>> Matrix;

// Переменные для локализации
string msgEnterMatrixSize = "Введите размер матриц: ";
string msgInputMatrix = "Ввод матрицы ";
string msgMatrixSaved = "Матрица сохранена в файл ";
string msgMatrixLoaded = "Матрица загружена из файла ";
string msgFileError = "Ошибка открытия файла ";
string msgEditElement = "Введите номер строки и столбца для редактирования (начиная с 0): ";
string msgEnterNewValue = "Введите новое значение: ";
string msgInvalidIndices = "Некорректные индексы.";
string msgMatrixResult = "Матрица C (результат):";

// Функция для создания квадратной матрицы заданного размера
Matrix createMatrix(int size) {
    return Matrix(size, vector<int>(size, 0));
}

// Функция для ввода матрицы с консоли
void inputMatrix(Matrix& matrix, const string& matrixName) {
    int size = matrix.size();
    cout << msgInputMatrix << matrixName << ":" << endl;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            cin >> matrix[i][j];
        }
    }
}

// Функция для вывода матрицы на консоль
void printMatrix(const Matrix& matrix) {
    for (const auto& row : matrix) {
        for (const auto& elem : row) {
            cout << setw(5) << elem;
        }
        cout << endl;
    }
}

// Функция для записи матрицы в файл
void saveMatrixToFile(const Matrix& matrix, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (const auto& row : matrix) {
            for (const auto& elem : row) {
                file << elem << " ";
            }
            file << endl;
        }
        file.close();
        cout << msgMatrixSaved << filename << endl;
    }
    else {
        cerr << msgFileError << filename << endl;
    }
}

// Функция для чтения матрицы из файла
void loadMatrixFromFile(Matrix& matrix, const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        for (auto& row : matrix) {
            for (auto& elem : row) {
                file >> elem;
            }
        }
        file.close();
        cout << msgMatrixLoaded << filename << endl;
    }
    else {
        cerr << msgFileError << filename << endl;
    }
}

// Функция для редактирования элемента матрицы
void editMatrixElement(Matrix& matrix) {
    int i, j, value;
    cout << msgEditElement;
    cin >> i >> j;
    if (i >= 0 && i < matrix.size() && j >= 0 && j < matrix.size()) {
        cout << msgEnterNewValue;
        cin >> value;
        matrix[i][j] = value;
    }
    else {
        cout << msgInvalidIndices << endl;
    }
}

// Функция для записи в матрицу C строк матрицы A, совпадающих с любым столбцом матрицы B
void fillMatrixC(const Matrix& A, const Matrix& B, Matrix& C) {
    int size = A.size();
    for (int i = 0; i < size; ++i) {
        bool matchFound = false;
        for (int j = 0; j < size; ++j) {
            bool isMatch = true;
            for (int k = 0; k < size; ++k) {
                if (A[i][k] != B[k][j]) {
                    isMatch = false;
                    break;
                }
            }
            if (isMatch) {
                matchFound = true;
                break;
            }
        }
        if (matchFound) {
            C[i] = A[i];
        }
        else {
            C[i] = vector<int>(size, 0);
        }
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    int size;
    cout << msgEnterMatrixSize;
    cin >> size;

    Matrix A = createMatrix(size);
    Matrix B = createMatrix(size);
    Matrix C = createMatrix(size);

    inputMatrix(A, "A");
    inputMatrix(B, "B");

    fillMatrixC(A, B, C);

    cout << "Матрица A:" << endl;
    printMatrix(A);

    cout << "Матрица B:" << endl;
    printMatrix(B);

    cout << msgMatrixResult << endl;
    printMatrix(C);

    return 0;
}

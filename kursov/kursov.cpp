#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>

using namespace std;

class Matrix {
public:
    int size;  // Размерность матрицы
    int** data;  // Данные матрицы

    // Конструктор для создания матрицы заданного размера
    Matrix(int n) : size(n) {
        data = new int* [size];
        for (int i = 0; i < size; ++i) {
            data[i] = new int[size];
        }
    }

    // Деструктор для освобождения памяти
    ~Matrix() {
        for (int i = 0; i < size; ++i) {
            delete[] data[i];
        }
        delete[] data;
    }

    // Функция для ввода данных из консоли
    void input() {
        cout << "Введите элементы матрицы (" << size << "x" << size << "):\n";
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                cin >> data[i][j];
            }
        }
    }

    // Функция для вывода матрицы в консоль
    void output() const {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                cout << data[i][j] << " ";
            }
            cout << endl;
        }
    }

    // Функция для записи матрицы в файл
    void saveToFile(const string& filename) const {
        ofstream out(filename);
        if (!out) {
            cout << "Ошибка при открытии файла для записи.\n";
            return;
        }
        out << size << endl;
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                out << data[i][j] << " ";
            }
            out << endl;
        }
        out.close();
    }

    // Функция для чтения матрицы из файла
    void loadFromFile(const string& filename) {
        ifstream in(filename);
        if (!in) {
            cout << "Ошибка при открытии файла для чтения.\n";
            return;
        }
        in >> size;
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                in >> data[i][j];
            }
        }
        in.close();
    }

    // Функция для редактирования элемента матрицы
    void editElement() {
        int row, col, value;
        cout << "Введите номер строки и столбца для редактирования (1-" << size << "): ";
        cin >> row >> col;
        cout << "Введите новое значение: ";
        cin >> value;
        data[row - 1][col - 1] = value;
    }

    // Функция для проверки совпадения строки с столбцом
    bool compareRowWithColumn(int row, int col) const {
        for (int i = 0; i < size; ++i) {
            if (data[row][i] != data[i][col]) {
                return false;
            }
        }
        return true;
    }

    // Функция для записи строк из A в C, если они совпадают с каким-либо столбцом B
    void processMatrix(const Matrix& B, Matrix& C) {
        for (int i = 0; i < size; ++i) {
            bool matchFound = false;
            for (int j = 0; j < size; ++j) {
                if (compareRowWithColumn(i, j)) {
                    matchFound = true;
                    break;
                }
            }
            for (int j = 0; j < size; ++j) {
                C.data[i][j] = matchFound ? data[i][j] : 0;
            }
        }
    }
};

// Функция для отображения главного меню
void showMenu() {
    cout << "\nГлавное меню:\n";
    cout << "1. Ввод данных для матрицы\n";
    cout << "2. Вывод данных матриц\n";
    cout << "3. Сохранить матрицу в файл\n";
    cout << "4. Загрузить матрицу из файла\n";
    cout << "5. Редактировать элемент матрицы\n";
    cout << "6. Обработать матрицы A и B, записать результат в C\n";
    cout << "0. Выход\n";
}

// Главная функция
int main() {
    setlocale(LC_ALL, "Russian");

    int size;
    cout << "Введите размерность матрицы: ";
    cin >> size;

    // Создаем три матрицы A, B и C
    Matrix A(size), B(size), C(size);

    int choice;
    while (true) {
        showMenu();
        cout << "Ваш выбор: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Выберите матрицу для ввода данных:\n";
            cout << "1. Матрица A\n";
            cout << "2. Матрица B\n";
            cout << "3. Матрица C\n";
            int matChoice;
            cin >> matChoice;
            if (matChoice == 1) A.input();
            else if (matChoice == 2) B.input();
            else if (matChoice == 3) C.input();
            break;

        case 2:
            cout << "Матрица A:\n";
            A.output();
            cout << "Матрица B:\n";
            B.output();
            cout << "Матрица C:\n";
            C.output();
            break;

        case 3:
            cout << "Выберите матрицу для сохранения:\n";
            cout << "1. Матрица A\n";
            cout << "2. Матрица B\n";
            cout << "3. Матрица C\n";
            cin >> matChoice;
            {
                string filename;
                cout << "Введите имя файла: ";
                cin >> filename;
                if (matChoice == 1) A.saveToFile(filename);
                else if (matChoice == 2) B.saveToFile(filename);
                else if (matChoice == 3) C.saveToFile(filename);
            }
            break;

        case 4:
            cout << "Выберите матрицу для загрузки:\n";
            cout << "1. Матрица A\n";
            cout << "2. Матрица B\n";
            cout << "3. Матрица C\n";
            cin >> matChoice;
            {
                string filename;
                cout << "Введите имя файла: ";
                cin >> filename;
                if (matChoice == 1) A.loadFromFile(filename);
                else if (matChoice == 2) B.loadFromFile(filename);
                else if (matChoice == 3) C.loadFromFile(filename);
            }
            break;

        case 5:
            cout << "Выберите матрицу для редактирования:\n";
            cout << "1. Матрица A\n";
            cout << "2. Матрица B\n";
            cout << "3. Матрица C\n";
            cin >> matChoice;
            if (matChoice == 1) A.editElement();
            else if (matChoice == 2) B.editElement();
            else if (matChoice == 3) C.editElement();
            break;

        case 6:
            A.processMatrix(B, C);
            cout << "Матрица C после обработки:\n";
            C.output();
            break;

        case 0:
            cout << "Выход из программы.\n";
            return 0;

        default:
            cout << "Неверный выбор. Попробуйте снова.\n";
            break;
        }
    }

    return 0;
}

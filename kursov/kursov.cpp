#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

// Класс для работы с матрицами
class Matrix {
private:
    int size;      // Размер матрицы
    int** data;    // Динамическое хранение матрицы

public:
    // Конструктор
    Matrix(int n) : size(n) {
        data = new int* [size];
        for (int i = 0; i < size; ++i) {
            data[i] = new int[size] {0}; // Инициализация нулями
        }
    }

    // Деструктор
    ~Matrix() {
        for (int i = 0; i < size; ++i) {
            delete[] data[i];
        }
        delete[] data;
    }

    // Получение размера матрицы
    int getSize() const {
        return size;
    }

    // Консольный ввод
    void input() {
        cout << "Введите элементы матрицы (" << size << "x" << size << "):\n";
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                cin >> data[i][j];
            }
        }
    }

    // Консольный вывод
    void output() const {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                cout << setw(5) << data[i][j] << " ";
            }
            cout << endl;
        }
    }

    // Файловый ввод
    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Ошибка открытия файла для чтения.\n";
            return;
        }
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                file >> data[i][j];
            }
        }
        file.close();
        cout << "Данные успешно загружены из файла.\n";
    }

    // Файловый вывод
    void saveToFile(const string& filename) const {
        ofstream file(filename);
        if (!file.is_open()) {
            cout << "Ошибка открытия файла для записи.\n";
            return;
        }
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                file << data[i][j] << " ";
            }
            file << endl;
        }
        file.close();
        cout << "Данные успешно сохранены в файл.\n";
    }

    // Редактирование элемента
    void editElement() {
        int row, col, value;
        cout << "Введите строку и столбец (от 1 до " << size << "): ";
        cin >> row >> col;
        if (row < 1 || row > size || col < 1 || col > size) {
            cout << "Некорректные индексы.\n";
            return;
        }
        cout << "Введите новое значение: ";
        cin >> value;
        data[row - 1][col - 1] = value;
        cout << "Элемент изменён.\n";
    }

    // Проверка, совпадает ли строка i матрицы A со столбцом j матрицы B
    static bool rowMatchesColumn(const Matrix& A, int row, const Matrix& B, int col) {
        for (int k = 0; k < A.size; ++k) {
            if (A.data[row][k] != B.data[k][col]) {
                return false;
            }
        }
        return true;
    }

    // Записать в матрицу C строки из A, совпадающие с любым столбцом из B
    static void processMatrix(const Matrix& A, const Matrix& B, Matrix& C) {
        if (A.size != B.size || A.size != C.size) {
            cout << "Ошибка: размеры матриц не совпадают.\n";
            return;
        }
        for (int i = 0; i < A.size; ++i) {
            bool matchFound = false;
            for (int j = 0; j < B.size; ++j) {
                if (rowMatchesColumn(A, i, B, j)) {
                    matchFound = true;
                    break;
                }
            }
            for (int j = 0; j < C.size; ++j) {
                C.data[i][j] = matchFound ? A.data[i][j] : 0;
            }
        }
    }
};

// Меню программы
void showMenu() {
    cout << "\nМеню:\n";
    cout << "1. Ввод матрицы\n";
    cout << "2. Вывод матрицы\n";
    cout << "3. Редактировать элемент матрицы\n";
    cout << "4. Сохранить матрицу в файл\n";
    cout << "5. Загрузить матрицу из файла\n";
    cout << "6. Обработать матрицы A и B, результат записать в C\n";
    cout << "0. Выход\n";
}

int main() {
    setlocale(LC_ALL, "Russian");

    int size;
    cout << "Введите размер квадратных матриц: ";
    cin >> size;

    // Инициализация матриц
    Matrix A(size), B(size), C(size);

    int choice;
    while (true) {
        showMenu();
        cout << "Выберите пункт меню: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            int mat;
            cout << "Выберите матрицу для ввода (1 - A, 2 - B, 3 - C): ";
            cin >> mat;
            if (mat == 1) A.input();
            else if (mat == 2) B.input();
            else if (mat == 3) C.input();
            else cout << "Неверный выбор.\n";
            break;
        }
        case 2: {
            cout << "Матрица A:\n";
            A.output();
            cout << "Матрица B:\n";
            B.output();
            cout << "Матрица C:\n";
            C.output();
            break;
        }
        case 3: {
            int mat;
            cout << "Выберите матрицу для редактирования (1 - A, 2 - B, 3 - C): ";
            cin >> mat;
            if (mat == 1) A.editElement();
            else if (mat == 2) B.editElement();
            else if (mat == 3) C.editElement();
            else cout << "Неверный выбор.\n";
            break;
        }
        case 4: {
            int mat;
            string filename;
            cout << "Выберите матрицу для сохранения (1 - A, 2 - B, 3 - C): ";
            cin >> mat;
            cout << "Введите имя файла: ";
            cin >> filename;
            if (mat == 1) A.saveToFile(filename);
            else if (mat == 2) B.saveToFile(filename);
            else if (mat == 3) C.saveToFile(filename);
            else cout << "Неверный выбор.\n";
            break;
        }
        case 5: {
            int mat;
            string filename;
            cout << "Выберите матрицу для загрузки (1 - A, 2 - B, 3 - C): ";
            cin >> mat;
            cout << "Введите имя файла: ";
            cin >> filename;
            if (mat == 1) A.loadFromFile(filename);
            else if (mat == 2) B.loadFromFile(filename);
            else if (mat == 3) C.loadFromFile(filename);
            else cout << "Неверный выбор.\n";
            break;
        }
        case 6:
            Matrix::processMatrix(A, B, C);
            cout << "Матрица C после обработки:\n";
            C.output();
            break;

        case 0:
            cout << "Выход из программы.\n";
            return 0;

        default:
            cout << "Неверный пункт меню.\n";
            break;
        }
    }
}

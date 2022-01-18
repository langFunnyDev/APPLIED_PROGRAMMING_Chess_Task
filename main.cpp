#include <Windows.h>
#include <iostream>

int manipulator, x_1, x_2, y_1, y_2, figure, answer2, answer3_x, answer3_y;

int plate [8][8] = {
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
};

int marked_plate [8][8] = {
        {1,0,1,0,1,0,1,0},
        {0,1,0,1,0,1,0,1},
        {1,0,1,0,1,0,1,0},
        {0,1,0,1,0,1,0,1},
        {1,0,1,0,1,0,1,0},
        {0,1,0,1,0,1,0,1},
        {1,0,1,0,1,0,1,0},
        {0,1,0,1,0,1,0,1}
};

/*
 *  Функция error_handler возвращает истину в случае соответствия заданному диапазоне и ложь в обратном
 */

bool error_handler(int number, int minimum, int maximum) {
    if (number >= minimum && number <= maximum) {
        return true;
    } else {
        std::cout << std::endl << "Вы ввели число не соответствующее заданным условиям. Попробуйте ещё раз!" << std::endl << std::endl;
        return false;
    }
}

void user_greeting() {

    do {
        std::cout << "Добро пожаловать в лабораторную работу №8 (№9) !" << std::endl;
        std::cout << "Выберите подзадачу:" << std::endl;
        std::cout << "    1) Выяснить, являются ли поля (k, I) и (m, n) полями одного цвета." << std::endl;
        std::cout << "    2) На поле (к, I) расположен ферзь, ладья, слон или конь. Угрожает ли он полю (m, n)?" << std::endl;
        std::cout << "    3) Выяснить, можно ли с поля (k, I) одним ходом ладьи, ферзя или слона попасть на поле (m, n). " <<
                  "Если нет, то выяснить, как это можно сделать за два хода." << std::endl;
        std::cout << "Для перехода в подзадачу введите число от 1 до 3: ";
        std::cin >> manipulator;
    } while (!error_handler(manipulator, 1, 3));

}

void request_coordinates() {
    std::cout << std::endl;

    do {
        std::cout << "Введите координату X для первой точки (число от 1 до 8): ";
        std::cin >> x_1;
    } while (!error_handler(x_1, 1, 8));

    do {
        std::cout << "Введите координату Y для первой точки (число от 1 до 8): ";
        std::cin >> y_1;
    } while (!error_handler(x_1, 1, 8));

    std::cout << std::endl;

    do {
        std::cout << "Введите координату X для второй точки (число от 1 до 8): ";
        std::cin >> x_2;
    } while (!error_handler(x_2, 1, 8));

    do {
        std::cout << "Введите координату Y для второй точки (число от 1 до 8): ";
        std::cin >> y_2;
    } while (!error_handler(x_2, 1, 8));

    std::cout << std::endl;
}

void request_figure(bool isSecondTask) {

    std::cout << std::endl;

    if(isSecondTask){
        do {
            std::cout << "Введите номер фигуры:" << std::endl;
            std::cout << "    1) Ферзь"  << std::endl;
            std::cout << "    2) Ладья"  << std::endl;
            std::cout << "    3) Слон"  << std::endl;
            std::cout << "    4) Конь"  << std::endl;
            std::cout << "Введите число от 1 до 4: ";
            std::cin >> figure;
        } while (!error_handler(x_1, 1, 4));
    } else {
        do {
            std::cout << "Введите номер фигуры:" << std::endl;
            std::cout << "    1) Ферзь"  << std::endl;
            std::cout << "    2) Ладья"  << std::endl;
            std::cout << "    3) Слон"  << std::endl;
            std::cout << "Введите число от 1 до 3: ";
            std::cin >> figure;
        } while (!error_handler(x_1, 1, 3));
    }

    std::cout << std::endl;

}

void mark_rock(int x, int y) {
    plate[x][y] = 5;
    for (int i = 0; i < x; ++i) {
        plate[i][y] += 1;
    }
    for (int i = 7; i > x; --i) {
        plate[i][y] += 1;
    }
    for (int i = 0; i < y; ++i) {
        plate[x][i] += 1;
    }
    for (int i = 7; i > y; --i) {
        plate[x][i] += 1;
    }
}

void mark_elephant(int x, int y) {
    plate[x][y] = 1;
    for (int i = x, j = y; (i < 8 && j < 8); ++i, ++j) {
        plate[i][j] += 1;
    }
    for (int i = x, j = y; (i >= 0 && j >= 0); --i, --j) {
        plate[i][j] += 1;
    }
    for (int i = x, j = y; (i < 8 && j >= 0); ++i, --j) {
        plate[i][j] += 1;
    }
    for (int i = x, j = y; (i >= 0 && j < 8); --i, ++j) {
        plate[i][j] += 1;
    }
}

void mark_queen(int x, int y) {
    mark_rock(x, y);
    mark_elephant(x, y);
}

void mark_horse(int x, int y) {
    plate[x][y] = 5;

    if ((x + 2 >= 0 && x + 2 < 8) && (y + 1 >= 0 && y + 1 < 8)) plate[x + 2][y + 1] += 1;
    if ((x + 2 >= 0 && x + 2 < 8) && (y - 1 >= 0 && y - 1 < 8)) plate[x + 2][y - 1] += 1;

    if ((x - 2 >= 0 && x - 2 < 8) && (y + 1 >= 0 && y + 1 < 8)) plate[x - 2][y + 1] += 1;
    if ((x - 2 >= 0 && x - 2 < 8) && (y - 1 >= 0 && y - 1 < 8)) plate[x - 2][y - 1] += 1;

    if ((y + 2 >= 0 && y + 2 < 8) && (x + 1 >= 0 && x + 1 < 8)) plate[x + 1][y + 2] += 1;
    if ((y + 2 >= 0 && y + 2 < 8) && (x - 1 >= 0 && x - 1 < 8)) plate[x - 1][y + 2] += 1;

    if ((y - 2 >= 0 && y - 2 < 8) && (x + 1 >= 0 && x + 1 < 8)) plate[x + 1][y - 2] += 1;
    if ((y - 2 >= 0 && y - 2 < 8) && (x - 1 >= 0 && x - 1 < 8)) plate[x - 1][y - 2] += 1;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);

    user_greeting();

    switch (manipulator) {
        case 1:

                request_coordinates();

                if (marked_plate[x_1 - 1][y_1 - 1] == marked_plate[x_2 - 1][y_2 - 1]) {
                   std::cout << "Поля (k, I) и (m, n) - являются полями одного цвета !";
                } else {
                    std::cout << "Поля (k, I) и (m, n) - НЕ являются полями одного цвета !";
                }

            break;
        case 2:
                request_coordinates();

                request_figure(true);

                switch (figure) {
                    case 1:
                        mark_queen(x_1 - 1, y_1 - 1);
                        break;
                    case 2:
                        mark_rock(x_1 - 1, y_1 - 1);
                        break;
                    case 3:
                        mark_elephant(x_1 - 1, y_1 - 1);
                        break;
                    case 4:
                        mark_horse(x_1 - 1, y_1 - 1);
                        break;
                    default:
                        break;
                }

                if(plate[x_2 - 1][y_2 - 1] != 0){
                    std::cout << "Поле (m, n) - находится под ударом !";
                } else {
                    std::cout << "Поле (m, n) - НЕ находится под ударом !";
                }

            break;
        case 3:

            break;
        default:
            break;
    }

    system("pause");
    return 0;
}

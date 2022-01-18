#include <Windows.h>
#include <iostream>

int manipulator, x_1, x_2, y_1, y_2;

int plate [8][8] = {
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
    std::cout << "Добро пожаловать в лабораторную работу №8 (№9) !" << std::endl;
    std::cout << "Выберите подзадачу:" << std::endl;
    std::cout << "    1) Выяснить, являются ли поля (k, I) и (m, n) полями одного цвета." << std::endl;
    std::cout << "    2) На поле (к, I) расположен ферзь, ладья, слон или конь. Угрожает ли он полю (m, n)?" << std::endl;
    std::cout << "    3) Выяснить, можно ли с поля (k, I) одним ходом ладьи, ферзя или слона попасть на поле (m, n). " <<
                        "Если нет, то выяснить, как это можно сделать за два хода." << std::endl;
    std::cout << "Для перехода в подзадачу введите число от 1 до 3: ";
}

int main() {
    SetConsoleOutputCP(CP_UTF8);

    do {
        user_greeting();
        std::cin >> manipulator;
    } while (!error_handler(manipulator, 1, 3));

    std::cout << std::endl;

    switch (manipulator) {
        case 1:
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

                if (plate[x_1 - 1][y_1 - 1] == plate[x_2 - 1][y_2 - 1]) {
                   std::cout << "Поля (k, I) и (m, n) - являются полями одного цвета !";
                } else {
                    std::cout << "Поля (k, I) и (m, n) - НЕ являются полями одного цвета !";
                }

            break;
        case 2:

            break;
        case 3:

            break;
        default:
            break;
    }

    system("pause");
    return 0;
}

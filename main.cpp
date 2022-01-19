#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

int manipulator, x_1, x_2, y_1, y_2, figure, answer2, answer3_x, answer3_y;
bool subtask3_flag1 = false;
bool subtask3_flag2 = false;
std::ofstream LogFile;

int plate [8][8] = {
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0}
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

void logger_init(){
    std::string LogFileName;
    // LogFileName += "\\File\\";

    time_t rawtime;
    struct tm * timeinfo;
    char buffer [80];                                                     // строка, в которой будет храниться текущее время
    time ( &rawtime );                                               // текущая дата в секундах
    timeinfo = localtime ( &rawtime );                               // текущее локальное время, представленное в структуре
    strftime (buffer,80,"(%Y-%m-%d)-(%H-%M-%S)-",timeinfo);     // форматируем строку времени

    LogFileName += buffer;
    LogFileName += "errors-log.txt";

    LogFile.open(LogFileName);
    if(!LogFile.is_open()) {
        std::cout << "Критическая ошибка! Невозможно создать файл журнала " << LogFileName;
        while(true);
    }
}

void logger(std::string Message) {

    time_t rawtime;
    struct tm * timeinfo;
    char buffer [80];                                                     // строка, в которой будет храниться текущее время
    time ( &rawtime );                                               // текущая дата в секундах
    timeinfo = localtime ( &rawtime );                               // текущее локальное время, представленное в структуре
    strftime (buffer,80,"(%H-%M-%S)-",timeinfo);     // форматируем строку времени

    std::string LogMessage;
    LogMessage += buffer;
    LogMessage += Message;

    LogFile << LogMessage << std::endl;
}

/*
 *  Функция error_handler возвращает истину в случае соответствия заданному диапазоне и ложь в обратном
 */

bool error_handler(int number, int minimum, int maximum) {
    if (number >= minimum && number <= maximum) {
        std::string Message;
        Message += "Проверка ввода пройдена успешно.";
        logger(Message);
        return true;
    } else {
        std::string Message;
        Message += "Пользователь допустил ошибку ввода, пользователь ввел - ";
        Message += std::to_string(number);
        Message += " при допустимом диапазоне от ";
        Message += std::to_string(minimum);
        Message += " до ";
        Message += std::to_string(maximum);
        logger(Message);
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
        logger("Пользователь получил приглашение к работе с программой");
    } while (!error_handler(manipulator, 1, 3));

}

void request_coordinates() {
    do {

        std::cout << std::endl;

        do {
            std::cout << "Введите координату X для первой точки (число от 1 до 8): ";
            std::cin >> x_1;
        } while (!error_handler(x_1, 1, 8));

        do {
            std::cout << "Введите координату Y для первой точки (число от 1 до 8): ";
            std::cin >> y_1;
        } while (!error_handler(y_1, 1, 8));

        std::cout << std::endl;

        do {
            std::cout << "Введите координату X для второй точки (число от 1 до 8): ";
            std::cin >> x_2;
        } while (!error_handler(x_2, 1, 8));

        do {
            std::cout << "Введите координату Y для второй точки (число от 1 до 8): ";
            std::cin >> y_2;
        } while (!error_handler(y_2, 1, 8));

        std::cout << std::endl;

        if (x_1 == x_2 && y_1 == y_2) {
            logger("Пользователь ввел одинаковые координаты.");
            std::cout << "Вы ввели одинаковые координаты ! Повторите попытку." << std::endl;
        }

    } while (x_1 == x_2 && y_1 == y_2); // Обработка ошибки ввода одинаковых координат
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
        } while (!error_handler(figure, 1, 4));
    } else {
        do {
            std::cout << "Введите номер фигуры:" << std::endl;
            std::cout << "    1) Ферзь"  << std::endl;
            std::cout << "    2) Ладья"  << std::endl;
            std::cout << "    3) Слон"  << std::endl;
            std::cout << "Введите число от 1 до 3: ";
            std::cin >> figure;
        } while (!error_handler(figure, 1, 3));
    }

    std::cout << std::endl;

    logger("Пользователь выбрал фигуру.");

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
    logger("Успешно произведена разметка треков ладьи.");
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
    logger("Успешно произведена разметка треков слона.");
}

void mark_queen(int x, int y) {
    mark_rock(x, y);
    mark_elephant(x, y);
    logger("Успешно произведена разметка треков ферзя.");
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

    logger("Успешно произведена разметка треков коня.");
}

int main() {
    SetConsoleOutputCP(CP_UTF8);

    logger_init();
    logger("Файл журнала успешно инициализирован");

    user_greeting();

    switch (manipulator) {
        case 1:
                logger("Пользователь выбрал подзадачу №1");

                request_coordinates();

                if (marked_plate[x_1 - 1][y_1 - 1] == marked_plate[x_2 - 1][y_2 - 1]) {
                   std::cout << "Поля (k, I) и (m, n) - являются полями одного цвета !" << std::endl;
                   logger("Поля (k, I) и (m, n) - являются полями одного цвета !");

                } else {
                    std::cout << "Поля (k, I) и (m, n) - НЕ являются полями одного цвета !" << std::endl;
                    logger("Поля (k, I) и (m, n) - НЕ являются полями одного цвета !");
                }

            break;
        case 2:
                logger("Пользователь выбрал подзадачу №2");
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
                    std::cout << "Поле (m, n) - находится под ударом !" << std::endl;
                    logger("Поле (m, n) - находится под ударом !");
                } else {
                    std::cout << "Поле (m, n) - НЕ находится под ударом !" << std::endl;
                    logger("Поле (m, n) - НЕ находится под ударом !");
                }

            break;
        case 3:
                logger("Пользователь выбрал подзадачу №3");
                request_coordinates();

                request_figure(false);

                switch (figure) {
                    case 1:
                        mark_queen(x_1 - 1, y_1 - 1);
                        if(plate[x_2 - 1][y_2 - 1] != 0){
                            subtask3_flag1 = true;
                        }
                        mark_queen(x_2 - 1, y_2 - 1);
                        break;
                    case 2:
                        mark_rock(x_1 - 1, y_1 - 1);
                        if(plate[x_2 - 1][y_2 - 1] != 0){
                            subtask3_flag1 = true;
                        }
                        mark_rock(x_2 - 1, y_2 - 1);
                        break;
                    case 3:
                        mark_elephant(x_1 - 1, y_1 - 1);
                        if(plate[x_2 - 1][y_2 - 1] != 0){
                            subtask3_flag1 = true;
                        }
                        mark_elephant(x_2 - 1, y_2 - 1);
                        break;
                    default:
                        break;
                }

                if(subtask3_flag1){
                    std::cout << "Можно попасть на поле (m, n) одним ходом !" << std::endl;
                } else {
                    for (int i = 0; i < 8; ++i) {
                        for (int j = 0; j < 8; ++j) {
                            if(plate[i][j] > 1 && plate[i][j] < 5) {
                                subtask3_flag2 = true;
                                std::cout << "Координаты промежуточного поля - (" << i + 1 << ":" << j + 1 << ") - для попадания на поле (m,n) за два хода." << std::endl;
                            }
                        }
                    }
                }

                if(!subtask3_flag2){
                    std::cout << "На поле (m,n) невозможно попасть ни за один, ни за два хода." << std::endl;
                }

            break;
        default:
            break;
    }

    std::cout << std::endl;
    LogFile.close();
    system("pause");
    return 0;
}

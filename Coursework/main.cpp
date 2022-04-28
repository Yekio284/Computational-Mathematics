#include <iostream>
#include "functions.h"

using namespace std;

int main() {
    double t0 = 0; // Начало отрезка
    double T = 90; // Конец отрезка
    double h = 1; // Шаг

    cout << "Входные данные: t0 = " << t0 << ", T = " << T << ", h = " << h << endl;
    cout << "Выходные данные записаны в файл 'out.txt'" << endl;

    euler_method(t0, T, h);
    
    return 0;
}
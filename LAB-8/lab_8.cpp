#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>

#define N 30

using namespace std;

double first_function(double x) {
    return x * x - 2 * x + 4;
}

double second_function(double x, double y) {
    return 3 * pow(y, 2) * pow(sin(x), 2);
}

double first_monte_carlo_method(double a, double b) {
    srand(time(NULL));
    
    FILE *out = fopen("out_first.txt", "w");
    double s = 0.0;

    for (int i = 0; i < N; i++) {
        double x = a + (double)(rand()) / RAND_MAX * (b - a); // случайное значение типа double в промежутке от a до b
        double y = first_function(a) + (double)(rand()) / RAND_MAX * (first_function(b) - first_function(a)); // случайное значение типа double в промежутке от f(a) до f(b)
        
        fprintf(out, "%lf %lf\n", x, y);

        s = s + first_function(x);
    }
    s = ((b - a) / N) * s;
    
    fclose(out);

    return s;
}

double second_monte_carlo_method() {
    srand(time(NULL));
    
    FILE *out = fopen("out_second.txt", "w");
    double s = 0.0;
    int in = 0;

    for (int i = 0; i < N; i++) {
        double x = (double)(rand()) / RAND_MAX * M_PI; // [0; PI] *double*
        double y = (double)(rand()) / RAND_MAX; // [0; 1] *double*
        
        fprintf(out, "%lf %lf\n", x, y);

        if (y <= sin(x)) {
            in++;
            s = s + second_function(x, y);
        }
    }

    fclose(out);

    double v = M_PI * in / N;
    double result = v * s / in;

    return result;
}

int main() {
    short choice;
    cout << "Какой интеграл будем считать?\n1. Одномерный определенный интеграл для функции x^2 - 2x + 4\n2. Двойной интеграл для функции 3y^2 * sin^2(x)\nВаш выбор: ";
    cin >> choice;
    cout << endl;
    if (choice != 1 && choice != 2) {
        cout << "Ошибка ввода." << endl;
        return -1;
    }
    
    switch (choice) {
    case 1:
        cout << "Введите отрезок [a; b]: ";
        double a, b;
        cin >> a >> b;
        cout << "Результат вычисления определенного интеграла методом Монте-Карло: S = " << first_monte_carlo_method(a, b) << endl;
        break;
    case 2:
        cout << "Интеграл посчитан в области Ω = {x ∈ [0; pi], y ∈ [0; sin(x)]}" << endl;
        cout << "Результат вычисления двойного интеграла методом Монте-Карло: S = " << second_monte_carlo_method() << endl; 
        break;

    default:
        break;
    }

    return 0;
}
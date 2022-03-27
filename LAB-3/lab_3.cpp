#include <iostream>
#include <cmath>
#include <unistd.h>

#define STEPS 4

using namespace std;

double function(double x) {
    return x*x - 3;
}

void show_function() {
    cout << "f(x) = x^2 - 3";
}

void bisection_method(double a, double b) {
    double epsilon, c;
    cout << "Метод половинного деления для ";
    show_function();
    cout << endl;
    
    for (int i = 0; i < STEPS; i++) {
        c = (a + b) / 2;
        cout << i + 1 << "-й шаг.\nc = " << c << endl;
        cout << "f(c) = " << function(c) << endl;
        
        epsilon = (abs(b - a)) / 2;
        cout << "ε = " << epsilon << endl;

        cout << "(" << a << "; "<< a + epsilon << "): " << function(a) * function (a + epsilon) << endl;
        cout << "(" << a + epsilon << "; "<< b << "): " << function(a + epsilon) * function (b) << endl;

        if (function(a) * function(a + epsilon) < 0) {
            cout << "(" << a << "; "<< a + epsilon << ") < 0 => данный интервал подходит нам.\n";
            b = a + epsilon;
        }
        else {
            cout << "(" << a + epsilon << "; "<< b << ") < 0 => данный интервал подходит нам.\n";
            a = a + epsilon;
        }

        cout << "---------------------------------------\n";
    }
    cout << "\n";
}

void secant_method(double a, double b) {
    double epsilon, c;
    cout << "Метод хорд для ";
    show_function();
    cout << endl;
    
    for (int i = 0; i < STEPS; i++) {
        c = (a * function(b) - b * function(a)) / (function(b) - function(a));
        cout << i + 1 << "-й шаг." << endl;
        cout << "f(a) = " << function(a) << endl;
        cout << "f(b) = " << function(b) << endl;
        cout << "c = " << c << endl;
        cout << "f(c) = " << function(c) << endl;
        
        epsilon = (abs(b - a)) / 2;
        cout << "ε = " << epsilon << endl;

        cout << "(" << a << "; "<< a + epsilon << "): " << function(a) * function (a + epsilon) << endl;
        cout << "(" << a + epsilon << "; "<< b << "): " << function(a + epsilon) * function (b) << endl;

        if (function(a) * function(a + epsilon) < 0) {
            cout << "(" << a << "; "<< a + epsilon << ") < 0 => данный интервал подходит нам.\n";
            b = a + epsilon;
        }
        else {
            cout << "(" << a + epsilon << "; "<< b << ") < 0 => данный интервал подходит нам.\n";
            a = a + epsilon;
        }

        cout << "---------------------------------------\n";
    }
    cout << "\n";
}

void newton_method() { // f(x) = x^2 -3, f'(x) = 2x
    double Xi = 2; //x0
    double df;
    cout << "Метод Ньютона для ";
    show_function();
    cout << endl;
    cout << "x0 = " << Xi << endl;

    for (int i = 0; i < STEPS; i++) {
        df = 2 * Xi;
        Xi = Xi - function(Xi) / df;
        cout << "x" << i + 1 << " = " << Xi << endl;
    }
}

int main() {
    double a, b;
    while (true) {
        system("clear");
        cout << "Введите интервал: ";
        cin >> a >> b;
        if (a > b) {
            cout << "Некорректный ввод интервала.\n";
            sleep(3);
            system("clear");
        }
        else {
            cout << endl;
            break;
        }
    }

    bisection_method(a, b);
    secant_method(a, b);
    newton_method();

    return 0;
}

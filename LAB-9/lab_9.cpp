#include <iostream>
#include <cstdio>

using namespace std;

double function(double x, double y) {
    return x + y;
}

void euler_method(double a, double b, int n) {
    FILE *out = fopen("out_euler.txt", "w");
    double h = (b - a) / n;
    double *x = new double[n + 1];
    double *y = new double[n + 1];

    x[0] = a;
    y[0] = 1;
    fprintf(out, "%lf %lf\n", x[0], y[0]);

    cout << "Метод Эйлера:\n";
    for (int i = 1; i <= n; i++) {
        x[i] = a + i * h;
        y[i] = y[i - 1] + h * function(x[i - 1], y[i - 1]);

        cout << "x[" << i << "] = " << x[i] << endl;
        cout << "y[" << i << "] = " << y[i] << endl << endl;
        fprintf(out, "%lf %lf\n", x[i], y[i]);
    }
    cout << "-----------------------------------------------\n\n";

    fclose(out);

    delete[] x;
    delete[] y;
}

void euler_cauchy_method(double a, double b, int n) {
    FILE *out = fopen("out_euler_cauchy.txt", "w");
    double h = (b - a) / n;
    double *x = new double[n + 1];
    double *y = new double[n + 1];
    double *y1 = new double[n + 1];

    x[0] = a;
    y[0] = 1;
    fprintf(out, "%lf %lf\n", x[0], y[0]);

    cout << "Метод Эйлера-Коши:\n";
    for (int i = 1; i <= n; i++) {
        x[i] = a + i * h;
        y1[i] = y[i - 1] + h * function(x[i - 1], y[i - 1]);
        y[i] = y[i - 1] + h * (function(x[i - 1], y[i - 1]) + function(x[i], y1[i])) / 2;

        cout << "x[" << i << "] = " << x[i] << endl;
        cout << "y[" << i << "] = " << y[i] << endl << endl;
        fprintf(out, "%lf %lf\n", x[i], y[i]);
    }
    cout << "-----------------------------------------------\n\n";

    fclose(out);

    delete[] x;
    delete[] y;
    delete[] y1;
}

void runge_kutta_method(double a, double b, int n) {
    FILE *out = fopen("out_runge_kutta.txt", "w");
    double h = (b - a) / n;
    double *x = new double[n + 1];
    double *y = new double[n + 1];
    double *y1 = new double[n + 1];
    double *y2 = new double[n + 1];
    double *y3 = new double[n + 1];
    double *y4 = new double[n + 1];

    x[0] = a;
    y[0] = 1;
    fprintf(out, "%lf %lf\n", x[0], y[0]);

    cout << "Метод Рунге-Кутты:\n";
    for (int i = 1; i <= n; i++) {
        x[i] = a + i * h;
        y1[i] = h * function(x[i - 1], y[i - 1]);
        y2[i] = h * function(x[i - 1] + h / 2, y[i - 1] + y1[i] / 2);
        y3[i] = h * function(x[i - 1] + h / 2, y[i - 1] + y2[i] / 2);
        y4[i] = h * function(x[i - 1] + h, y[i - 1] + y3[i]);
        y[i] = y[i - 1] + (y1[i] + 2 * y2[i] + 2 * y3[i] + y4[i]) / 6;

        cout << "x[" << i << "] = " << x[i] << endl;
        cout << "y[" << i << "] = " << y[i] << endl << endl;
        fprintf(out, "%lf %lf\n", x[i], y[i]);
    }
    cout << "-----------------------------------------------\n\n";

    fclose(out);

    delete[] x;
    delete[] y;
    delete[] y1;
    delete[] y2;
    delete[] y3;
    delete[] y4;
}

int main() {
    cout << "Выберите метод:\n1. Метод Эйлера\n2. Метод Эйлера-Коши\n3. Метод Рунге-Кутты\n4. Все три\nВаш выбор: ";
    short choice;
    try {
        cin >> choice;
        if (choice != 1 && choice != 2 && choice != 3 && choice != 4)
            throw choice;
    }
    catch (short personsChoice) {
        cout << "Ошибка ввода. Введенное число (" << personsChoice << ") не является ни 1, ни 2, ни 3, ни 4.\n";
        return -1;
    }

    cout << endl;

    cout << "Введите отрезок [a; b]: ";
    double a, b;
    cin >> a >> b;

    cout << "Введите кол-во разбиений n: ";
    int n;
    cin >> n;

    switch (choice) {
    case 1:
        euler_method(a, b, n);
        break;
    case 2:
        euler_cauchy_method(a, b, n);
        break;
    case 3:
        runge_kutta_method(a, b, n);
        break;
    case 4:
        euler_method(a, b, n);
        euler_cauchy_method(a, b, n);
        runge_kutta_method(a, b, n);
        break;
    
    default:
        break;
    }

    return 0;
}
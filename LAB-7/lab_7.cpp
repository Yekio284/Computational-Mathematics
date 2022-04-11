#include <iostream>
#include <cmath>

using namespace std;

double function(double x) {
    return x * x - 2 * x + 4;
}

double right_rectangle_method(double a, double b, double n) {
    double h = (b - a) / n; 
    double s = 0.0;

    for (int i = 1; i <= n; i++)
        s = s + h * function(a + i * h);

    return s;
}

double trapeze_method(double a, double b, double n) {
    double h = (b - a) / n;
    double s = function(a) + function(b);

    for (int i = 1; i <= n - 1; i++)
        s = s + 2 * function(a + i * h);
    
    s = s * h / 2;
    return s;
}

double simpson_method(double a, double b, double n) {
    double h = (b - a) / n;
    double s = function(a) + function(b);

    for (int i = 1; i <= n - 1; i++) {
        int k = 2 + 2 * (i % 2);
        s = s + k * function(a + i * h);
    }

    s = s * h / 3;
    return s;
}

int main() {
    short choice;
    cout << "Выберите метод интегрирования:\n1. Метод правых прямоугольников\n2. Метод трапеций\n3. Метод Симпсона\nВаш выбор: ";
    cin >> choice;
    if (choice != 1 && choice != 2 && choice != 3) {
        cout << "Неверный ввод." << endl;
        return -1;
    }

    cout << "Введите отрезок [a; b]: ";
    double a, b;
    cin >> a >> b;

    cout << "Введите погрешность вычисления интеграла ε: ";
    double epsilon;
    cin >> epsilon;

    int k = 10; 
    int i = 1;

    switch (choice) {
    case 1:
        while (abs(right_rectangle_method(a, b, k * i) - right_rectangle_method(a, b, k * (i + 1))) > epsilon)
            i++;
        cout << "Результат интегрирования методом правых прямоугольников: S = " << right_rectangle_method(a, b, k * (i + 1)) << endl;
        break;
    case 2:
        while (abs(trapeze_method(a, b, k * i) - trapeze_method(a, b, k * (i + 1))) > epsilon)
            i++;
        cout << "Результат интегрирования методом трапеций: S = " << trapeze_method(a, b, k * (i + 1)) << endl;
        break;
    case 3:
        while (abs(simpson_method(a, b, k * i) - simpson_method(a, b, k * (i + 1))) > epsilon)
            i++;
        cout << "Результат интегрирования методом Симпсона: S = " << simpson_method(a, b, k * (i + 1)) << endl;
        break;

    default:
        break;
    }   

    return 0;
}
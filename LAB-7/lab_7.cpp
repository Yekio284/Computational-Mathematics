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

int main() {
    cout << "Введите отрезок [a; b]: ";
    double a, b;
    cin >> a >> b;

    cout << "Введите погрешность вычисления интеграла ε: ";
    double epsilon;
    cin >> epsilon;

    int k = 10; 
    int i = 1;
    
    while (abs(right_rectangle_method(a, b, k * i) - right_rectangle_method(a, b, k * (i + 1))) > epsilon)
        i++;
    
    cout << "Результат интегрирования методом правых прямоугольников: S = " << right_rectangle_method(a, b, k * i) << endl;

    return 0;
}
#pragma once

#include <cstdio>
#include <iostream>
#include "coefficients.h"

double function_a(double t) {
    return t;
}

double function_c(double t) {
    return 1 + c_isol * (1 - 2 / 5 * function_a(t));
}

double function_s(double S, double E, double I, double R, double N) {
    return -1 * function_c(c_isol) * ((alpha_I * S * I) / N  + (alpha_E * S * E) / N) + gamma * R;
}

double function_e(double S, double E, double I, double N) {
    return function_c(c_isol) * ((alpha_I * S * I) / N + (alpha_E * S * E) / N) - (k + ro) * E;
}

double function_i(double E, double I) {
    return k * E - betta * I - mu * I;
}

double function_r(double E, double I, double R) {
    return betta * I + ro * E - gamma * R;
}

double function_d(double I) {
    return mu * I;
}

void euler_method(double t0, double T, double h) {
    FILE *out = fopen("out.txt", "w"); // Открываем файл out.txt на запись
    int n = (T - t0) / h + 1; // Количество промежутков
    double *S = new double[n]; // Восприимчивые (незараженные) индивидуумы c 3 лет;
    double *E = new double[n]; // Зараженные или находящиеся в инкубационном периоде индивидуумы;
    double *I = new double[n]; // Инфицированные с симптомами;
    double *R = new double[n]; // Вылеченные;
    double *D = new double[n]; // Умершие;
    double *N = new double[n]; // Вся популяция;
    double *t = new double[n]; // Номер дня.

    /* Начальные значения для массивов: */
    E[0] = E0;
    R[0] = R0;
    S[0] = 2798170 - E[0] - R[0];
    I[0] = I0;
    D[0] = D0;
    N[0] = S[0] + E[0] + I[0] + R[0] + D[0];
    t[0] = t0;
    
    fprintf(out, "%lf %.2lf %.2lf %.2lf %.2lf %.2lf %.2lf\n", t[0], N[0], S[0], E[0], I[0], R[0], D[0]); // Запись в файл начальных значений

    /* Высчитываем значения для i-х ячеек массивов */
    for (int i = 1; i < n; i++) {
        t[i] = t0 + i * h;
        S[i] = S[i - 1] + h * function_s(S[i - 1] + h / 2 * function_s(S[i - 1], E[i - 1], I[i - 1], R[i - 1], N[i - 1]), E[i - 1], I[i - 1], R[i - 1], N[i - 1]);
        E[i] = E[i - 1] + h * function_e(S[i - 1], E[i - 1] + h / 2 * function_e(S[i - 1], E[i - 1], I[i - 1], N[i - 1]), I[i - 1], N[i - 1]);
        I[i] = I[i - 1] + h * function_i(E[i - 1], I[i - 1] + h / 2 * function_i(E[i - 1], I[i - 1]));
        R[i] = R[i - 1] + h * function_r(E[i - 1], I[i - 1], R[i - 1] + h / 2 * function_r(E[i - 1], I[i - 1], R[i - 1]));
        D[i] = D[i - 1] + h * function_d(I[i - 1]);
        N[i] = S[i] + E[i] + I[i] + R[i] + D[i];

        fprintf(out, "%lf %.2lf %.2lf %.2lf %.2lf %.2lf %.2lf\n", t[i], N[i], S[i], E[i], I[i], R[i], D[i]); // Запись в файл высчитанных значений
    }

    fclose(out); // Закрываем файл out.txt

    /* Высвобождаем память, которую выделили для массивов */
    delete[] S;
    delete[] E;
    delete[] I;
    delete[] R;
    delete[] D;
    delete[] N;
    delete[] t;
}

#include <iostream>
#include <cstdio>

#define LENGTH 4

using namespace std;

double newton_first(double *x, double *y, double inter, double h) {
    double **delta_y = new double*[LENGTH];
    for (int i = 0; i < LENGTH; i++) 
        delta_y[i] = new double[LENGTH];
    
    for (int i = 0; i < LENGTH; i++)
        delta_y[0][i] = y[i];
 
    for (int i = 1; i < LENGTH; i++) {
        for (int j = 0; j < LENGTH - i; j++) {
            delta_y[i][j] = delta_y[i - 1][j + 1] - delta_y[i - 1][j];
        }
    }

    double q = (inter - x[0]) / h;
    double result = y[0];
    double qn = 1;
    double factorial = 1; 
 
    for (int i = 1; i < LENGTH; i++) {
        factorial = factorial * i;
        qn = qn * (q - i + 1);
        result = result + qn / factorial * delta_y[i][0];
    }
 
    for (int i = 0; i < LENGTH; i++) 
        delete[] delta_y[i];
    delete[] delta_y;
 
    return result;
}

double newton_second(double *x, double *y, double inter, double h) {
    double **delta_y = new double*[LENGTH];
    for (int i = 0; i < LENGTH; i++) 
        delta_y[i] = new double[LENGTH];
    
    for (int i = 0; i < LENGTH; i++)
        delta_y[0][i] = y[i];
 
    for (int i = 1; i < LENGTH; i++) {
        for (int j = 0; j < LENGTH - i; j++) {
            delta_y[i][j] = delta_y[i - 1][j + 1] - delta_y[i - 1][j];
        }
    }

    double q = (inter - x[LENGTH - 1]) / h;
    double result = y[LENGTH - 1];
    double qn = 1;
    double factorial = 1; 
 
    for (int i = 1, t = LENGTH - 2; i < LENGTH; i++, t--) {
        factorial = factorial * i;
        qn = qn * (q + i - 1);
        result = result + qn / factorial * delta_y[i][t];
    }

    for (int i = 0; i < LENGTH; i++) 
        delete[] delta_y[i];
    delete[] delta_y;
 
    return result;
}

int main() {
    FILE *in = fopen("in.txt", "r");
    FILE *out_first = fopen("out_first.txt", "w");
    FILE *out_second = fopen("out_second.txt", "w");

    double inter;
    cout << "Введите число для интерполяции(x): ";
    cin >> inter;
    
    double *x = new double[LENGTH];
    double *y = new double[LENGTH];

    for (int i = 0; i < LENGTH; i++) {
        fscanf(in, "%lf", &x[i]);
    }
    for (int i = 0; i < LENGTH; i++) {
        fscanf(in, "%lf", &y[i]);
    }

    cout << "Введите h: ";
    double h;
    cin >> h;

    double result_first = newton_first(x, y, inter, h);
    cout << "Результат интерполяции по I-й формуле Ньютона: " << result_first << endl;
    double result_second = newton_second(x, y, inter, h);
    cout << "Результат интерполяции по II-й формуле Ньютона: " << result_second << endl;


    short a = 0, i = 0;
    
    while (i < LENGTH) {
        if (inter > x[LENGTH - 1]) {
	    for (int j = 0; j < LENGTH; j++) {
	        fprintf(out_first, "%lf %lf\n", x[j], y[j]);
                fprintf(out_second, "%lf %lf\n", x[j], y[j]);
	    }
	    fprintf(out_first, "%lf %lf\n", inter, result_first);
            fprintf(out_second, "%lf %lf\n", inter, result_second);
	    break;
	}
	else {
	    if (x[i] < inter || a) {
                fprintf(out_first, "%lf %lf\n", x[i], y[i]);
                fprintf(out_second, "%lf %lf\n", x[i], y[i]);
	        i++;
	    }
	    else if (!a) {
                fprintf(out_first, "%lf %lf\n", inter, result_first);
                fprintf(out_second, "%lf %lf\n", inter, result_second);
                a = 1;
	    }
	}
    }

    fclose(in);
    fclose(out_first);
    fclose(out_second);

    delete[] x;
    delete[] y;
    
    return 0;
}
#include <iostream>
#include <cstdio>
#include <cmath>

#define SIZE 3

using namespace std;

double *iterative_method(double **a, double *x, int n) {
	double *result = new double[n];
	int i, j;

	for (i = 0; i < n; i++)
		result[i] = x[i] / a[i][i]; //результат и начальное приближение

	double epsilon = 0.0001; //вводим точность
	double *next_approximation = new double[n]; //вычисляем последующие приближения

	while (true) {
		for (i = 0; i < n; i++) { //сам алгоритм
			next_approximation[i] = x[i] / a[i][i];
			for (j = 0; j < n; j++) {
				if (i == j)
					continue;
				else {
					next_approximation[i] = next_approximation[i] - a[i][j] / a[i][i] * result[j];
				}
			}
		}

		bool flag = true;
		
        for (i = 0; i < n - 1; i++) { //проверяем: является ли текущее приблежение верным?
			if (abs(next_approximation[i] - result[i]) > epsilon) {
				flag = false;
				break;
			}
		}

		for (i = 0; i < n; i++)
			result[i] = next_approximation[i];

		if (flag)
			break;

	}

        delete[] next_approximation;

	return result;
}

int main() {
    double **matrix = new double*[SIZE];
    for (int i = 0; i < SIZE; i++) 
        matrix[i] = new double[SIZE];

    double *x = new double[SIZE];
    
    FILE *in = fopen("in.txt", "r");
    FILE *out = fopen("out.txt", "w");

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            fscanf(in, "%lf", &matrix[i][j]);
        }
	fscanf(in, "%lf", &x[i]);
    }
    fclose(in);
    
    double *result = iterative_method(matrix, x, SIZE);
    
    for (int i = 0; i < SIZE; i++)
        fprintf(out, "x%d = %lf\n", i + 1, result[i]);
    
    fclose(out);

    delete[] result;
    delete[] x;
    
    for(int i = 0; i < SIZE; i++)
	delete[] matrix[i];
    
    return 0;
}

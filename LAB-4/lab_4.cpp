#include <iostream> 
#include <cstdio>

#define LENGTH 5

using namespace std;

double lagrange_method(double *x, double *y, double inter) {
	double result = 0.0;
	double k;

	for (int i = 0; i < LENGTH; i++) {
		k = y[i];
		for (int j = 0; j < LENGTH; j++) {
			if (i != j)
				k = k * ((inter - x[j]) / (x[i] - x[j])); 
		}
		result = result + k;
	}
	return result;
}

int main() {
	FILE *in = fopen("in.txt", "r");
	FILE *out = fopen("out.txt", "w");
	
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

	double result = lagrange_method(x, y, inter);
	cout << "Результат интерполяции: " << result << endl;

	short a = 0, i = 0;

	while (i < LENGTH) {
		if (inter > x[LENGTH - 1]) {
			for (int j = 0; j < LENGTH; j++) {
				fprintf(out, "%lf %lf\n", x[j], y[j]);
			}
			fprintf(out, "%lf %lf\n", inter, result);
			break;
		}
		else {
			if (x[i] < inter || a) {
				fprintf(out, "%lf %lf\n", x[i], y[i]);
				i++;
			}
			else if (!a) {
				fprintf(out, "%lf %lf\n", inter, result);
				a = 1;
			}
		}
	}

	fclose(in);
	fclose(out);

	delete[] x;
	delete[] y;
	
	return 0;
}

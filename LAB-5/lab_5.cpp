#include <iostream>
#include <cstdio>

using namespace std;

struct Length {
    int x_length = 5;
    int y_length = 0;
};

double aitken_method(double *x, double *y, double inter, struct Length length) {
    int c = length.x_length;

    for (int i = 0; i < length.x_length - 1; i++) {
        for (int j = 0; j < length.x_length - i - 1; j++, c++) {
            y[c] = (y[c - length.x_length + i] * (inter - x[i + j + 1]) - y[c - length.x_length + i + 1] * (inter - x[j])) / (x[j] - x[i + j + 1]);
        }
    }

    return y[c - 1];
}

int main() {
    FILE *in = fopen("in.txt", "r");
    FILE *out = fopen("out.txt", "w");
	
    double inter;
    cout << "Введите число для интерполяции(x): ";
    cin >> inter;

    struct Length length;
    
    for (int i = 0; i < length.x_length; i++) {
        length.y_length = length.y_length + length.x_length - i;
    }

    double *x = new double[length.x_length];
    double *y = new double[length.y_length];

    for (int i = 0; i < length.x_length; i++) {
        fscanf(in, "%lf", &x[i]);
    }
    for (int i = 0; i < length.x_length; i++) {
	fscanf(in, "%lf", &y[i]);
    }
    
    double result = aitken_method(x, y, inter, length);
    cout << "Результат интерполяции: " << result << endl;

    short a = 0, i = 0;
    
    while (i < length.x_length) {
	if (inter > x[length.x_length - 1]) {
	    for (int j = 0; j < length.x_length; j++) {
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

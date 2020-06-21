#include <cmath>
#include <stdio.h>

int main() {
    double x = 12e-9;
    double c = cos(x);
    double one_sub_c = 1 - c;
    double denom = x*x;
    double yhat = one_sub_c / denom;

    printf("x:         %20.16f\n"
           "cx:        %20.16f\n"
           "one_sub_c: %20.16f\n"
           "denom:     %20.16f\n"
           "yhat:      %20.16f\n",
            x, c, one_sub_c, denom, yhat); 
}

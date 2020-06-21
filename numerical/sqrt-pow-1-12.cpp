#include <cmath>
#include <stdio.h>

int main() {
    double x = 2;
    for(int i = 0; i < 55; ++i) {
        printf("x: %10.20f\n", x);
        x = sqrt(x);
    }
    printf("x: %10.20f\n", x);
    printf("###POWERING###\n");
    for(int i = 0; i < 55; ++i) {
        printf("x: %10.20f\n", x);
        x = x*x;
    }
    printf("x: %10.20f\n", x);
}

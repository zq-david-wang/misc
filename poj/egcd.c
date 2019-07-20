#include<stdio.h>

int egcd(int a, int b, int *x, int *y)
{
    if (a == 0) {
        *x = 0; *y = 1;
        return b;
    }
    int x1, y1; // To store results of recursive call
    int g = egcd(b%a, a, &x1, &y1);
    *x = y1 - (b/a) * x1;
    *y = x1;
    return g;
}

int main() {
    return 0;
}

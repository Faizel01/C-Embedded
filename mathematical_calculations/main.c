#include <stdio.h>
#include <math.h>

// VARIANT 16

int main() {
    double x;
    double z1, z2;

    printf("Enter x: ");
    scanf("%lf", &x);

    if (x * x - 9 < 0) {
        printf("Error: z1 is not defined for this x.\n");
        return 1;
    }

    double sqrt_part = sqrt(x * x - 9);

    double denominator =
        x * x - 2 * x - 3 + (x - 1) * sqrt_part;

    if (fabs(denominator) < 1e-12) {
        printf("Error: denominator of z1 is zero.\n");
        return 1;
    }

    z1 = (x * x + 2 * x - 3 + (x + 1) * sqrt_part) / denominator;

    // z2 = sqrt((x + 3) / (x - 3))
    double fraction = (x + 3) / (x - 3);

    if (x == 3 || fraction < 0) {
        printf("Error: z2 is not defined for this x.\n");
        return 1;
    }

    z2 = sqrt(fraction);

    printf("z1 = %.6f\n", z1);
    printf("z2 = %.6f\n", z2);

    return 0;
}
#include <iostream>
#include <cstdio>
#include "rational.h"

int main(void)
{
    PRATIONAL n1, n2;
    int fenzi, fenmu;

    printf("input two rational numbers in the form of \"x/y\": \n");

    printf("input first rational number:");
    scanf("%d/%d", &fenzi, &fenmu);
    while (fenmu == 0) {
        printf("the denominator cannot be zero, please re-enter！\n");
        printf("input first rational number:");
        scanf("%d/%d", &fenzi, &fenmu);
    }
    n1 = create_rational(fenzi, fenmu);

    printf("input second rational number:");
    scanf("%d /%d", &fenzi, &fenmu);
    while (fenmu == 0) {
        printf("the denominator cannot be zero, please re-enter！\n");
        printf("input second rational number:");
        scanf("%d/%d", &fenzi, &fenmu);
    }
    n2 = create_rational(fenzi, fenmu);

    printf("\n");
    PRATIONAL result = plus(n1, n2);
    printf("plus result: %d/%d\n", get_fenzi(result), get_fenmu(result));
    result = minus(n1, n2);
    printf("minus result: %d/%d\n", get_fenzi(result), get_fenmu(result));
    result = multi(n1, n2);
    printf("multiply result: %d/%d\n", get_fenzi(result), get_fenmu(result));
    result = div(n1, n2);
    printf("division result: %d/%d\n", get_fenzi(result), get_fenmu(result));

    destroy_rational(result);
    destroy_rational(n1);
    destroy_rational(n2);

    return 0;
}
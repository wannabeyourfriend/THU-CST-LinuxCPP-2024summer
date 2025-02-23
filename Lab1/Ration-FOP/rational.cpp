#include <iostream>
#include <cstdio>
#include "rational.h"

struct RATIONAL {int fenzi, fenmu;};

PRATIONAL create_rational(int fenzi, int fenmu)
{
    PRATIONAL p = new RATIONAL;
    if (p == NULL){
        exit(1);
    }

    p->fenzi = fenzi;
    p->fenmu = fenmu;

    return p;
}

void destroy_rational(PRATIONAL x)
{
    delete x;
}

PRATIONAL plus(const PRATIONAL first, const PRATIONAL second)
{
    PRATIONAL result = new RATIONAL;

    result->fenzi = first->fenzi * second->fenmu + second->fenzi * first->fenmu;
    result->fenmu = first->fenmu * second->fenmu;

    simply(result);

    return result;
}

PRATIONAL minus(const PRATIONAL first, const PRATIONAL second)
{
    PRATIONAL result = new RATIONAL;

    result->fenzi = first->fenzi * second->fenmu - second->fenzi * first->fenmu;
    result->fenmu = first->fenmu * second->fenmu;

    simply(result);

    return result;
}


PRATIONAL multi(const PRATIONAL first, const PRATIONAL second)
{
    PRATIONAL result = new RATIONAL;

    result->fenzi = first->fenzi * second->fenzi;
    result->fenmu = first->fenmu * second->fenmu;

    simply(result);

    return result;
}


PRATIONAL div(const PRATIONAL first, const PRATIONAL second)
{
    if (second->fenzi == 0)
    {
        exit(1);
    }

    PRATIONAL result = new RATIONAL;

    result->fenzi = first->fenzi * second->fenmu;
    result->fenmu = first->fenmu * second->fenzi;

    simply(result);

    return result;
}

void simply(PRATIONAL x)
{
    int a = x->fenzi, b = x->fenmu;

    while (b){
        int mod = a % b;
        a = b;
        b = mod;
    }

    x->fenzi /= a;
    x->fenmu /= a;
}

int get_fenzi(PRATIONAL x)
{
    return x->fenzi;
}

int get_fenmu(PRATIONAL x)
{
    return x->fenmu;
}
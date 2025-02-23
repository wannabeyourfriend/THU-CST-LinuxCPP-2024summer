#ifndef RATIONAL_H
#define RATIONAL_H
struct RATIONAL;
typedef struct RATIONAL * PRATIONAL;
PRATIONAL create_rational(int fenzi, int fenmu);
void destroy_rational(PRATIONAL x);
PRATIONAL plus(const PRATIONAL first, const PRATIONAL second);
PRATIONAL minus(const PRATIONAL first, const PRATIONAL second);
PRATIONAL multi(const PRATIONAL first, const PRATIONAL second);
PRATIONAL div(const PRATIONAL first, const PRATIONAL second);
void simply(PRATIONAL x);
int get_fenzi(PRATIONAL x);
int get_fenmu(PRATIONAL x);

#endif
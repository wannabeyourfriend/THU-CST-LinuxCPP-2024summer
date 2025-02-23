#ifndef POINT_H
#define POINT_H
struct POINT;
typedef struct POINT * PPOINT;

PPOINT PtCreate(double x, double y);
void PtDestroy(PPOINT point);
void PtGetValue(PPOINT point, double *x, double *y);
void PtSetValue(PPOINT point, double x, double y);
bool PtCompare(PPOINT point1, PPOINT point2);
char * PtTransformIntoString(const char *format, PPOINT point);
void PtPrint(PPOINT point);
#endif
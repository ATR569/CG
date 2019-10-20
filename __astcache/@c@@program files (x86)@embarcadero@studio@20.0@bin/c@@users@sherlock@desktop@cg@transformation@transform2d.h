#ifndef transform2DH
#define transform2DH

#include <math.h>

class Matrix;
class Point2D;

Matrix * getTranslationMatrix(double tx, double ty);

Matrix * getScaleMatrix(double sx, double sy);

Matrix * getScaleMatrix(double sx, double sy, Point2D * p);

Matrix * getShearMatrix(double shx, double shy);

Matrix * getShearMatrix(double shx, double shy, Point2D * p);

Matrix * getRotationMatrix(double theta);

Matrix * getRotationMatrix(double theta, Point2D * p);

Matrix * getReflectionMatrix(int axis);

Matrix * getReflectionMatrix(double m, double b);

Matrix * getIdentityMatrix();

Matrix * getWinVPMatrix(double uMin, double uMax, double vMin, double vMax, int xMin, int xMax, int yMin, int yMax);

bool cut(Point2D * p1, Point2D * p2, int xMin, int xMax, int yMin, int yMax);

#endif
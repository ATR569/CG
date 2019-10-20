#ifndef transform3DH
#define transform3DH

#include <math.h>

class Matrix;
class Point3D;

Matrix * getTranslationMatrix(double tx, double ty, double tz);

Matrix * getScaleMatrix(double sx, double sy, double sz);

Matrix * getScaleMatrix(double sx, double sy, double sz, Point3D * p);

Matrix * getShearMatrix(double shx, double shy);

Matrix * getShearMatrix(double shx, double shy, Point3D * p);

Matrix * getRotationMatrix(double theta);

Matrix * getRotationMatrix(double theta, Point3D * p);

Matrix * getReflectionMatrix(int axis);

Matrix * getReflectionMatrix(double m, double b);

Matrix * getIdentityMatrix();

Matrix * getWinVPMatrix(double uMin, double uMax, double vMin, double vMax, int xMin, int xMax, int yMin, int yMax, int zMin, int zMax);

#endif
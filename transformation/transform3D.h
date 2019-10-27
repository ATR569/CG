#ifndef transform3DH
#define transform3DH

#include <math.h>

class Matrix;
class Point3D;

Matrix * getTranslation3DMatrix(double tx, double ty, double tz);

Matrix * getScale3DMatrix(double sx, double sy, double sz);

Matrix * getScale3DMatrix(double sx, double sy, double sz, Point3D * p);

Matrix * getShear3DMatrix(double shx, double shy);

Matrix * getShear3DMatrix(double shx, double shy, Point3D * p);

Matrix * getRotation3DMatrix(double theta);

Matrix * getRotation3DMatrix(double theta, Point3D * p);

Matrix * getReflectionMatrixAxis(int axis);

Matrix * getReflectionMatrixPlan(int plan);

Matrix * getReflection3DMatrix(double m, double b);

Matrix * getIdentity3DMatrix();

Matrix * getProjectionMatrix();

#endif
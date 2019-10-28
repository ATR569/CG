#ifndef transform3DH
#define transform3DH

#include <math.h>

class Matrix;
class Point3D;

Matrix * getTranslation3DMatrix(double tx, double ty, double tz);

Matrix * getScale3DMatrix(double sx, double sy, double sz);

Matrix * getScale3DMatrix(double sx, double sy, double sz, Point3D * p);

Matrix * getShearMatrixAroundAxisX(double shy, double shz, Point3D * p);

Matrix * getShearMatrixAroundAxisY(double shx, double shz, Point3D * p);

Matrix * getShearMatrixAroundAxisZ(double shx, double shy, Point3D * p);

Matrix * getRotation3DMatrix(double theta, int axis);

Matrix * getRotation3DMatrix(double theta, Point3D * p);

Matrix * getReflectionMatrixAxis(int axis);

Matrix * getReflectionMatrixPlan(int plan);

Matrix * getReflection3DMatrix(double m, double b);

Matrix * getProjectionMatrix();

Matrix * getIdentity3DMatrix();

#endif
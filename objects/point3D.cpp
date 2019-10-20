//---------------------------------------------------------------------------

#pragma hdrstop

#include "point3D.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

#include "matrix.h"

Point3D::Point3D(double X, double Y, double Z) {
	this->X = X;
	this->Y = Y;
    this->Z = Z;
}

Point3D::Point3D(){
	Point3D(0,0,0);
}

void Point3D::aplly(Matrix * t){
	Matrix M2 = ((*t)*(*this->asMatrix()));
	(*this) = *(M2.asPoint3D());
}

Matrix * Point3D::asMatrix(){
	Matrix * m = new Matrix(4,1);
	m->setValue(0,0,this->X);
	m->setValue(1,0,this->Y);
	m->setValue(2,0,this->Z);	
	m->setValue(3,0,1);	
	return m;
}

double dist(Point3D * p1, Point3D * p2){
	double dx = p1->X - p2->X;
	double dy = p1->Y - p2->Y;
    double dz = p1->Z - p2->Z;
	return sqrt(dx*dx + dy*dy + dz*dz);
}


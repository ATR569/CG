//---------------------------------------------------------------------------

#pragma hdrstop

#include "point2D.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

#include "matrix.h"

Point2D::Point2D(double X, double Y) {
	this->X = X;
	this->Y = Y;
}

Point2D::Point2D(){
	Point2D(0,0);
}

void Point2D::aplly(Matrix * t){
	Matrix M2 = ((*t)*(*this->asMatrix()));
	(*this) = *(M2.asPoint2D());
}

Matrix * Point2D::asMatrix(){
	Matrix * m = new Matrix(3,1);
	m->setValue(0,0,this->X);
	m->setValue(1,0,this->Y);
	m->setValue(2,0,1);
	
	return m;
}

double dist(Point2D * p1, Point2D * p2){
	double dx = p1->X - p2->X;
	double dy = p1->Y - p2->Y;
	return sqrt(dx*dx + dy*dy);
}


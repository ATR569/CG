#ifndef matrixH
#define matrixH

#include <vector>

#define vvd std::vector<std::vector<double> >

class Point2D;
class Point3D;

class Matrix{
	vvd data;
public:
	Matrix(int N, int M);
	Matrix(vvd data);

	Matrix operator*(Matrix & m1);

	std::pair<int, int> dim();
	vvd getData();
	
	void setValue(unsigned i, unsigned j, double v);
	void assign(vvd data);
	void assign(Matrix M);
	
    Point2D * asPoint2D();
    Point3D * asPoint3D();
};

#endif
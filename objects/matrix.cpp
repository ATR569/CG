//---------------------------------------------------------------------------

#pragma hdrstop

#include "matrix.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

#include "point2D.h"
#include <math.h>

Matrix::Matrix(int N, int M) : data(vvd(N, std::vector<double>(M, 0))){}

Matrix::Matrix(vvd data) : data(data){}

Matrix Matrix::operator*(Matrix & m1){
	if (dim().second != m1.dim().first)
		throw(std::exception());

	int n = dim().first;
	int m = m1.dim().second;
	int line = dim().second;

	Matrix result(n, m);

	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){
			for (int k = 0; k < line; k++){
				result.data[i][j] += data[i][k]*m1.data[k][j];
			}
		}
	}

	return result;
}

std::pair<int, int> Matrix::dim(){
	return std::pair<int, int>(data.size(), data[0].size());
}

vvd Matrix::getData(){
	return this->data;
}

void Matrix::setValue(unsigned i, unsigned j, double v){
	if (i < data.size() && j < data[0].size())
		this->data[i][j] = v;
}

Point2D * Matrix::asPoint2D(){
    if (this->data.size() != 3 || this->data[0].size() != 1)
		throw std::exception();

	return new Point2D(this->data[0][0], this->data[1][0]);
}


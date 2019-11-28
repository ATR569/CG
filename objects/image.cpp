//---------------------------------------------------------------------------

#pragma hdrstop

#include "image.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

#include "workspace.h"
#include "graphics.h"

bool Image::isValid(int i, int j){
    if (i < 0 || i >= getHeight()) return false;
    if (j < 0 || j >= getWidth()) return false;
    return true;
}

Image::Image(int X, int Y, vector<vector<int> > data){
    this->X = X;
    this->Y = Y;
    this->data = data;
}

vector<vector<int>> Image::getData(){
    return this->data;
}

vector<int> Image::getLine(int i){
    return this->data[i];
}

int Image::getX(){
    return this->X;
}

int Image::getY(){
    return this->Y;
}

int Image::getHeight(){
    return data.size();
}

int Image::getWidth(){
    return data[0].size();
}

void Image::setPixel(int X, int Y, int value){
    if (X < data.size() && Y < data[X].size()){
        data[X][Y] = value;
    }
}

int Image::getPixel(int X, int Y){
    return data[X][Y];
}

void Image::setData(vector<vector<int> > & data){
    this->data = data;
}

double Image::correlation(int i, int j, vector<vector<double> > & M){
    double result = 0;

    for (int k = -1; k <= 1; k++){
        for (int l = -1; l <= 1; l++) {
            if (isValid(i+k, j+l)){
                result += M[k+1][l+1] * data[i+k][j+l];
            }
        }
    }

    return result;
}

ImageGS::ImageGS(int X, int Y, vector<vector<int>> data, int colorDepth) : Image(X, Y, data){
    this->colorDepth = colorDepth;
}

/**
 * Calcula P(r) para cada pixel da imagem
 * @return vector<double> com P(r)
 */ 
vector<double> ImageGS::getHistogramValues(){
	vector<double> hist(this->colorDepth, 0);

	for (int i = 0; i < this->getHeight(); i++) {
		for (int j = 0; j < this->getWidth(); j++) {
			int value = this->data[i][j];
			hist[value]++;
		}
	}

	double totalSize = this->getHeight() * this->getWidth();
	for (int i = 0; i < hist.size(); i++)
		hist[i] /= totalSize;

	return hist;
}

void ImageGS::equalizeHistogram(){
    vector<double> histogram = getHistogramValues();
    vector<int> mapPixels;

    double prob = 0;
    for (int i = 0; i < histogram.size(); i++){
        prob += histogram[i];
        mapPixels.push_back((int)round(prob*(colorDepth-1)));
    }

	for (int i = 0; i < this->getHeight(); i++) {
		for (int j = 0; j < this->getWidth(); j++) {
			int value = this->data[i][j];
            this->data[i][j] = mapPixels[value];
        }
    }
}

int ImageGS::getColorDepth(){
    return this->colorDepth;
}

void ImageGS::setColorDepth(int colorDepth){
    this->colorDepth = colorDepth;
}

ImageBW::ImageBW(int X, int Y, vector<vector<int> > data) : Image(X, Y, data){}

void ImageGS::draw(WorkSpace * work){
    //TO DO
}

void ImageBW::draw(WorkSpace * work){
    //TO DO
}
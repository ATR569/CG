﻿//---------------------------------------------------------------------------

#pragma hdrstop

#include "image.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

#include "workspace.h"
#include "graphics.h"
#include <fstream>

bool Image::isValid(int i, int j){
    if (i < 0 || i >= getHeight()) return false;
    if (j < 0 || j >= getWidth()) return false;
    return true;
}

Image::Image(vector<vector<int> > data){
    this->data = data;
}

ImageGS::ImageGS(String filePath) : Image(vector<vector<int>>()){
	ifstream file(filePath.c_str());

	string format;
	int height, width;

	file >> format;             //  ASCII ou binário
	file >> height >> width;    //  Tamanho da imagem
	file >> this->colorDepth; 	//  Níves de cinza

	//  Leitura dos pixels da imagem
	for (int X = 0; X < height; X++){
		this->data.push_back(vector<int>());
		int pixelValue;
		for (int Y = 0; Y < width; Y++){
			file >> pixelValue;
			this->data[X].push_back(pixelValue);
		}
	}

    file.close();
}

vector<vector<int>> Image::getData(){
    return this->data;
}

vector<int> Image::getLine(int i){
    return this->data[i];
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

double Image::correlation(int X, int Y, vector<vector<double> > & M){
    double result = 0;

    for (int i = -1; i <= 1; i++){
        for (int j = -1; j <= 1; j++) {
            if (isValid(X+i, Y+j)){
                result += M[i+1][j+1] * data[X+i][Y+j];
            }
        }
    }

    return result;
}

ImageGS::ImageGS(vector<vector<int>> data, int colorDepth) : Image(data){
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

ImageBW::ImageBW(vector<vector<int> > data) : Image(data){}

void ImageGS::draw(HDC hdc, int X, int Y){
    drawImageGS(hdc, X, Y, this->data);
}

void ImageBW::draw(HDC hdc, int X, int Y){
    drawImageBW(hdc, X, Y, this->data);
}
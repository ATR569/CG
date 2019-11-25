//---------------------------------------------------------------------------

#pragma hdrstop

#include "image.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

//#include "./workspace.h"

bool Image::isValid(int i, int j){
    if (i < 0 || i >= getHeight()) return false;
    if (j < 0 || j >= getWidth()) return false;
    return true;
}

Image::Image(int X, int Y, vector<vector<int>> data){
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

void Image::setData(vector<vector<int>> & data){
    this->data = data;
}

double Image::correlation(int i, int j, vector<vector<double>> & M){
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

ImageGS::ImageGS(int X, int Y, vector<vector<int>> data) : Image(X, Y, data){}

ImageBW::ImageBW(int X, int Y, vector<vector<int>> data) : Image(X, Y, data){}

void ImageGS::draw(WorkSpace * work){
    //TO DO
}

void ImageBW::draw(WorkSpace * work){
    //TO DO
}
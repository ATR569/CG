#ifndef imageH
#define imageH

#include <vector>
#include <System.Classes.hpp>

#include <windows.h>

using namespace std;

class Image{
protected:
    vector<vector<int> > data;

    vector<int> getLine(int i);
    bool isValid(int i, int j);
public:
    Image(vector<vector<int> > data);
    
    virtual void draw(HDC hdc, int X, int Y) = 0;

    vector<vector<int> > getData();

    int getHeight();
    int getWidth();
    void setPixel(int X, int Y, int value);
    int getPixel(int X, int Y);
    void setData(vector<vector<int> > & data);
    double correlation(int X, int Y, vector<vector<double> > & M);
};

class ImageGS : public Image{
    int colorDepth;
public:
    ImageGS(vector<vector<int>> data, int colorDepth);
    ImageGS(String filePath);
    int getColorDepth();
    void setColorDepth(int colorDepth);
    vector<double> getHistogramValues();
    void equalizeHistogram();
    
    void draw(HDC hdc, int X, int Y);
};

class ImageBW : public Image{
public:
    ImageBW(vector<vector<int> > data);
    void draw(HDC hdc, int X, int Y);
};

#endif
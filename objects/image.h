#ifndef imageH
#define imageH

#include <vector>
#include <System.Classes.hpp>

#include <windows.h>

using namespace std;

class Image{
protected:
    int colorDepth;
    vector<vector<int> > data;
    vector<int> getLine(int i);

public:
    void setDynamicRange(int fmin, int fmax, int target);
    void itfSigmoid(double sigma);
    void itfLog(double a);
    void linearTransform(double a, double b);

    Image(vector<vector<int> > data);
    
    virtual void negative();
    virtual void draw(HDC hdc, int X, int Y) = 0;

    vector<vector<int> > getData();

    int getColorDepth();
    void setColorDepth(int colorDepth);
    int getHeight();
    int getWidth();
    void setPixel(int X, int Y, int value);
    int getPixel(int X, int Y);
    void setData(vector<vector<int> > & data);

    bool isValid(int i, int j);
    double correlation(int X, int Y, vector<vector<double> > & M);
};

class ImageGS : public Image{
public:
    ImageGS(vector<vector<int>> data, int colorDepth);
    ImageGS(String filePath);
    vector<double> getHistogramValues();
    void equalizeHistogram();
    
    void draw(HDC hdc, int X, int Y);
};

class ImageBW : public Image{
public:
    ImageBW(String filePath);
    ImageBW(vector<vector<int> > data);
    
    void draw(HDC hdc, int X, int Y);
};

#endif
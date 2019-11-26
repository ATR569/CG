#ifndef imageH
#define imageH

#include <vector>
#include <windows.h>

using namespace std;

class WorkSpace;

class Image{
    int X;
    int Y;
    vector<vector<int> > data;

public:
    bool isValid(int i, int j);
    Image(int X, int Y, vector<vector<int> > data);
    
    virtual void draw(WorkSpace * work) = 0;

    vector<vector<int> > getData();
    vector<int> getLine(int i);

    int getX();
    int getY();
    int getHeight();
    int getWidth();
    void setPixel(int X, int Y, int value);
    int getPixel(int X, int Y);
    void setData(vector<vector<int> > & data);
    double correlation(int i, int j, vector<vector<double> > & M);
};

class ImageGS : public Image{
public:
    ImageGS(int X, int Y, vector<vector<int> > data);
    void draw(WorkSpace * work);
};

class ImageBW : public Image{
public:
    ImageBW(int X, int Y, vector<vector<int> > data);
    void draw(WorkSpace * work);
};

#endif
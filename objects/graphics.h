#ifndef graphicsH
#define graphicsH

#include <windows.h>
#include <algorithm>
#include <math.h>

class Point2D;

typedef unsigned DrawColor;

const DrawColor CL_WHITE = RGB(255,255,255);
const DrawColor CL_LIGHTGREY = RGB(230,230,230);
const DrawColor CL_GREY = RGB(200,200,200);
const DrawColor CL_BLACK = RGB(0,0,0);
const DrawColor CL_BLUE = RGB(0,128,255);

using namespace std;

void printAxis(HDC & hdc, int width, int height, DrawColor color);

void drawGrid(HDC & hdc, double canvasH, double canvasV, double userH, double userV, DrawColor color);

void drawLineBresenhan(HDC & hdc, Point2D * p1, Point2D * p2, DrawColor color);

void drawLineDDA(HDC & hdc, Point2D * p1, Point2D * p2, DrawColor color);

void circlePoints(HDC & hdc, double X, double Y, Point2D * center, DrawColor color, bool oct = false);

void drawCircleBresenhan(HDC & hdc, Point2D * center, double radius, DrawColor color);

void drawCirclePolynomial(HDC & hdc, Point2D * center, double radius, DrawColor color);

void drawCircleTrigonometric(HDC & hdc, Point2D * center, double radius, DrawColor color);

void drawPoint(HDC & hdc, Point2D * P, DrawColor color);

#endif

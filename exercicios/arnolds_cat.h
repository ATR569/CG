#ifndef arnolds_catH
#define arnolds_catH

#include <windows.h>

class ImageGS;
class ImageBW;

int arnoldsCatTransform(HDC hdc, int X, int Y, ImageBW * image);

int arnoldsCatTransform(HDC hdc, int X, int Y, ImageGS * image);

#endif

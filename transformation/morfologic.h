#ifndef mofologicH
#define mofologicH

#include "../objects/image.h"

enum MorfOperation{DILATION, EROSION};
enum BorderOperation{INNER, EXTERNAL};

void morfologicBW(ImageBW * image, MorfOperation mo);

void openingBW(ImageBW * image);

void closureBW(ImageBW * image);

void extractionBorders(ImageBW * image, BorderOperation bp);

void gradientBW(ImageBW * image);

void morfologicGS(ImageGS * image);

int getTruncatedValue(int nv);

bool isValid(int i, int j, vector<vector<int>> & M);

#endif
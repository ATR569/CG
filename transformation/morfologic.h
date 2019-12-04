#ifndef mofologicH
#define mofologicH

#include "../objects/image.h"

enum MorfOperation{DILATION, EROSION};
enum BorderOperation{INNER, EXTERNAL};

void morfologicBW(ImageBW * image, MorfOperation mo, vector<vector<int>> & M);

void openingBW(ImageBW * image, vector<vector<int>> & M);

void closureBW(ImageBW * image, vector<vector<int>> & M);

void extractionBordersBW(ImageBW * image, BorderOperation bp, vector<vector<int>> & M);

void gradientBW(ImageBW * image, vector<vector<int>> & M);

void hitMiss(ImageBW * image);

#endif
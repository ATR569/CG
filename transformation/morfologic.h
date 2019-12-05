#ifndef morfologicH
#define morfologicH

#include <vector>
#include <algorithm>

class ImageBW;
class ImageGS;
class Image;

enum MorfOperation{DILATION, EROSION};
enum BorderOperation{INNER, EXTERNAL};

void morfologicBW(ImageBW * image, MorfOperation mo, std::vector<std::vector<int>> & M);

void openingBW(ImageBW * image, std::vector<std::vector<int>> & M);

void closureBW(ImageBW * image, std::vector<std::vector<int>> & M);

void extractionBordersBW(ImageBW * image, BorderOperation bp, std::vector<std::vector<int>> & M);

void gradientBW(ImageBW * image, std::vector<std::vector<int>> & M);

void hitMiss(ImageBW * image, std::vector<std::vector<int>> & M, std::vector<std::vector<int>> & M2);

void morfologicGS(ImageGS * image, MorfOperation mo, std::vector<std::vector<int>> & M);

void openingGS(ImageGS * image, std::vector<std::vector<int>> & M);

void closureGS(ImageGS * image, std::vector<std::vector<int>> & M);

void gradientGS(ImageGS * image, std::vector<std::vector<int>> & M);

void topHat(ImageGS * image, std::vector<std::vector<int>> & M);

void bottomHat(ImageGS * image, std::vector<std::vector<int>> & M);

#endif
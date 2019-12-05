#ifndef morfologicH
#define morfologicH

#include <vector>

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

void hitMiss(ImageBW * image);

#endif
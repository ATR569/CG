#ifndef filtersH
#define filtersH

using namespace std;

class ImageGS;

void meanFilter(ImageGS *image);

void medianFilter(ImageGS *image);

void HighPassFilter(ImageGS *image);

void RobertsFilter(ImageGS *image);

void RobertsCrossedFilter(ImageGS *image);

void PrewittFilter(ImageGS *image);

void HighBoostFilter(ImageGS *image, double A);

void SobelFilter(ImageGS *image);

#endif
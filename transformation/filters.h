#ifndef filtersH
#define filtersH

class ImageGS;

void meanFilter(ImageGS *image);

void medianFilter(ImageGS *image);

void HighPassFilter(ImageGS *image);

void RobertsFilter(ImageGS *image);

void RobertsCrossedFilter(ImageGS *image);

void PrewittFilter(ImageGS *image);

void HighBoostFilter(ImageGS *image, double A);

void SobelFilter(ImageGS *image);

ImageGS * opAND(ImageGS *image1, ImageGS *image2);

ImageGS * opOR(ImageGS *image1, ImageGS *image2);

ImageGS * opXOR(ImageGS *image1, ImageGS *image2);

#endif
//---------------------------------------------------------------------------

#pragma hdrstop

#include "arnolds_cat.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

#include "../objects/image.h"

bool isEqual(Image * image, Image * image2){
	for(int i = 0; i < image->getHeight(); i++){
		for(int j = 0; j < image->getHeight(); j++){
			if(image->getPixel(i,j) != image2->getPixel(i,j)) return false;
		}
	}

	return true;
}

int arnoldsCatTransform(HDC hdc, int X, int Y, Image * image, Image * img[2]){
	int iter = 0, height, width;

	height = image->getHeight();
	width = image->getWidth();

	int atual = 0;

	do {
		img[atual]->draw(hdc, X, Y);
		iter++;
		for(int i = 0; i < height; i++){
			for(int j = 0; j < width; j++){
				int a = (i + j) % height;
				int b = (i + ( 2 * j) ) % width;
				img[!atual]->setPixel(a, b, img[atual]->getPixel(i, j));
			}
		}
		atual = !atual;
	}while(!isEqual(image, img[atual]));

	img[atual]->draw(hdc, X, Y);

	return iter;
}

int arnoldsCatTransform(HDC hdc, int X, int Y, ImageGS *image){
	Image * img[2];
	img[0] = new ImageGS(image->getData(), image->getColorDepth());
	img[1] = new ImageGS(image->getData(), image->getColorDepth());

	return arnoldsCatTransform(hdc, X, Y, image, img);
}

int arnoldsCatTransform(HDC hdc, int X, int Y, ImageBW *image){
	Image * img[2];
	img[0] = new ImageBW(image->getData());
	img[1] = new ImageBW(image->getData());

	return arnoldsCatTransform(hdc, X, Y, image, img);
}





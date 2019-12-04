//---------------------------------------------------------------------------

#pragma hdrstop

#include "arnolds_cat.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

int transform(HDC &hdc, int X, int Y, ImageBW *image){
    ImageBW * img[2];
    img[0] = new ImageBW(image->getData());
    img[1] = new ImageBW(image->getData());

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

bool isEqual(ImageBW * image, ImageBW * image2){
    for(int i = 0; i < image->getHeight(); i++){
        for(int j = 0; j < image->getHeight(); j++){
            if(image->getPixel(i,j) != image2->getPixel(i,j)) return false;
        }
    }

    return true;
}

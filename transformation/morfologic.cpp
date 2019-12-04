#include "morfologic.h"

// Morfologia em imagens binárias
// ----------------------------------------------------------------------------------------------------------------

/** Método que realiza as operações de dilatação ou erosão
 *  de acordo com parâmetro especificado pelo usúario
 *
 * @image ImageBW - imagem binária que irá sofrer a operação de dilatação ou erosão
 * @mo MorfOperation - valor que define se a operação será de dilatação ou erosão
*/
void morfologicBW(ImageBW * image, MorfOperation mo, vector<vector<int>> & M){
    vector<vector<int>> data = image->getData();

    //  Iterando pixel a pixel da imagem
    for (int i = 0; i < data.size(); i++) {
        for (int j = 0; j < data[i].size(); j++) {
            //  Iterando no elemento estruturante
            for (int k = -1; k <= 1; k++) {
                for (int l = -1; l <= 1; l++) {
                    int value = image->getPixel(i,j);
                    int value2 = image->isValid(i+k, j+l) ? (data[i+k][j+l] && M[k+1][l+1]) : 0; 

                    if (mo == DILATION)
                        image->setPixel(i, j, value || value2); 
                    else
                        image->setPixel(i, j, value && value2); 
                    
                }
            }
        }
    }
}

/** Método que realiza a operação de abertura em uma imagem
*
* @image ImageBW - imagem binária que irá sofrer a operação de abertura
*/
void openingBW(ImageBW * image, vector<vector<int>> & M){
    morfologicBW(image, EROSION, M);
    morfologicBW(image, DILATION, M);
}

/** Método que realiza a operação de fechamento em uma imagem
*
* @image ImageBW - imagem binária que irá sofrer a operação de fechamento
*/
void closureBW(ImageBW * image, vector<vector<int>> & M){
    morfologicBW(image, DILATION, M);
    morfologicBW(image, EROSION, M);
}

/** A função realiza as operações necessárias para extrações de fronteira, seja 
 *  ela interna ou externa
 *
 * @image ImageBW - imagem binária que terá elementos extraidos
 * @bp BorderOperation - valor que define se a fronteira extraida sera interna ou externa.
 *
*/
void extractionBordersBW(ImageBW * image, BorderOperation bp, vector<vector<int>> & M){
    vector<vector<int>> data = image->getData(); // guarda uma cópia da imagem original
    vector<vector<int>> data2; // guarda a matriz da imagem após a dilatação ou erosão
    if(bp == INNER)
        morfologicBW(image, EROSION, M); // erosão da imagem original
    else
        morfologicBW(image, DILATION, M); // dilatação da imagem original

    data2 = image->getData(); // variavel recebe a imagem original após a dilatação ou erosão

    for (int i = 0; i < data.size(); i++) {
        for (int j = 0; j < data[i].size(); j++) {
            if(bp == INNER)
                image->setPixel(i, j, data[i][j] && !data2[i][j]); // é feito a operação da (imagem orignal - a imagem erodida)
            else
                image->setPixel(i, j, data2[i][j] && !data[i][j]); // é feito a operação da (imagem dilatada - imagem original)
        }
    }
}

/** Realiza a operação de gradiente morfológico em uma imagem binária
 *
 * @image ImageBW - imagem binária que terá o grandiente extraido
*/
void gradientBW(ImageBW * image, vector<vector<int>> & M){
    vector<vector<int>> data = image->getData(); // guarda uma cópia da imagem original
    ImageBW * copyImage = new ImageBW(data); // guarda uma cópia da image original para usar na operação de erosão
    vector<vector<int>> erosion; // guarda a referencia para a imagem após a erosão
    vector<vector<int>> dilation; // guarda a referencia para a imagem após a erosão

    morfologicBW(image, DILATION, M); // operação de dilatação
    dilation = image->getData(); // variavel dilation guarda a imagem dilatada

    morfologicBW(copyImage, EROSION, M); // operação de erosão
    erosion = copyImage->getData(); // variavel erosion guarda a imagem erodida


    for (int i = 0; i < data.size(); i++){
        for (int j = 0; j < data[i].size(); j++){
            image->setPixel(i, j, dilation[i][j] && !erosion[i][j]);
        }
    }
}

void hitMiss(ImageBW * image, vector<vector<int>> & M, vector<vector<int>> & M2){
    vector<vector<int>> data = image->getData(); // guarda uma cópia da imagem original
    ImageBW * imageCopy = new ImageBW(data); // imagem que irá sofrer erosão
    ImageBW * imageC; // complemento da imagem original
    vector<vector<int>> imageCop; // matriz de pixels da imagem original apos erosão
    vector<vector<int>> imageComp; // matriz de pixels do complementar da imagem apois erosão

    for (int i = 0; i < data.size(); i++){
        for (int j = 0; j < data[i].size(); j++){
            imageC->setPixel(i, j, !data[i][j]);
        }
    }
    
    morfologicBW(imageCopy, EROSION, M);
    morfologicBW(imageC, EROSION, M2);

    imageCop = imageCopy->getData();
    imageComp = imageC->getData();

    for (int i = 0; i < data.size(); i++){
        for (int j = 0; j < data[i].size(); j++) {
            image->setPixel(i, j, imageCop[i][j] && imageComp[i][j]);
        }
    }
}


// Morfologia em nível de cinza
// ----------------------------------------------------------------------------------------------------------------



#include "morfologic.h"

/** Método que realiza as operações de dilatação ou erosão
 *  de acordo com parâmetro especificado pelo usúario
 *
 * @image ImageBW - imagem binária que irá sofrer a operação de dilatação ou erosão
 * @mo MorfOperation - valor que define se a operação será de dilatação ou erosão
*/
void morfologicBW(ImageBW * image, MorfOperation mo){
    vector<vector<int>> data = image->getData();
    vector<vector<int>> M {
        {1,1,1},
        {1,1,1},
        {1,1,1}
    };

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
void openingBW(ImageBW * image){
    morfologicBW(image, EROSION);
    morfologicBW(image, DILATION);
}

/** Método que realiza a operação de fechamento em uma imagem
*
* @image ImageBW - imagem binária que irá sofrer a operação de fechamento
*/
void closureBW(ImageBW * image){
    morfologicBW(image, DILATION);
    morfologicBW(image, EROSION);
}

/** A função realiza as operações necessárias para extrações de fronteira, seja 
 *  ela interna ou externa
 *
 * @image ImageBW - imagem binária que terá elementos extraidos
 * @bp BorderOperation - valor que define se a fronteira extraida sera interna ou externa.
 *
*/
void extractionBorders(ImageBW * image, BorderOperation bp){
    vector<vector<int>> data = image->getData(); // guarda uma cópia da imagem original
    vector<vector<int>> data2; // guarda a matriz da imagem após a dilatação ou erosão
    if(bp == INNER)
        morfologicBW(image, EROSION); // erosão da imagem original
    else
        morfologicBW(image, DILATION); // dilatação da imagem original

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
void gradientBW(ImageBW * image){
    vector<vector<int>> data = image->getData(); // guarda uma cópia da image original
    ImageBW * copyImage = new ImageBW(0, 0, data); // guarda uma cópia da image original para usar na operação de erosão
    vector<vector<int>> erosion; // guarda a referencia para a imagem após a erosão
    vector<vector<int>> dilation; // guarda a referencia para a imagem após a erosão

    morfologicBW(image, DILATION); // operação de dilatação
    dilation = image->getData(); // variavel dilation guarda a imagem dilatada

    morfologicBW(copyImage, EROSION); // operação de erosão
    erosion = copyImage->getData(); // variavel erosion guarda a imagem erodida


    for (int i = 0; i < data.size(); i++){
        for (int j = 0; j < data[i].size(); j++){
            image->setPixel(i, j, dilation[i][j] && !erosion[i][j]);
        }
    }
}

// Morfologia em nível de cinza
// ----------------------------------------------------------------------------------------------------------------

int getTruncatedValue(int nv){
    return (int) round(max(0, min(nv, 255)));
}

bool isValid(int i, int j, vector<vector<int>> & M){
    if (i < 0 || i >= M.size()) return false;
    if (j < 0 || j >= M[0].size()) return false;
    return true;
}

void morfologicGS(ImageGS * image){
    vector<vector<int>> data = image->getData();
    vector<vector<int>> M {
        {1,1,1},
        {1,1,1},
        {1,1,1}
    };
}



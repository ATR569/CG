#include <iostream>
#include <math.h>
#include "../objects/image.cpp"

using namespace std;

void meanFilter(ImageGS * image){
    vector<vector<int>> data = image->getData();

    vector<vector<double>> M = {
        {1,1,1},
        {1,1,1},
        {1,1,1}
    };

    for (int i = 0; i < data.size(); i++)  {
        for (int j = 0; j < data[i].size(); j++) {
            double mean = image->correlation(i, j, M)/9;
            data[i][j] = (int)round(mean);
        }
    }

    image->setData(data);
}


enum MorfOperation{dilatacao, erosao};

void morfologic(Image * image, MorfOperation mo){
    vector<vector<int>> data = image->getData();
    vector<vector<int>> M {
        {1,1,1},
        {1,1,1},
        {1,1,1}
    };

    //  Dilatação
    //  Iterando pixel a pixel da imagem
    for (int i = 0; i < data.size(); i++) {
        for (int j = 0; j < data[i].size(); j++) {
            //  Iterando no elemento estruturante
            for (int k = -1; k <= 1; k++) {
                for (int l = -1; l <= 1; l++) {
                    if (image->isValid(i+k, j+l)){
                        int value = image->getPixel(i,j);

                        if (mo == dilatacao)
                            image->setPixel(i, j, value || (data[i+k][j+l] && M[k+1][l+1])); 
                        else
                            image->setPixel(i, j, value && (data[i+k][j+l] && M[k+1][l+1])); 
                    }
                }
            }
        }
    }
}

int main(){
    vector<vector<int>> data = {
        {10,25,30},
        {13,12,60},
        {25,25,120}
    };

    ImageGS * image = new ImageGS(0, 0, data);
    
    meanFilter(image);
    
    vector<vector<int>> data1 = image->getData();
    

    for (int i = 0; i < data1.size(); i++) {
        for (int j = 0; j < data1[i].size(); j++) {
            cout << data1[i][j] << " ";
        }
        cout << endl;
    }

    cout << "dilatacao\n";

    vector<vector<int>> data2 = {
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,1,0,0,0,0},
        {0,0,1,1,1,0,1,1,1,0,0,0},
        {0,0,1,1,1,0,1,1,1,0,0,0},
        {0,0,1,1,1,1,1,1,1,0,0,0},
        {0,0,0,0,1,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0}
    };

    ImageGS * image2 = new ImageGS(0, 0, data2);
    dilatacao(image2);

    data1 = image2->getData();
    

    for (int i = 0; i < data1.size(); i++) {
        for (int j = 0; j < data1[i].size(); j++) {
            cout << data1[i][j] << " ";
        }
        cout << endl;
    }

    
    return 0;
}

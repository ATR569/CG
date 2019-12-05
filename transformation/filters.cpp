//---------------------------------------------------------------------------

#pragma hdrstop

#include "filters.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

#include <algorithm>
#include <math.h>
#include "../objects/image.h"

int getTruncatedValue(double nv){
	return (int) round(max(0.0, min(nv, 255.0)));
}

bool isValid(int i, int j, vector<vector<int>> & M){
    if (i < 0 || i >= M.size()) return false;
    if (j < 0 || j >= M[0].size()) return false;
    return true;
}

double getMedianValue(int i, int j, vector<vector<int>> & M){
    double result = 0;
    vector<int> values;

    for (int k = -1; k <= 1; k++){
        for (int l = -1; l <= 1; l++) {
            if (isValid(i+k, j+l, M)){
                values.push_back(M[i+k][j+l]);
            }else{
                values.push_back(0);
            }
        }
    }

    sort(values.begin(), values.end());

    return values[values.size() / 2];
}

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
			data[i][j] = getTruncatedValue(mean);
            image->setPixel(i, j, getTruncatedValue(mean));
        }
    }

    image->setData(data);
}

void medianFilter(ImageGS * image){
    vector<vector<int>> data = image->getData();
    vector<vector<int>> median = image->getData();

    for (int i = 0; i < data.size(); i++)  {
        for (int j = 0; j < data[i].size(); j++) {
            median[i][j] = getTruncatedValue(getMedianValue(i, j, data));
        }
    }

    image->setData(median);
}

void HighPassFilter(ImageGS * image){
    vector<vector<int>> data = image->getData();

    vector<vector<double>> M = {
        {-1, -1, -1},
        {-1,  8, -1},
        {-1, -1, -1}
    };

    for (int i = 0; i < data.size(); i++)  {
        for (int j = 0; j < data[i].size(); j++) {
            double mean = image->correlation(i, j, M);
            data[i][j] = getTruncatedValue(mean);
        }
    }

    image->setData(data);
}

void RobertsFilter(ImageGS * image){
    vector<vector<int>> data = image->getData();
    vector<vector<int>> data2 = image->getData();

    vector<vector<double>> MX = {
        {0,  0, 0},
        {0,  1, 0},
        {0, -1, 0}
    };

    vector<vector<double>> MY = {
        {0,  0,  0},
        {0,  1, -1},
        {0,  0,  0}
    };

    for (int i = 0; i < data.size(); i++)  {
        for (int j = 0; j < data[i].size(); j++) {
            double mean = image->correlation(i, j, MX);
            data[i][j] = abs((int)round(mean));
        }
    }

    for (int i = 0; i < data.size(); i++)  {
        for (int j = 0; j < data[i].size(); j++) {
            double mean = image->correlation(i, j, MY);
            data2[i][j] = abs((int)round(mean));
        }
    }  

    for (int i = 0; i < data.size(); i++)  {
        for (int j = 0; j < data[i].size(); j++) {
            data[i][j] = getTruncatedValue(data[i][j] + data2[i][j]);
        }
    }         

    image->setData(data);
}

void RobertsCrossedFilter(ImageGS * image){
    vector<vector<int>> data = image->getData();
    vector<vector<int>> data2 = image->getData();

    vector<vector<double>> MX = {
        {0,  0,  0},
        {0,  1,  0},
        {0,  0, -1}
    };

    vector<vector<double>> MY = {
        {0,  0,  0},
        {0,  0,  1},
        {0, -1,  0}
    };

    for (int i = 0; i < data.size(); i++)  {
        for (int j = 0; j < data[i].size(); j++) {
            double mean = image->correlation(i, j, MX);
            data[i][j] = abs((int)round(mean));
        }
    }

    for (int i = 0; i < data.size(); i++)  {
        for (int j = 0; j < data[i].size(); j++) {
            double mean = image->correlation(i, j, MY);
            data2[i][j] = abs((int)round(mean));
        }
    }  

    for (int i = 0; i < data.size(); i++)  {
        for (int j = 0; j < data[i].size(); j++) {
            data[i][j] = getTruncatedValue(data[i][j] + data2[i][j]);
        }
    }         

    image->setData(data);
}

void PrewittFilter(ImageGS * image){
    vector<vector<int>> data = image->getData();
    vector<vector<int>> data2 = image->getData();

    vector<vector<double>> MX = {
        {-1, -1, -1},
        {0,   0,  0},
        {1,   1,  1}
    };

    vector<vector<double>> MY = {
        {-1,  0,  1},
        {-1,  0,  1},
        {-1,  0,  1}
    };

    for (int i = 0; i < data.size(); i++)  {
        for (int j = 0; j < data[i].size(); j++) {
            double mean = image->correlation(i, j, MX);
            data[i][j] = abs((int)round(mean));
        }
    }

    for (int i = 0; i < data.size(); i++)  {
        for (int j = 0; j < data[i].size(); j++) {
            double mean = image->correlation(i, j, MY);
            data2[i][j] = abs((int)round(mean));
        }
    }  

    for (int i = 0; i < data.size(); i++)  {
        for (int j = 0; j < data[i].size(); j++) {
            data[i][j] = getTruncatedValue(data[i][j] + data2[i][j]);
        }
    }         

    image->setData(data);
}

void HighBoostFilter(ImageGS * image, double A){
    vector<vector<int>> data = image->getData();

    meanFilter(image);

    vector<vector<int>> dataMean = image->getData();
    
    for (int i = 0; i < dataMean.size(); i++) {
        for (int j = 0; j < dataMean[i].size(); j++) {
            dataMean[i][j] = (data[i][j] - dataMean[i][j]) * A; // A * g_mascara
            data[i][j] = getTruncatedValue(data[i][j] + dataMean[i][j]);
        }
    }    

    image->setData(data);    
}

void SobelFilter(ImageGS * image){
    vector<vector<int>> data = image->getData();
    vector<vector<int>> data2 = image->getData();

    vector<vector<double>> MX = {
        {-1, -2, -1},
        {0,   0,  0},
        {1,   2,  1}
    };

    vector<vector<double>> MY = {
        {-1,  0,  1},
        {-2,  0,  2},
        {-1,  0,  1}
    };

    for (int i = 0; i < data.size(); i++)  {
        for (int j = 0; j < data[i].size(); j++) {
            double mean = image->correlation(i, j, MX);
            data[i][j] = abs((int)round(mean));
        }
    }

    for (int i = 0; i < data.size(); i++)  {
        for (int j = 0; j < data[i].size(); j++) {
            double mean = image->correlation(i, j, MY);
            data2[i][j] = abs((int)round(mean));
        }
    }  

    for (int i = 0; i < data.size(); i++)  {
        for (int j = 0; j < data[i].size(); j++) {
            data[i][j] = (data[i][j] + data2[i][j]);
        }
    }         

    image->setData(data);
}
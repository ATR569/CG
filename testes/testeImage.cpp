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
    
    return 0;
}

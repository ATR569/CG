#include <iostream>
#include <math.h>
#include "../objects/image.cpp"
#include "morfologic.cpp"

using namespace std;

int main()
{

    vector<vector<int>> data = {
        {1, 1, 1, 0, 1, 1, 1, 1, 1, 0},
        {1, 1, 1, 0, 1, 1, 1, 1, 1, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };

    vector<vector<int>> data2 = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0},
        {0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0},
        {0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };

    ImageBW * image = new ImageBW(0, 0, data);
    ImageBW * image2 = new ImageBW(0, 0, data2);
    ImageBW * copy = new ImageBW(0, 0, data2);

    gradientBW(image2);

    vector<vector<int>> data1 = image2->getData();


    cout << "Gradiente\n\n";
    for (int i = 0; i < data1.size(); i++)
    {
        for (int j = 0; j < data1[i].size(); j++)
        {
            cout << data1[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl;

    morfologicBW(copy, DILATION);
    vector<vector<int>> data3 = copy->getData();

    cout << "Dilatacao\n\n";
    for (int i = 0; i < data3.size(); i++)
    {
        for (int j = 0; j < data3[i].size(); j++)
        {
            cout << data3[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
#include <iostream>
#include <math.h>
#include "../objects/point2D.cpp"
#include "../transformation/transform2D.cpp"
#include "../objects/matrix.cpp"
#include "../objects/object.cpp"

using namespace std;

int main(){
	double x1, x2, y1, y2;
    int xmax, xmin, ymax, ymin;
    cout << "Coordenadas do ponto 1 (X, Y): ";
    cin >> x1 >> y1;
    cout << "Coordenadas do ponto 2 (X, Y): ";
    cin >> x2 >> y2;
    cout << "Xmin: ";
    cin >> xmin;
    cout << "Xmax: ";
    cin >> xmax;
    cout << "Ymin: ";
    cin >> ymin;
    cout << "Ymax: ";
    cin >> ymax;
    Point2D * p1 = new Point2D(x1,y1);
	Point2D * p2 = new Point2D(x2,y2);

	if (cut(p1, p2, xmin,xmax,ymin,ymax)){
        cout << "Aceita!" << endl;
        cout << p1->X <<", "<<p1->Y<<endl;
        cout << p2->X <<", "<<p2->Y<<endl;
    }else{
        cout << "Rejeitada!";
    }

    return 0;
}



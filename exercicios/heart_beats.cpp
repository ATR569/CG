//---------------------------------------------------------------------------

#pragma hdrstop

#include "heart_beats.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

#include "../cglib.h"
#include <cstdlib>
#include <windows.h>

void executarBatimentos(WorkSpace * work){
    Point2D * p[2];
    double sizeCanvasV = work->getCanvasV()/2;
    int sizeCanvasH = work->getCanvasH();

    p[0] = new Point2D(0, sizeCanvasV);
	p[1] = new Point2D(5, sizeCanvasV);

    int current = 1;

	double newX = 0, newY = 0, posCurrentY;

    for(int i = 10; i < sizeCanvasH; i+=5){
        Sleep(10);
        drawLineBresenhan(work->hdc, p[!current], p[current], CL_BLACK);
        int r = rand() % 81 + 20; // 20 até 100
        int r2 = rand() % 2 + 0; // 0 ou 1
        int r3 = rand() % 2 - 1; // -1 ou 0
        int r4 = rand() % 3 - 1; // -1 até 1

        newX = i;
        newY = sizeCanvasV;

        posCurrentY = p[current]->Y;

        if(posCurrentY > sizeCanvasV){
            newY += (r * r3);
        }else if(posCurrentY < sizeCanvasV){
            newY += (r * r2);
        }else{
            newY += (r * r4);
        }

        p[!current]->X = newX;
        p[!current]->Y = newY;
        current = !current;
    }
}

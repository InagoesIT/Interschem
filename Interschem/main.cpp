#include <iostream>
#include <graphics.h>
#include <winbgim.h>
#include <cmath>
#include "blocks.h"


int main()
{
    initwindow(800,600);
    createStart();
    createStop();
    createIn();
    createOut();
    createAssign();
    createDecision();

    //testing

//    int xx, yy;
//    while (!ismouseclick(WM_LBUTTONDOWN))
//        delay(500);
//    getmouseclick(WM_LBUTTONDOWN, xx, yy);
//    node * p = new node;
//    selectCorrectNode(xx, yy, p);
//    cout<<xx<<' '<<yy<<'\n';
//    writeNode(p);

    getch();
    closegraph();
    return 0;
}

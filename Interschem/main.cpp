#include <iostream>
#include <graphics.h>
#include <winbgim.h>
#include <cmath>
#include "blocks.h"

int main()
{
    initwindow(800,600);
    createStart(30, 30, true);
    createStop(30, 130, true);
    createIn(30, 230, true);
    createOut(30, 310, true);
    createAssign(30, 390, true);
    createDecision(30, 480, true);

    //testing//

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

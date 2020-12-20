#include <iostream>
#include <graphics.h>
#include <winbgim.h>
#include <cmath>

#include "blocks.h"
#include "blocksMoveDel.h"

int main()
{
    initialize();
    initwindow(800,600);

//    createStart(30, 30, true);
//    createStop(30, 130, true);
//    createIn(30, 230, true);
//    createOut(30, 310, true);
//    createAssign(30, 390, true);
//    createDecision(30, 480, true);


//moving blocks//

//    createStart(30, 150, true);
//    createNode("START", false, 30, 150);
//    createStop(50, 190, true);
//    createNode("STOP", false, 50, 190);
//    createOut(30, 310, true);
//    createNode("OUT", false, 30, 310);
//
//    int xx, yy;
//    node * p = new node;
//    node * behind = new node;
//
//    while (1)
//    {
//        if (ismouseclick(WM_LBUTTONDOWN))
//        {
//            getmouseclick(WM_LBUTTONDOWN, xx, yy);
//            selectCorrectNode(xx, yy, p, behind);
//
//            if (p)
//                moveBlock(xx, yy, p);
//        }
//    }


    //testing//
//    while (!ismouseclick(WM_LBUTTONDOWN))
//        delay(500);
//    getmouseclick(WM_LBUTTONDOWN, xx, yy);
//    node * p = new node;
//    selectCorrectNode(xx, yy, p);
//    cout<<xx<<' '<<yy<<'\n';
//    writeNode(p);

//    int xx, yy;
//
//    while (!ismouseclick(WM_LBUTTONDOWN))
//        delay(500);
//    getmouseclick(WM_LBUTTONDOWN, xx, yy);
//    node * frst = new node;
//    node * sec = new node;
//    selectCorrectNode(xx, yy, frst, sec);
//    cout<<xx<<' '<<yy<<'\n';
//    writeNode(frst);

//    START->next=FREE_NODES->n[1];
//    cout<<isSchemeCorrect(START);


//    int xx, yy;
//    while (!ismouseclick(WM_LBUTTONDOWN))
//        delay(500);
//    getmouseclick(WM_LBUTTONDOWN, xx, yy);
//    node * frst = new node;
//    node * sec = new node;
//    selectCorrectNode(xx, yy, frst, sec);
//    cout<<xx<<' '<<yy<<'\n';
//    writeNode(sec);

    getch();
    closegraph();
    return 0;
}

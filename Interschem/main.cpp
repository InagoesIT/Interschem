#include <iostream>
#include <graphics.h>
#include <winbgim.h>
#include <cmath>

#include "menu.h"
#include "blocks.h"

#define WINDOWX 1200
#define WINDOWY 700
#define MENUY 70


int main()
{
    initialize();
    initwindow(WINDOWX, WINDOWY);
    drawPage();
    drawMenu();

    int xx, yy;
    node * p = new node;
    node * behind = new node;
//    POINT cursorPos;
    char newBlock[10];
    bool isFirstTime = true;
    bool isDone = false;

    while(!isDone)
    {
//        GetCursorPos(&cursorPos);
//        if (cursorPos.y <= MENUY)
//            hoverMenu(cursorPos.x, cursorPos.y);
        if (ismouseclick(WM_LBUTTONDOWN))
        {
            getmouseclick(WM_LBUTTONDOWN, xx, yy);
            clearmouseclick(WM_LBUTTONDOWN);

            if (yy <= MENUY)
                handleMenuClick(xx, yy);
            else
            {
                selectCorrectNode(xx, yy, p, behind);

                if (p)
                    moveBlock(xx, yy, p, false);


                else if (xx < DRAG_SIZE_X && yy > MENUY)
                {
                    strcpy(newBlock, selectedNewBlock(xx, yy));
                    if (strcmp(newBlock, "NO") && ((strcmp(newBlock, "START") && !isFirstTime) || (!strcmp(newBlock, "START") && isFirstTime)))
                    {
                        dragNewBlock(xx, yy, newBlock);
                        if (isFirstTime && START->wasCreated)
                            isFirstTime = false;
                    }
                }
            }
        }
    }



//testing//

//    createStart(30, 30, true, true);
//    createStop(30, 130, true, true);
//    createIn(30, 230, true, true);
//    createOut(30, 310, true, true);
//    createAssign(30, 390, true, true);
//    createDecision(30, 480, true, true);

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

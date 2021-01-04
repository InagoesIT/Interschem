#include <iostream>
#include <graphics.h>
#include <winbgim.h>
#include <cmath>
#include <fstream>

#include "menu.h"
#include "blocks.h"
#include "interpretation.h"
#include "blockOptions.h"

#define WINDOWX 1200
#define WINDOWY 700
#define MENUY 70
#define DRAG_SIZE_X 250

int main()
{
    initialize();
    initwindow(WINDOWX, WINDOWY);
    drawPage();
    drawMenu();

    int xx, yy;
    node * p = new node;
    node * behind = new node;
//    POINT cursorPos; //for the hover thingie
    char newBlock[10];
    //bool isFirstTime = true; //we are going to use START.wasCreated, because this is global and we need to change this state for empyScheme() in another header
    bool isDone = false;

    //interface for the app
    int ok=1;
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
                reinitializeAllViz();
                selectCorrectNode(xx, yy, p, behind);
                if(p)
                    moveBlock(xx, yy, p, false);
                else if (xx < DRAG_SIZE_X && yy > MENUY)
                {
                    strcpy(newBlock, selectedNewBlock(xx, yy));
                    if (strcmp(newBlock, "NO") && ((strcmp(newBlock, "START") && START->wasCreated) || (!strcmp(newBlock, "START") && !START->wasCreated)))
                    {
                        dragNewBlock(xx, yy, newBlock);
//                        if (isFirstTime)  //we are going to use START.wasCreated, because this is global and we need to change this state for empyScheme() in another header
//                            isFirstTime = false;
                    }
                }
            }
        }
        else

            if (ismouseclick(WM_RBUTTONDOWN))
            {
                getmouseclick(WM_RBUTTONDOWN, xx, yy);
                clearmouseclick(WM_RBUTTONDOWN);
                if (yy > MENUY and xx > DRAG_SIZE_X)
                {
                    reinitializeAllViz();
                    selectCorrectNode(xx, yy, p, behind);
                    reinitializeAllViz();
                    if(p)
                    {

                        int opx, opy;
                        getOptionsXY(p, opx, opy);
                        int nrOfOptions = getNrOfOptions(p);

                        if(opx + OPTIONS_WIDTH < WINDOWX-5)
                        {
                            if(opy + ONE_OPTION_HEIGHT * nrOfOptions < WINDOWY-5)
                                drawRightClickOptions(p, opx, opy, nrOfOptions);
                            else
                            {
                                int dif=opy + ONE_OPTION_HEIGHT * nrOfOptions - WINDOWY + 5;
                                opy-=dif;
                                drawRightClickOptions(p, opx, opy, nrOfOptions);
                            }
                        }
                        else
                        {
                            if(opy + ONE_OPTION_HEIGHT * nrOfOptions < WINDOWY-5)
                            {
                                opx=p->coordX-OPTIONS_WIDTH;
                                drawRightClickOptions(p, opx, opy, nrOfOptions);
                            }
                            else
                            {
                                opx=p->coordX-OPTIONS_WIDTH;
                                opy=p->coordY-ONE_OPTION_HEIGHT * nrOfOptions;
                                drawRightClickOptions(p, opx, opy, nrOfOptions);
                            }
                        }
                        int finished=0;
                        while(!finished)
                        {
                            if (ismouseclick(WM_LBUTTONDOWN))
                            {
                                getmouseclick(WM_LBUTTONDOWN, xx, yy);
                                clearmouseclick(WM_LBUTTONDOWN);
                                if(!insideOptions(xx, yy, opx, opy, nrOfOptions))
                                {
                                    closeOptions(opx, opy, nrOfOptions, finished);
                                }
                                else
                                {
                                    triggerOption(xx, yy, opx, opy, nrOfOptions, p, finished);
                                }
                            }
                            else if(ismouseclick(WM_RBUTTONDOWN))
                            {
                                getmouseclick(WM_RBUTTONDOWN, xx, yy);
                                clearmouseclick(WM_RBUTTONDOWN);
                                closeOptions(opx, opy, nrOfOptions, finished);
                            }

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

    //testing// 1.0

//    int xx, yy;
//    node * p = new node;
//    node * behind = new node;
////    POINT cursorPos; //for the hover thingie
//    char newBlock[10];
//    bool isFirstTime = true;
//    bool isDone = false;
//
//    //interface for the app
//    while(!isDone)
//    {
////        GetCursorPos(&cursorPos);
////        if (cursorPos.y <= MENUY)
////            hoverMenu(cursorPos.x, cursorPos.y);
//        if (ismouseclick(WM_LBUTTONDOWN))
//        {
//            getmouseclick(WM_LBUTTONDOWN, xx, yy);
//            clearmouseclick(WM_LBUTTONDOWN);
//
//            if (yy <= MENUY)
//                handleMenuClick(xx, yy);
//            else
//            {
//                selectCorrectNode(xx, yy, p, behind);
//
//                if (p)
//                    moveBlock(xx, yy, p, false);
//
//
//                else if (xx < DRAG_SIZE_X && yy > MENUY)
//                {
//                    strcpy(newBlock, selectedNewBlock(xx, yy));
//                    if (strcmp(newBlock, "NO") && ((strcmp(newBlock, "START") && !isFirstTime) || (!strcmp(newBlock, "START") && isFirstTime)))
//                    {
//                        dragNewBlock(xx, yy, newBlock);
//                        if (isFirstTime)
//                            isFirstTime = false;
//                    }
//                }
//            }
//        }
//    }

//TESTING 2.0 analyzeScheme(START). To modify cin>>pisica value go to interpretation.h, getVariableFromIN() and modify value.
//note: this function is not finished, dont judge it :)

    node * in = new node;
    strcpy(in->type, "IN");
    strcpy(in->expression, "pisica");
    in->nextElse=NULL;

    node * decision = new node;
    strcpy(decision->type, "DECISION");
    strcpy(decision->expression, "pisica<=29");

    node * assig = new node;
    strcpy(assig->type, "ASSIGN");
    strcpy(assig->expression, "pisica=10*pisica+1");
    assig->nextElse=NULL;

    node * out = new node;
    strcpy(out->type, "OUT");
    strcpy(out->expression, "pisica");
    out->nextElse=NULL;

    node * stop = new node;
    strcpy(stop->type, "STOP");
    stop->next=stop->nextElse=NULL;

    START->wasCreated=1;
    START->next=in;
    in->next=decision;
    decision->next=out;
    decision->nextElse=assig;
    assig->next=out;
    out->next=stop;

    analyzeScheme(START);



//TESTING 2.1 expression evaluation. To test write down below an expression in "getExpressionValue". If u want to use named variables first associate
//the name with a value in a free space in VARIABLES[]

//    char infix[20][20], postfix[20][20];
//    int elemi=0, elemp=0, value=0;
//    strcpy(VARIABLES[0].name, "pisica");
//    VARIABLES[0].value=10;
//    strcpy(VARIABLES[1].name, "altNumar");
//    VARIABLES[1].value=2;
//    getInfix("1-pisica*3+altNumar", infix, elemi);
//    for(int i=0;i<elemi;++i)
//        cout<<infix[i]<<'\n';
//    cout<<'\n';
//    getExpressionValue("1-pisica*3+altNumar", value);
//    cout<<value;


    getch();
    closegraph();
    return 0;
}

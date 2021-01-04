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
    char newBlock[10];
    bool isDone = false;

    //interface for the app//

    int ok=1;
    while(!isDone)
    {
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
                        dragNewBlock(xx, yy, newBlock);
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
                                    closeOptions(opx, opy, nrOfOptions, finished);
                                else
                                    triggerOption(xx, yy, opx, opy, nrOfOptions, p, finished);
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
    getch();
    closegraph();
    return 0;
}

//TESTING 2.0 analyzeScheme(START). To modify cin>>pisica value go to interpretation.h, getVariableFromIN() and modify value.
//note: this function is not finished, dont judge it :)

//    node * in = new node;
//    strcpy(in->type, "IN");
//    strcpy(in->expression, "pisica");
//    in->nextElse=NULL;
//
//    node * decision = new node;
//    strcpy(decision->type, "DECISION");
//    strcpy(decision->expression, "pisica<=29");
//
//    node * assig = new node;
//    strcpy(assig->type, "ASSIGN");
//    strcpy(assig->expression, "pisica=10*pisica+1");
//    assig->nextElse=NULL;
//
//    node * out = new node;
//    strcpy(out->type, "OUT");
//    strcpy(out->expression, "pisica");
//    out->nextElse=NULL;
//
//    node * stop = new node;
//    strcpy(stop->type, "STOP");
//    stop->next=stop->nextElse=NULL;
//
//    START->wasCreated=1;
//    START->next=in;
//    in->next=decision;
//    decision->next=out;
//    decision->nextElse=assig;
//    assig->next=out;
//    out->next=stop;
//
//    analyzeScheme(START);

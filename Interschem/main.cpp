#include <iostream>
#include <graphics.h>
#include <winbgim.h>
#include <conio.h>
#include <cmath>
#include <fstream>

#include "menu.h"
#include "blocks.h"
#include "interpretation.h"
#include "blockOptions.h"
#include "generateCode.h"

#define WINDOWX GetSystemMetrics(SM_CXSCREEN)
#define WINDOWY GetSystemMetrics(SM_CYSCREEN)
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
    refresh();
    bool isGenCode = 0;
    while(!isDone)
    {
        POINT CursorPosition;
        CursorPosition.x=mousex();
        CursorPosition.y=mousey();
        if(isInsideScheme(CursorPosition) and IS_INSIDE_SCHEME==0)
        {
            IS_INSIDE_SCHEME=1;
            hoverEffect(0, 0, "SCHEME", IS_INSIDE_SCHEME);
        }
        else if(!isInsideScheme(CursorPosition) and IS_INSIDE_SCHEME==1)
        {
            IS_INSIDE_SCHEME=0;
            hoverEffect(0, 0, "SCHEME", IS_INSIDE_SCHEME);
        }

        if(isInsideCustomize(CursorPosition) and IS_INSIDE_CUSTOMIZE==0)
        {
            IS_INSIDE_CUSTOMIZE=1;
            hoverEffect(tileX, 0, "CUSTOMIZE", IS_INSIDE_CUSTOMIZE);
        }
        else if(!isInsideCustomize(CursorPosition) and IS_INSIDE_CUSTOMIZE==1)
        {
            IS_INSIDE_CUSTOMIZE=0;
            hoverEffect(tileX, 0, "CUSTOMIZE", IS_INSIDE_CUSTOMIZE);
        }

        if(isInsideOthers(CursorPosition) and IS_INSIDE_OTHERS==0) //inside others button
        {
            IS_INSIDE_OTHERS=1;
            hoverEffect(tileX*2, 0, "OTHERS", IS_INSIDE_OTHERS);
        }
        else if(!isInsideOthers(CursorPosition) and IS_INSIDE_OTHERS==1) //inside others button
        {
            IS_INSIDE_OTHERS=0;
            hoverEffect(tileX*2, 0, "OTHERS", IS_INSIDE_OTHERS);
        }

        if (ismouseclick(WM_LBUTTONDOWN))
        {
            getmouseclick(WM_LBUTTONDOWN, xx, yy);
            clearmouseclick(WM_LBUTTONDOWN);

            if (yy <= MENUY)
                handleMenuClick(xx, yy, isGenCode);
            else
            {
                reinitializeAllViz();
                selectCorrectNode(xx, yy, p, behind);

                if(p)
                {
                    int difX=xx-p->coordX;
                    int difY=yy-p->coordY;
                    moveBlock(xx, yy, p, false, difX, difY);
                }
                else if (xx < DRAG_SIZE_X && yy > MENUY)
                {
                    strcpy(newBlock, selectedNewBlock(xx, yy));
                    if (strcmp(newBlock, "NO") && ((strcmp(newBlock, "START") && START->wasCreated) || (!strcmp(newBlock, "START") && !START->wasCreated)))
                        dragNewBlock(xx, yy, newBlock);
                }
                else if (xx > firstGenCodeX && xx < lastGenCodeX && yy > MENUY + spaceGenCodeY && yy <  MENUY + spaceGenCodeY + smallTileY)
                {
                    isGenCode=1;
                    IS_OUTPUT_ON=0;
                }
                refresh();
                if(isGenCode==1) generateCode(isGenCode);
                else if(IS_OUTPUT_ON) outputNow(IS_OUTPUT_ON);
            }
        }
        else if (ismouseclick(WM_RBUTTONDOWN))
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

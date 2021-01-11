#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "list.h"
#include "blocksMoveDel.h"
#include "openSaveScheme.h"

#define START_X 70
#define START_Y 110
#define STOP_X 70
#define STOP_Y 200
#define IN_X 80
#define IN_Y 300
#define OUT_X 80
#define OUT_Y 380
#define ASSIGN_X 50
#define ASSIGN_Y 480
#define DECISION_X 50
#define DECISION_Y 570

#define MENUY 70
#define WINDOWX GetSystemMetrics(SM_CXSCREEN)
#define WINDOWY GetSystemMetrics(SM_CYSCREEN)

void refresh();
void moveBlock(int x, int y, node *p, bool isNew);
void isSchemeCorrect(node * k, bool & isCorrect);
void analyzeScheme(node * k);

const int tileX = WINDOWX / 3;
const int smallTileX = 170;// textwidth("Background Color") + 50
const int smallTileY = MENUY * 0.8;
const int firstSchemeX = (tileX - smallTileX) / 2;
const int lastSchemeX = smallTileX + firstSchemeX;
const int lastSchemeY = MENUY + smallTileY * 4;
const int firstCustomizeX = tileX + (tileX - smallTileX) / 2;
const int lastCustomizeX = smallTileX + firstCustomizeX;
const int lastCustomizeY = MENUY + smallTileY * 2;
const int spaceGenCodeY = 10;
const int sizeGenCodeY = MENUY * 0.6;
const int sizeGenCodeX = 146; // textwidth("Generate Code")-96 + 50
const int spaceGenCodeX = (OUTPUT_SIZE_X  - sizeGenCodeX) / 2;
const int firstGenCodeX = WINDOWX - OUTPUT_SIZE_X + spaceGenCodeX;
const int lastGenCodeX = WINDOWX - spaceGenCodeX;
const int textGenCodeX = firstGenCodeX + 25; // 50/2
const int textGenCodeY = (sizeGenCodeY - 16)/2 + MENUY + spaceGenCodeY; // 16-- textheight

char *selectedNewBlock(int x, int y)
{
    node *newBlock = new node;
    newBlock->coordX = START_X;
    newBlock->coordY = START_Y;
    strcpy(newBlock->type, "START");
    if (isInsideNode(x, y, newBlock))
        return newBlock->type;

    newBlock->coordX = STOP_X;
    newBlock->coordY = STOP_Y;
    strcpy(newBlock->type, "STOP");
    if (isInsideNode(x, y, newBlock))
        return newBlock->type;

    newBlock->coordX = IN_X;
    newBlock->coordY = IN_Y;
    strcpy(newBlock->type, "IN");
    if (isInsideNode(x, y, newBlock))
        return newBlock->type;

    newBlock->coordX = OUT_X;
    newBlock->coordY = OUT_Y;
    strcpy(newBlock->type, "OUT");
    if (isInsideNode(x, y, newBlock))
        return newBlock->type;

    newBlock->coordX = ASSIGN_X;
    newBlock->coordY = ASSIGN_Y;
    strcpy(newBlock->type, "ASSIGN");
    if (isInsideNode(x, y, newBlock))
        return newBlock->type;

    newBlock->coordX = DECISION_X;
    newBlock->coordY = DECISION_Y;
    strcpy(newBlock->type, "DECISION");
    if (isInsideNode(x, y, newBlock))
        return newBlock->type;

    return "NO";
}

void dragNewBlock(int x, int y, char *blockType)
{
    moveBlock(x, y, createNode(blockType, !strcmp(blockType, "DECISION"), x, y, 0), true);
}

void drawGenCodeButton()
{
    setcolor(DARKGRAY);
    line(firstGenCodeX, MENUY + spaceGenCodeY + sizeGenCodeY, firstGenCodeX, MENUY + spaceGenCodeY); // |
    line(firstGenCodeX, MENUY + spaceGenCodeY, lastGenCodeX, MENUY + spaceGenCodeY); // --
    line(lastGenCodeX, MENUY + spaceGenCodeY, lastGenCodeX, MENUY + spaceGenCodeY + sizeGenCodeY); // |
    line(lastGenCodeX, MENUY + spaceGenCodeY + sizeGenCodeY, firstGenCodeX, MENUY + spaceGenCodeY + sizeGenCodeY); // --

    setfillstyle(SOLID_FILL, THEME[CURRENT_THEME].option_clr);
    floodfill(firstGenCodeX + sizeGenCodeX / 2, MENUY + spaceGenCodeY + sizeGenCodeY / 2, DARKGRAY);

    setcolor(WHITE);
    setbkcolor(THEME[CURRENT_THEME].option_clr);
    outtextxy(textGenCodeX, textGenCodeY, "Generate Code");
    setbkcolor(THEME[CURRENT_THEME].bck_clr);
}

void drawPage()
{
    setbkcolor(THEME[CURRENT_THEME].bck_clr);
    //drag and drop blocks
    setlinestyle(0, 0, 3);
    createStart(START_X, START_Y, true, true);
    createStop(STOP_X, STOP_Y, true, true);
    createIn(IN_X, IN_Y, true, true, "no expression");
    createOut(OUT_X, OUT_Y, true, true, "no expression");
    createAssign(ASSIGN_X, ASSIGN_Y, true, true, "no expression");
    createDecision(DECISION_X, DECISION_Y, true, true, "no expression");

    setcolor(THEME[CURRENT_THEME].button_clr);
    line(0, MENUY, WINDOWX, MENUY); // menu
    line(DRAG_SIZE_X, MENUY, DRAG_SIZE_X, WINDOWY); //drag
    line(WINDOWX - OUTPUT_SIZE_X, MENUY, WINDOWX - OUTPUT_SIZE_X, WINDOWY); //output
    drawGenCodeButton();
}

void drawMenu()
{
    setfillstyle(SOLID_FILL, THEME[CURRENT_THEME].button_clr);

    setcolor(RED);
    line(0, MENUY, WINDOWX, MENUY);

    floodfill(tileX / 2, MENUY / 2, RED);

    setcolor(THEME[CURRENT_THEME].button_clr);
    line(0, MENUY, WINDOWX, MENUY);

    setlinestyle(SOLID_LINE, 0, 1);
    setcolor(THEME[CURRENT_THEME].bck_clr);
    line(tileX * 2, 0, tileX * 2, MENUY);
    line(tileX, 0, tileX, MENUY);

    setbkcolor(THEME[CURRENT_THEME].button_clr);
    setcolor(WHITE);
    outtextxy((tileX - textwidth("SCHEME")) / 2, (MENUY - textheight("SCHEME")) / 2, "SCHEME");
    outtextxy((tileX - textwidth("CUSTOMIZE")) / 2 + tileX, (MENUY - textheight("CUSTOMIZE")) / 2, "CUSTOMIZE");
    outtextxy((tileX - textwidth("HELP")) / 2 + tileX * 2, (MENUY - textheight("HELP")) / 2, "HELP");
    setbkcolor(THEME[CURRENT_THEME].bck_clr);
}

void drawSubmenuScheme(bool isColored)
{
    setlinestyle(0, 0, 1);
    setcolor(DARKGRAY);

    line(firstSchemeX, MENUY, firstSchemeX, lastSchemeY); // |
    line(firstSchemeX, lastSchemeY, lastSchemeX, lastSchemeY); // -
    line(lastSchemeX, MENUY, lastSchemeX, lastSchemeY); // |
    line(firstSchemeX, MENUY, lastSchemeX, MENUY); // -

    if (isColored)
    {
        setfillstyle(SOLID_FILL, THEME[CURRENT_THEME].option_clr);
        setcolor(THEME[CURRENT_THEME].option_clr);
    }
    else
    {
        setfillstyle(SOLID_FILL, THEME[CURRENT_THEME].bck_clr);
        setcolor(THEME[CURRENT_THEME].bck_clr);
    }

    floodfill(firstSchemeX + smallTileX / 2, lastSchemeY / 2, DARKGRAY);

    line(firstSchemeX, MENUY, firstSchemeX, lastSchemeY); // |
    line(firstSchemeX, lastSchemeY, lastSchemeX, lastSchemeY); // -
    line(lastSchemeX, MENUY, lastSchemeX, lastSchemeY); // |
    line(firstSchemeX, MENUY, lastSchemeX, MENUY); // -

    if (isColored)
    {
        setcolor(THEME[CURRENT_THEME].bck_clr);
        line(firstSchemeX, MENUY + smallTileY, lastSchemeX, MENUY + smallTileY);
        line(firstSchemeX, MENUY + smallTileY * 2, lastSchemeX, MENUY + smallTileY * 2);
        line(firstSchemeX, MENUY + smallTileY * 3, lastSchemeX, MENUY + smallTileY * 3);

        setbkcolor(THEME[CURRENT_THEME].option_clr);
        setcolor(WHITE);
        outtextxy(firstSchemeX + (smallTileX - textwidth("Save")) / 2, MENUY + (smallTileY - textheight("Save")) / 2, "Save");
        outtextxy(firstSchemeX + (smallTileX - textwidth("Open")) / 2, MENUY + smallTileY + (smallTileY - textheight("Open")) / 2, "Open");
        outtextxy(firstSchemeX + (smallTileX - textwidth("Clear")) / 2, MENUY + smallTileY * 2 + (smallTileY - textheight("Clear")) / 2, "Clear");
        outtextxy(firstSchemeX + (smallTileX - textwidth("Run")) / 2, MENUY + smallTileY * 3 + (smallTileY - textheight("Run")) / 2, "Run");
        setbkcolor(THEME[CURRENT_THEME].bck_clr);
    }
}

void drawSubmenuCustomize(bool isColored)
{
    setlinestyle(0, 0, 1);
    setcolor(DARKGRAY);

    line(firstCustomizeX, MENUY, firstCustomizeX, lastCustomizeY); // |
    line(firstCustomizeX, lastCustomizeY, lastCustomizeX, lastCustomizeY); // -
    line(lastCustomizeX, MENUY, lastCustomizeX, lastCustomizeY); // |
    line(firstCustomizeX, MENUY, lastCustomizeX, MENUY); // -

    if (isColored)
    {
        setfillstyle(SOLID_FILL, THEME[CURRENT_THEME].option_clr);
        setcolor(THEME[CURRENT_THEME].option_clr);
    }
    else
    {
        setfillstyle(SOLID_FILL, THEME[CURRENT_THEME].bck_clr);
        setcolor(THEME[CURRENT_THEME].bck_clr);
    }

    floodfill(firstCustomizeX + smallTileX / 2, lastCustomizeY / 2, DARKGRAY);

    line(firstCustomizeX, MENUY, firstCustomizeX, lastCustomizeY); // |
    line(firstCustomizeX, lastCustomizeY, lastCustomizeX, lastCustomizeY); // -
    line(lastCustomizeX, MENUY, lastCustomizeX, lastCustomizeY); // |
    line(firstCustomizeX, MENUY, lastCustomizeX, MENUY); // -

    if (isColored)
    {
        setcolor(THEME[CURRENT_THEME].bck_clr);
        line(firstCustomizeX, MENUY + smallTileY, lastCustomizeX, MENUY + smallTileY);

        setbkcolor(THEME[CURRENT_THEME].option_clr);
        setcolor(WHITE);
        outtextxy(firstCustomizeX + (smallTileX - textwidth("Theme 1")) / 2, MENUY + (smallTileY - textheight("Theme 1")) / 2, "Theme 1");
        outtextxy(firstCustomizeX + (smallTileX - textwidth("Theme 2")) / 2, MENUY + smallTileY + (smallTileY - textheight("Theme 2")) / 2, "Theme 2");
        setbkcolor(THEME[CURRENT_THEME].bck_clr);
    }
}

//to implement as sparkles
void hoverMenu(int x, int y)
{
}

void popUpAgreeEmptyScheme(bool & continueEmptyScheme)
{
    int textboxWidth=250, textboxHeight=100;
    setlinestyle(SOLID_LINE, 0, 1);
    setcolor(RED);
    line(WINDOWX/2-textboxWidth/2, WINDOWY/2-textboxHeight/2, WINDOWX/2-textboxWidth/2, WINDOWY/2+textboxHeight/2);
    line(WINDOWX/2-textboxWidth/2, WINDOWY/2-textboxHeight/2, WINDOWX/2+textboxWidth/2, WINDOWY/2-textboxHeight/2);
    line(WINDOWX/2+textboxWidth/2, WINDOWY/2-textboxHeight/2, WINDOWX/2+textboxWidth/2, WINDOWY/2+textboxHeight/2);
    line(WINDOWX/2+textboxWidth/2, WINDOWY/2+textboxHeight/2, WINDOWX/2-textboxWidth/2, WINDOWY/2+textboxHeight/2);

    setfillstyle(SOLID_FILL, THEME[CURRENT_THEME].option_clr);
    floodfill(WINDOWX/2, WINDOWY/2, RED);

    setcolor(THEME[CURRENT_THEME].option_clr);
    line(WINDOWX/2-textboxWidth/2, WINDOWY/2-textboxHeight/2, WINDOWX/2-textboxWidth/2, WINDOWY/2+textboxHeight/2);
    line(WINDOWX/2-textboxWidth/2, WINDOWY/2-textboxHeight/2, WINDOWX/2+textboxWidth/2, WINDOWY/2-textboxHeight/2);
    line(WINDOWX/2+textboxWidth/2, WINDOWY/2-textboxHeight/2, WINDOWX/2+textboxWidth/2, WINDOWY/2+textboxHeight/2);
    line(WINDOWX/2+textboxWidth/2, WINDOWY/2+textboxHeight/2, WINDOWX/2-textboxWidth/2, WINDOWY/2+textboxHeight/2);

    setcolor(THEME[CURRENT_THEME].bck_clr);
    line(WINDOWX/2-textboxWidth/2, WINDOWY/2, WINDOWX/2+textboxWidth/2, WINDOWY/2);
    line(WINDOWX/2, WINDOWY/2, WINDOWX/2, WINDOWY/2+textboxHeight/2);

    setbkcolor(THEME[CURRENT_THEME].option_clr);
    setcolor(WHITE);
    outtextxy(WINDOWX/2-textwidth("Unsaved scheme will be lost!")/2, WINDOWY/2-textheight("Unsaved scheme will be lost!")/2-textboxHeight/4, "Unsaved scheme will be lost!");
    outtextxy(WINDOWX/2-textboxWidth/4-textwidth("Continue")/2, WINDOWY/2-textheight("Continue")/2+textboxHeight/4, "Continue");
    outtextxy(WINDOWX/2+textboxWidth/4-textwidth("Back")/2, WINDOWY/2-textheight("Back")/2+textboxHeight/4, "Back");
    setbkcolor(THEME[CURRENT_THEME].bck_clr);

    bool done=0;
    while(!done)
    {
        if (ismouseclick(WM_LBUTTONDOWN))
        {
            int xx, yy;
            getmouseclick(WM_LBUTTONDOWN, xx, yy);
            clearmouseclick(WM_LBUTTONDOWN);
            if(xx<WINDOWX/2 and xx>WINDOWX/2-textboxWidth/2 and yy>WINDOWY/2 and yy<WINDOWY/2+textboxHeight/2)
                done=1;
            else
            {
                if(!(xx<WINDOWX/2+textboxWidth/2 and xx>WINDOWX/2-textboxWidth/2 and yy<WINDOWY/2 and yy>WINDOWY/2-textboxHeight/2))
                {
                    done=1;
                    continueEmptyScheme=0;
                }
            }
        }
    }
}

void emptyScheme()
{
    bool continueEmptyScheme=1;
    popUpAgreeEmptyScheme(continueEmptyScheme);
    if(continueEmptyScheme==1)
    {
        reinitializeAllViz();
        reinitializeAllNodesTime();
        createArrayWithAllBlocks();
        if(ALL_NODES_TIME.arraySize)
        {
            for (int i = 0; i < ALL_NODES_TIME.arraySize; ++i)
            {
                reinitializeAllViz();
                node * k = new node;
                k=findNodeByTime(ALL_NODES_TIME.n[i]);
                if(k!=START)
                    deleteNode(k);
            }
        }
        START->wasCreated=0;
    }
    cleardevice();
    drawPage();
    drawMenu();
    drawAllBlocks();
}

void run()
{
    bool isCorrect=1;
    isSchemeCorrect(START, isCorrect);
    if(isCorrect)
        analyzeScheme(START);
}

void handleMenuClick(int x, int y)
{
    int xx, yy;
    bool isDone = false;
//    hoverMenu(x, y);

    //scheme
    if (x < tileX)
    {
        drawSubmenuScheme(true);
        clearmouseclick(WM_LBUTTONDOWN);

        while (!isDone)
        {
            getmouseclick(WM_LBUTTONDOWN, xx, yy);
            if (xx != -1 && yy != -1)
            {
                if (xx > firstSchemeX && xx < lastSchemeX && yy > MENUY && yy < lastSchemeY)
                {
                    if (yy < MENUY + smallTileY)
                        saveScheme();
                    else if (yy < MENUY + smallTileY * 2)
                        openScheme();
                    else if (yy < MENUY + smallTileY * 3)
                        emptyScheme();
                    else if (yy < MENUY + smallTileY * 4)
                        run();
                }
                else
                {
                    cleardevice();
                    drawPage();
                    drawMenu();
                    drawAllBlocks();
                    clearmouseclick(WM_LBUTTONDOWN);
                    isDone = true;
                }
            }
        }
    }

    //customize
    else if (x > tileX && x < tileX * 2)
    {
        drawSubmenuCustomize(true);
        clearmouseclick(WM_LBUTTONDOWN);

        while (!isDone)
        {
            getmouseclick(WM_LBUTTONDOWN, xx, yy);
            if (xx != -1 && yy != -1)
            {
                if (xx > firstCustomizeX && xx < lastCustomizeX && yy > MENUY && yy < lastCustomizeY)
                {
                    if (yy < MENUY + smallTileY)
                        {
                            CURRENT_THEME=0;
                            refresh();
                        }
                    else if (yy < MENUY + smallTileY * 2)
                        {
                            CURRENT_THEME=1;
                            refresh();
                        }
                }
                cleardevice();
                drawPage();
                drawMenu();
                drawAllBlocks();
                isDone = true;
            }
        }
    }
//
//    //help
//    else if (x > tileX * 2)
//    {
//
//    }
}

#endif // MENU_H_INCLUDED
